#include "model_drawer.h"

result_t draw_model(const model_t& model, const scene_t& scene)
{
    result_t ec = OK_CODE;

    scene.scene->clear();

    point_t p1, p2;
    double x1, x2, y1, y2;
    edge_t current_edge;

    for (size_t i = 0; i < get_edges_size(model.edges); ++i)
    {
        current_edge = get_edges_array(model.edges)[i];

        p1 = get_points_array(model.points)[current_edge.p1];
        p2 = get_points_array(model.points)[current_edge.p2];

        x1 = p1.x + scene.width / 2;
        x2 = p2.x + scene.width / 2;
        y1 = p1.y + scene.height / 2;
        y2 = p2.y + scene.height / 2;

        scene.scene->addLine(x1, y1, x2, y2, QPen(QColor(204, 36, 84)));
    }

    return ec;
}   