#ifndef PROCESS_H
#define PROCESS_H

#include "result.h"
#include "model_processor.h"
#include "model_reader.h"
#include "model_drawer.h"
#include <QGraphicsScene>

using namespace std;

typedef enum
{
    LOAD_MODEL,
    DRAW_MODEL,
    ROTATE_MODEL,
    SCALE_MODEL,
    TRANSFER_MODEL
} request_type_t;

typedef struct
{
    request_type_t type;
    scene_t scene;
    union
    {
        const char *filename;
        rotate_params_t rotate_params;
        scale_params_t scale_params;
        transfer_params_t transfer_params;
    };
} request_t;

result_t process_request(const request_t& request);

#endif // PROCESS_H