#include "model_reader.h"

static result_t fread_points(model_t& model, ifstream& file)
{
    result_t ec = OK_CODE;

    size_t points_quantity;
    point_t point;

    file >> points_quantity;
    if (file.fail())
        ec = FORMAT_ERROR_CODE;
    else
        set_points_capacity(model.points, points_quantity);
    
    if (ec == OK_CODE)
        ec = allocate_points_array(model.points, points_quantity);
    
    for (size_t i = 0; (ec == OK_CODE) && (i < points_quantity); ++i)
    {
        file >> point.x >> point.y >> point.z;
        if (file.fail())
            ec = FORMAT_ERROR_CODE;
        else
            ec = push_back_point(model.points, point);
    }


    return ec;
}

static result_t fread_edges(model_t& model, ifstream& file)
{
    result_t ec = OK_CODE;

    size_t edges_quantity;
    edge_t edge;

    file >> edges_quantity;
    if (file.fail())
        ec = FORMAT_ERROR_CODE;
    else
        set_edges_capacity(model.edges, edges_quantity);
    
    if (ec == OK_CODE)
        ec = allocate_edges_array(model.edges, edges_quantity);
    
    for (size_t i = 0; (ec == OK_CODE) && (i < edges_quantity); ++i)
    {
        file >> edge.p1 >> edge.p2;
        if (file.fail())
            ec = FORMAT_ERROR_CODE;
        else
            ec = push_back_edge(model.edges, edge);
    }


    return ec;
}

result_t load_model(model_t& model, const char *filename)
{
    result_t ec = OK_CODE;

    free_model(model);

    ifstream file(filename);

    if (!file.is_open())
        ec = FILE_ERROR_CODE;
    else
    {
        fread_points(model, file);
        fread_edges(model, file);
        ec = validate_model(model);
    } 

    return ec;
}