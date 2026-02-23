#ifndef MODEL_H
#define MODEL_H

#include "result.h"
#include "point.h"
#include "edge.h"
#include <iostream>
#include <fstream>
#include <QGraphicsScene>

using namespace std;

typedef struct
{
    point_t center;
    edges_t edges;
    points_t points;
} model_t;

typedef struct
{
    QGraphicsScene *scene;
    double width;
    double height;
} scene_t;

typedef struct {
    double angle_x;
    double angle_y;
    double angle_z;
} rotate_params_t;

typedef struct {
    double kx;
    double ky;
    double kz;
} scale_params_t;

typedef struct {
    double dx;
    double dy;
    double dz;
} transfer_params_t;

result_t init_model(model_t& model);
result_t free_model(model_t& model);
result_t load_model(model_t& model, const char *filename);
result_t draw_model(model_t& model, scene_t& scene);
result_t scale_model(model_t& model, scale_params_t& params);
result_t rotate_model(model_t& model, rotate_params_t& params);
result_t transfer_model(model_t& model, transfer_params_t& params);

#endif // MODEL_H