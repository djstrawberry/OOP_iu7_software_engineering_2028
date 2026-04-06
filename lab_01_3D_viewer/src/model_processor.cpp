#include "model_processor.h"

void init_model(model_t& model)
{
    init_point(model.center);
    init_edges(model.edges);
    init_points(model.points);
}

void free_model(model_t& model)
{
    free_edges(model.edges);
    free_points(model.points);
}

result_t validate_model(const model_t& model)
{
    result_t ec = OK_CODE;

    if (get_edges_size(model.edges) > get_edges_capacity(model.edges))
        ec = RANGE_ERROR_CODE;
    else
    {
        validate_edges(model.edges, get_points_size(model.points));
    }

    return ec;
}

static void scale_point(point_t& point, point_t& center, const scale_params_t& params)
{
    point.x = center.x + (point.x - center.x) * params.kx;
    point.y = center.y + (point.y - center.y) * params.ky;
    point.z = center.z + (point.z - center.z) * params.kz;
}

static bool check_scale_params(const scale_params_t& params)
{
    return params.kx && params.ky && params.kz;
}

static result_t scale_points(points_t& points, point_t& center, const scale_params_t& params)
{
    result_t ec = OK_CODE;

    point_t* points_array = get_points_array(points);
    if (!points_array)
    {
        ec = NULLPTR_ERROR_CODE;
    }
    else
    {
        for (size_t i = 0; i < get_points_size(points); ++i)
        {
            scale_point(points_array[i], center, params);
        }
    }
    return ec;
}

result_t scale_model(model_t& model, const scale_params_t& params)
{
    result_t ec = validate_model(model);

    if (ec == OK_CODE)
    {
        if (!check_scale_params(params))
        {
            ec = RANGE_ERROR_CODE;
        }
        else
        {
            ec = scale_points(model.points, model.center, params);
        }
    }

    return ec;
}

static void convert_to_radians(double degrees, double& radians)
{
    radians = degrees * M_PI / 180.0;
}

static void rotate_around_x_axis(point_t& point, point_t& center, double angle)
{
    double radians;
    convert_to_radians(angle, radians);

    double y = point.y;

    double cos_a = cos(radians), sin_a = sin(radians);

    point.y = (point.y - center.y) * cos_a + (point.z - center.z) * sin_a + center.y;
    point.z = -(y - center.y) * sin_a + (point.z - center.z) * cos_a + center.z;
}

static void rotate_around_y_axis(point_t& point, point_t& center, double angle)
{
    double radians;
    convert_to_radians(angle, radians);

    double x = point.x;

    double cos_a = cos(radians), sin_a = sin(radians);

    point.x = (point.x - center.x) * cos_a + (point.z - center.z) * sin_a + center.x;
    point.z = -(x - center.x) * sin_a + (point.z - center.z) * cos_a + center.z;
}

static void rotate_around_z_axis(point_t& point, point_t& center, double angle)
{
    double radians;
    convert_to_radians(angle, radians);

    double x = point.x;

    double cos_a = cos(radians), sin_a = sin(radians);

    point.x = (point.x - center.x) * cos_a + (point.y - center.y) * sin_a + center.x;
    point.y = -(x - center.x) * sin_a + (point.y - center.y) * cos_a + center.y;
}

static void rotate_point(point_t& point, point_t& center, const rotate_params_t& params)
{
    rotate_around_x_axis(point, center, params.angle_x);
    rotate_around_y_axis(point, center, params.angle_y);
    rotate_around_z_axis(point, center, params.angle_z);
}

static void rotate_points(point_t *points_array, point_t& center, size_t size, const rotate_params_t& params)
{
    for (size_t i = 0; i < size; ++i)
    {
        rotate_point(points_array[i], center, params);
    }
}

result_t rotate_model(model_t& model, const rotate_params_t& params)
{
    result_t ec = validate_model(model);
    point_t* points_array;

    if (ec == OK_CODE)
    {
        points_array = get_points_array(model.points);
        if (!points_array)
        {
            ec = NULLPTR_ERROR_CODE;
        }
        else
        {
            rotate_points(points_array, model.center, get_points_size(model.points), params);
        }
    }

    return ec;
}

static void transfer_point(point_t& point, const transfer_params_t& params)
{
    point.x = point.x + params.dx;
    point.y = point.y + params.dy;
    point.z = point.z + params.dz;
}

static void transfer_points(point_t *points_array, point_t& center, size_t size, const transfer_params_t& params)
{
    transfer_point(center, params);
    for (size_t i = 0; i < size; ++i)
    {
        transfer_point(points_array[i], params);
    }
}

result_t transfer_model(model_t& model, const transfer_params_t& params)
{
    result_t ec = validate_model(model);
    point_t* points_array;

    if (ec == OK_CODE)
    {
        points_array = get_points_array(model.points);
        if (!points_array)
        {
            ec = NULLPTR_ERROR_CODE;
        }
        else
        {
            transfer_points(points_array, model.center, get_points_size(model.points), params);
        }
    }
 
    return ec;
}