#include "model_reader.h"

static result_t fread_point(FILE *file, point_t& point)
{
    result_t ec = OK_CODE;

    if (fscanf(file, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
    {
        ec = FORMAT_ERROR_CODE;
    }

    return ec;
}

static result_t read_points_to_array(FILE *file, points_t& points, size_t points_quantity)
{
    result_t ec = OK_CODE;

    point_t point;

    for (size_t i = 0; (ec == OK_CODE) && (i < points_quantity); ++i)
    {
        if (fread_point(file, point) == OK_CODE)
        {
            ec = push_back_point(points, point);
        }
    }

    return ec;
}

static result_t fread_points(FILE *file, points_t& points, size_t& points_quantity)
{
    result_t ec = OK_CODE;

    if (fscanf(file, "%zu", &points_quantity) != 1)
    {
        ec = FORMAT_ERROR_CODE;
    }
    else
    {
        set_points_capacity(points, points_quantity);
        ec = allocate_points_array(points, points_quantity);
        if (ec == OK_CODE)
        { 
            ec = read_points_to_array(file, points, points_quantity);
        }
    }

    return ec;
}

static result_t fread_edge(FILE *file, edge_t& edge)
{
    result_t ec = OK_CODE;

    if (fscanf(file, "%zu %zu", &edge.p1, &edge.p2) != 2)
    {
        ec = FORMAT_ERROR_CODE;
    }

    return ec;
}

static result_t read_edges_to_array(FILE *file, edges_t& edges, size_t edges_quantity, size_t points_quantity)
{
    result_t ec = OK_CODE;

    edge_t edge;

    for (size_t i = 0; (ec == OK_CODE) && (i < edges_quantity); ++i)
    {
        if (fread_edge(file, edge) == OK_CODE)
        {
            ec = validate_edge(edge, points_quantity);  
        }
        if (ec == OK_CODE)
        {
            ec = push_back_edge(edges, edge);
        }
    }

    return ec;
}

static result_t fread_edges(FILE *file, edges_t& edges, size_t points_quantity)
{
    result_t ec = OK_CODE;

    size_t edges_quantity;

    if (fscanf(file, "%zu", &edges_quantity) != 1)
        ec = FORMAT_ERROR_CODE;
    else
    {
        set_edges_capacity(edges, edges_quantity);
        ec = allocate_edges_array(edges, edges_quantity);
        if (ec == OK_CODE)
        {
            ec = read_edges_to_array(file, edges, edges_quantity, points_quantity);
        }
    }

    return ec;
}

result_t fread_model(model_t& model, FILE *file)
{
    result_t ec = OK_CODE;

    size_t points_quantity;
    ec = fread_points(file, model.points, points_quantity);

    if (ec == OK_CODE)
    {
        ec = fread_edges(file, model.edges, points_quantity);
        if (ec != OK_CODE)
        {
            free_points(model.points);
        }
    }

    return ec;
}

static void copy_model(model_t& dst, model_t& src)
{
    dst = src;
}

result_t load_model(model_t& model, const char *filename)
{
    result_t ec = OK_CODE;

    FILE* file = fopen(filename, "r");

    if (!file)
    {
        ec = FILE_ERROR_CODE;
    }
    else
    {
        model_t temp_model;
        init_model(temp_model);

        ec = fread_model(temp_model, file);
        fclose(file);

        if (ec == OK_CODE)
        {
            ec = validate_model(temp_model);
            if (ec != OK_CODE)
            {
                free_model(temp_model);
            }
            else
            {
                free_model(model);
                copy_model(model, temp_model);
            }
                
        }
    }

    return ec;
}