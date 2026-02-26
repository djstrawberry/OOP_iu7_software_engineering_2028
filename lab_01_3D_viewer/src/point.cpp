#include "point.h"

size_t get_points_size(const points_t& points)
{
    return points.size;
}

point_t *get_points_array(const points_t& points)
{
    return points.points;
}

void set_points_capacity(points_t& points, size_t capacity)
{
    points.capacity = capacity;
}

void init_point(point_t& point)
{
    point.x = 0.0;
    point.y = 0.0;
    point.z = 0.0;
}

void init_points(points_t& points)
{
    points.points = nullptr;
    points.size = 0;
    points.capacity = 0;
}   

void free_points(points_t& points)
{
    if (points.points)
    {
        free(points.points);
    }
    points.points = nullptr;

    points.size = 0;
    points.capacity = 0;
}

result_t allocate_points_array(points_t& points, size_t capacity)
{
    result_t ec = OK_CODE;

    points.points = (point_t *)malloc(sizeof(point_t) * capacity);
    if (!points.points)
    {
        ec = MEMORY_ERROR_CODE;
    }
    else
    {
        points.size = 0;
        points.capacity = capacity;
    }

    return ec;
}

result_t push_back_point(points_t& points, const point_t& point)
{
    result_t ec = OK_CODE;

    if (points.size >= points.capacity)
    {
        ec = RANGE_ERROR_CODE;
    }
    else
    {
        points.points[points.size++] = point;
    }

    return ec;
}