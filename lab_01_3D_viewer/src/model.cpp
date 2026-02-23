#include "../inc/model.h"

result_t init_model(model_t& model)
{
    result_t ec = OK_CODE;

    init_point(model.center);
    init_edges(model.edges);
    init_points(model.points);

    return ec;
}

result_t free_model(model_t& model)
{
    result_t ec = OK_CODE;

    free_edges(model.edges);
    free_points(model.points);

    return ec;
}

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

// МБ объединить их? 
// TODO: перегрузить

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

static result_t validate_edge(edge_t& edge, const size_t& max_index)
{
    result_t ec = OK_CODE;

    if (edge.p1 < 0 || edge.p1 >= max_index || edge.p2 < 0 || edge.p2 >= max_index)
    {
        ec = RANGE_ERROR_CODE;
        cout << "HERE";
    }

    return ec;
}

static result_t validate_model(model_t& model)
{
    result_t ec = OK_CODE;

    if (get_edges_size(model.edges) > get_edges_capacity(model.edges))
        ec = RANGE_ERROR_CODE;
    else
    {
        for (size_t i = 0; (ec == OK_CODE) && (i < get_edges_size(model.edges)); ++i)
        {
            ec = validate_edge(get_edges_array(model.edges)[i], get_points_size(model.points));
        }
    }

    return ec;
}

result_t load_model(model_t& model, const char *filename)
{
    result_t ec = OK_CODE;

    free_model(model);

    ifstream file(filename);

    if (file.is_open())
    {
        fread_points(model, file);
        fread_edges(model, file);
        ec = validate_model(model);
    }
    else
        ec = FILE_ERROR_CODE;

    return ec;
}

result_t draw_model(model_t& model, scene_t& scene)
{
    result_t ec = OK_CODE;

    scene.scene->clear();

    point_t p1, p2;
    double x1, x2, y1, y2;
    edge_t current_edge;

    for (size_t i = 0; i < get_edges_size(model.edges); ++i)
    {
        current_edge = get_edges_array(model.edges)[i];

        p1 = get_points_array(model.points)[current_edge.p1];
        p2 = get_points_array(model.points)[current_edge.p2];

        x1 = p1.x + scene.width / 2;
        x2 = p2.x + scene.width / 2;
        y1 = p1.y + scene.height / 2;
        y2 = p2.y + scene.height / 2;

        scene.scene->addLine(x1, y1, x2, y2, QPen(QColor(204, 36, 84)));
    }

    return ec;
}

static result_t scale_point(point_t& point, point_t& center, scale_params_t& params)
{
    result_t ec = OK_CODE;

    point.x = center.x + (point.x - center.x) * params.kx;
    point.y = center.y + (point.y - center.y) * params.ky;
    point.z = center.z + (point.z - center.z) * params.kz;

    return ec;
}

result_t scale_model(model_t& model, scale_params_t& params)
{
    result_t ec = OK_CODE;

    if (!params.kx || !params.ky || !params.kz)
        ec = RANGE_ERROR_CODE;
    else
    {
        for (size_t i = 0; i < get_points_size(model.points); ++i)
            scale_point(get_points_array(model.points)[i], model.center, params);
    }

    return ec;
}

static result_t convert_to_radians(double degrees, double& radians)
{
    result_t ec = OK_CODE;

    radians = degrees * M_PI / 180.0;

    return ec;
}

static result_t rotate_around_x_axis(point_t& point, point_t& center, double angle)
{
    result_t ec = OK_CODE;

    double radians;
    convert_to_radians(angle, radians);

    double y = point.y;

    double cos_a = cos(radians), sin_a = sin(radians);

    point.y = (point.y - center.y) * cos_a + (point.z - center.z) * sin_a + center.y;
    point.z = -(y - center.y) * sin_a + (point.z - center.z) * cos_a + center.z;

    return ec;
}

static result_t rotate_around_y_axis(point_t& point, point_t& center, double angle)
{
    result_t ec = OK_CODE;

    double radians;
    convert_to_radians(angle, radians);

    double x = point.x;

    double cos_a = cos(radians), sin_a = sin(radians);

    point.x = (point.x - center.x) * cos_a + (point.z - center.z) * sin_a + center.x;
    point.z = -(x - center.x) * sin_a + (point.z - center.z) * cos_a + center.z;

    return ec;
}

static result_t rotate_around_z_axis(point_t& point, point_t& center, double angle)
{
    result_t ec = OK_CODE;

    double radians;
    convert_to_radians(angle, radians);

    double x = point.x;

    double cos_a = cos(radians), sin_a = sin(radians);

    point.x = (point.x - center.x) * cos_a + (point.y - center.y) * sin_a + center.x;
    point.y = -(x - center.x) * sin_a + (point.y - center.y) * cos_a + center.y;

    return ec;
}

static result_t rotate_point(point_t& point, point_t& center, rotate_params_t& params)
{
    result_t ec = OK_CODE;

    rotate_around_x_axis(point, center, params.angle_x);
    rotate_around_y_axis(point, center, params.angle_y);
    rotate_around_z_axis(point, center, params.angle_z);

    return ec;
}

result_t rotate_model(model_t& model, rotate_params_t& params)
{
    result_t ec = OK_CODE;

    for (size_t i = 0; i < get_points_size(model.points); ++i)
        rotate_point(get_points_array(model.points)[i], model.center, params);

    return ec;
}

static result_t transfer_point(point_t& point, transfer_params_t& params)
{
    result_t ec = OK_CODE;

    point.x = point.x + params.dx;
    point.y = point.y + params.dy;
    point.z = point.z + params.dz;

    return ec;
}

result_t transfer_model(model_t& model, transfer_params_t& params)
{
    result_t ec = OK_CODE;

    transfer_point(model.center, params);
    for (size_t i = 0; i < get_points_size(model.points); ++i)
        transfer_point(get_points_array(model.points)[i], params);

    return ec;
}