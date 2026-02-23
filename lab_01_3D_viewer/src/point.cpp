#include "../inc/point.h"

size_t get_points_size(const points_t& points)
{
    return points.size;
}

point_t *get_points_array(points_t& points)
{
    return points.points;
}

void set_points_capacity(points_t& points, size_t capacity)
{
    points.capacity = capacity;
}

result_t init_point(point_t& point)
{
    result_t ec = OK_CODE;

    point.x = 0.0;
    point.y = 0.0;
    point.z = 0.0;

    return ec;                          
}

result_t init_points(points_t& points)
{
    result_t ec = OK_CODE;

    points.points = nullptr;
    points.size = 0;
    points.capacity = 0;

    return ec;                          
}   

result_t free_points(points_t& points)
{
    result_t ec = OK_CODE;

    if (points.points)
        free(points.points);
    points.points = nullptr;

    points.size = 0;
    points.capacity = 0;

    return ec;
}

result_t allocate_points_array(points_t& points, size_t capacity)
{
    result_t ec = OK_CODE;

    points.points = (point_t *)malloc(sizeof(point_t) * capacity);
    if (!points.points)
        ec = MEMORY_ERROR_CODE;
    else
    {
        points.size = 0;
        points.capacity = capacity;
    }

    return ec;
}

result_t push_back_point(points_t& points, point_t& point)
{
    result_t ec = OK_CODE;

    if (points.size >= points.capacity)
        ec = RANGE_ERROR_CODE;
    else
        points.points[points.size++] = point;

    return ec;
}