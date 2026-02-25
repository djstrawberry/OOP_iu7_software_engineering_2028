#ifndef POINT_H
#define POINT_H

#include "result.h"

typedef struct
{
    double x;
    double y;
    double z;
} point_t;

typedef struct
{
    point_t *points;
    size_t size;
    size_t capacity;
} points_t;

result_t init_point(point_t& point);
result_t init_points(points_t& points);
result_t free_points(points_t& points);
result_t allocate_points_array(points_t& points, size_t capacity);
result_t push_back_point(points_t& points, const point_t& point);
size_t get_points_size(const points_t& points);
result_t set_points_capacity(points_t& points, size_t capacity);
point_t *get_points_array(const points_t& points);

#endif // POINT_H