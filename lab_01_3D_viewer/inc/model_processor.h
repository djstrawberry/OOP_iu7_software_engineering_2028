#ifndef MODEL_H
#define MODEL_H

#include "result.h"
#include "point.h"
#include "edge.h"

using namespace std;

typedef struct
{
    point_t center;
    edges_t edges;
    points_t points;
} model_t;

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

void init_model(model_t& model);
void free_model(model_t& model);
result_t validate_model(const model_t& model);
result_t scale_model(model_t& model, const scale_params_t& params);
result_t rotate_model(model_t& model, const rotate_params_t& params);
result_t transfer_model(model_t& model, const transfer_params_t& params);

#endif // MODEL_H