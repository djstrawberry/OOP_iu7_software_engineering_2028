#include "edge.h"

size_t get_edges_size(const edges_t& edges)
{
    return edges.size;
}

size_t get_edges_capacity(const edges_t& edges)
{
    return edges.capacity;
}

result_t set_edges_capacity(edges_t& edges, size_t capacity)
{
    result_t ec = OK_CODE;

    edges.capacity = capacity;

    return ec;
}

edge_t *get_edges_array(const edges_t& edges)
{
    return edges.edges;
}

result_t init_edges(edges_t& edges)
{
    result_t ec = OK_CODE;

    edges.edges = nullptr;
    edges.size = 0;
    edges.capacity = 0;

    return ec;                          
}

result_t free_edges(edges_t& edges)
{
    result_t ec = OK_CODE;

    if (edges.edges)
    {
        free(edges.edges);
    }

    edges.edges = nullptr;

    edges.size = 0;
    edges.capacity = 0;

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