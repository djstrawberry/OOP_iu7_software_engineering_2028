#ifndef MODEL_DRAWER_H
#define MODEL_DRAWER_H

#include "model_processor.h"
#include "result.h"
#include <QGraphicsScene>

#define PEN_COLOR QColor(204, 36, 84)

typedef struct
{
    QGraphicsScene *scene;
    double width;
    double height;
} scene_t;

result_t draw_model(const model_t& model, const scene_t& scene);

#endif