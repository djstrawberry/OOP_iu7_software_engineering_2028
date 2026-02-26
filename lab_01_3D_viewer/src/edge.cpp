#include "edge.h"

size_t get_edges_size(const edges_t& edges)
{
    return edges.size;
}

size_t get_edges_capacity(const edges_t& edges)
{
    return edges.capacity;
}

void set_edges_capacity(edges_t& edges, size_t capacity)
{
    edges.capacity = capacity;
}

edge_t *get_edges_array(const edges_t& edges)
{
    return edges.edges;
}

void init_edges(edges_t& edges)
{
    edges.edges = nullptr;
    edges.size = 0;
    edges.capacity = 0;
}

void free_edges(edges_t& edges)
{
    if (edges.edges)
    {
        free(edges.edges);
    }

    edges.edges = nullptr;

    edges.size = 0;
    edges.capacity = 0;
}

result_t validate_edge(const edge_t& edge, size_t max_quantity)
{
    result_t ec = OK_CODE;

    if (edge.p1 < 0 || edge.p1 >= max_quantity || edge.p2 < 0 || edge.p2 >= max_quantity)
        ec = RANGE_ERROR_CODE;

    return ec;
}

result_t validate_edges(const edges_t& edges, size_t max_quantity)
{
    result_t ec = OK_CODE;

    for (size_t i = 0; (ec == OK_CODE) && (i < get_edges_size(edges)); ++i)
    {
        ec = validate_edge(get_edges_array(edges)[i], max_quantity);
    }

    return ec;
}

result_t allocate_edges_array(edges_t& edges, size_t capacity)
{
    result_t ec = OK_CODE;

    edges.edges = (edge_t *)malloc(sizeof(edge_t) * capacity);
    if (!edges.edges)
    {
        ec = MEMORY_ERROR_CODE;
    }
    else
    {
        edges.size = 0;
        edges.capacity = capacity;
    }

    return ec;
}

result_t push_back_edge(edges_t& edges, const edge_t& edge)
{
    result_t ec = OK_CODE;

    if (edges.size >= edges.capacity)
    {
        ec = RANGE_ERROR_CODE;
    }
    else
    {
        edges.edges[edges.size++] = edge;
    }

    return ec;
}