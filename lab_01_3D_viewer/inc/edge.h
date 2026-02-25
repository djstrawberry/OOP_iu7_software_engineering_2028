#ifndef EDGE_H
#define EDGE_H

#include "result.h"

typedef struct
{
    size_t p1;
    size_t p2;
} edge_t;

typedef struct
{
    edge_t *edges;
    size_t size;
    size_t capacity;
} edges_t;

result_t init_edges(edges_t& edges);
result_t free_edges(edges_t& edges);
result_t allocate_edges_array(edges_t& edges, size_t capacity);
result_t push_back_edge(edges_t& edges, const edge_t& edge);
size_t get_edges_size(const edges_t& edges);
size_t get_edges_capacity(const edges_t& edges);
result_t set_edges_capacity(edges_t& edges, size_t capacity);
edge_t *get_edges_array(const edges_t& edges);

#endif // EDGE_H