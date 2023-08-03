#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct
{
    int num_vertexs;
    int*  vertex_coloration;
    int** adjacency_matrix;
}*Graph;

Graph graph_allocate_memory(int num_vertexs);
Graph graph_desallocate_memory(Graph G);

Graph graph_adjacency_matrix_fill(Graph G);
void graph_adjacency_matrix_print(Graph G);

Graph graph_coloring(Graph G);
void graph_vertex_coloration_print(Graph G);

#endif // GRAPH_H_INCLUDED
