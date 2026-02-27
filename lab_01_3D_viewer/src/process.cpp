#include "process.h"

result_t process_request(const request_t& request)
{
    result_t ec = OK_CODE;
    static model_t model;

    switch(request.type)
    {
        case LOAD_MODEL:
            ec = load_model(model, request.filename);
            break;
        
        case DRAW_MODEL:
            ec = draw_model(model, request.scene);
            break;

        case SCALE_MODEL:
            ec = scale_model(model, request.scale_params);
            break;

        case ROTATE_MODEL:
            ec = rotate_model(model, request.rotate_params);
            break;

        case TRANSFER_MODEL:
            ec = transfer_model(model, request.transfer_params);
            break;

        default:
            ec = UNKNOWN_ERROR_CODE;
            break;
    }

    return ec;
}
