#include "model_drawer.h"

result_t draw_line(const points_t& points, const edge_t& edge, const scene_t& scene, const QColor& color)
{
    result_t ec = OK_CODE;

    point_t* points_array = get_points_array(points);

    if (!points_array)
    {
        ec = NULLPTR_ERROR_CODE;
    }
    else
    {
        point_t point_1 = points_array[edge.p1];
        point_t point_2 = points_array[edge.p2];

        double cx = scene.width / 2;
        double cy = scene.height / 2;

        double x1 = cx + point_1.x;
        double y1 = cy - point_1.y;
        double x2 = cx + point_2.x;
        double y2 = cy - point_2.y; 

        scene.scene->addLine(x1, y1, x2, y2, QPen(color));
    }

    return ec;
}

result_t draw_model(const model_t& model, const scene_t& scene)
{
    result_t ec = OK_CODE;

    if (!scene.scene)
    {
        ec = NULLPTR_ERROR_CODE;
    }
    else if (validate_model(model) == OK_CODE)
    {
        scene.scene->clear();

        edge_t *edges_array = get_edges_array(model.edges);
        if (!edges_array)
        {
            ec = NULLPTR_ERROR_CODE;
        }
        else
        {
            for (size_t i = 0; i < get_edges_size(model.edges); ++i)
            {
                ec = draw_line(model.points, edges_array[i], scene, PEN_COLOR);
            }
        }
    }

    return ec;
}   