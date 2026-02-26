#include "model_reader.h"

static result_t fread_point(ifstream& file, point_t& point)
{
    result_t ec = OK_CODE;

    file >> point.x >> point.y >> point.z;

    return ec;
}

static result_t fread_points(points_t& points, ifstream& file)
{
    result_t ec = OK_CODE;

    size_t points_quantity;
    point_t point;

    file >> points_quantity;
    if (file.fail())
    {
        ec = FORMAT_ERROR_CODE;
    }
    else
    {
        set_points_capacity(points, points_quantity);
    }
    
    if (ec == OK_CODE)
    {
        ec = allocate_points_array(points, points_quantity);
    }
    
    for (size_t i = 0; (ec == OK_CODE) && (i < points_quantity); ++i)
    {
        fread_point(file, point);
        if (file.fail())
        {
            ec = FORMAT_ERROR_CODE;
        }
        else
        {
            ec = push_back_point(points, point);
        }
    }


    return ec;
}

static result_t fread_edge(ifstream& file, edge_t& edge)
{
    result_t ec = OK_CODE;

    file >> edge.p1 >> edge.p2;

    return ec;
}

static result_t fread_edges(edges_t& edges, ifstream& file)
{
    result_t ec = OK_CODE;

    size_t edges_quantity;
    edge_t edge;

    file >> edges_quantity;
    if (file.fail())
    {
        ec = FORMAT_ERROR_CODE;
    }
    else
    {
        set_edges_capacity(edges, edges_quantity);
    }
    
    if (ec == OK_CODE)
    {
        ec = allocate_edges_array(edges, edges_quantity);
    }
    
    for (size_t i = 0; (ec == OK_CODE) && (i < edges_quantity); ++i)
    {
        fread_edge(file, edge);
        if (file.fail())
        {
            ec = FORMAT_ERROR_CODE;
        }
        else
        {
            ec = push_back_edge(edges, edge);
        }
    }


    return ec;
}

result_t fread_model(model_t& model, ifstream& file)
{
    result_t ec = OK_CODE;


    ec = fread_points(model.points, file);

    if (ec == OK_CODE)
    {
        ec = fread_edges(model.edges, file);
        if (ec != OK_CODE)
        {
            free_points(model.points);
        }
    }

    return ec;
}

result_t load_model(model_t& model, const char *filename)
{
    result_t ec = OK_CODE;

    ifstream file(filename);

    if (!file.is_open())
    {
        ec = FILE_ERROR_CODE;
    }
    else
    {
        model_t temp_model;
        init_model(temp_model);

        ec = fread_model(temp_model, file);

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
                model = temp_model;
            }
                
        }
    }

    return ec;
}