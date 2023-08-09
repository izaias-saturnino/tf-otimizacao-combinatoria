#define NUMBER_OF_VERTEXS 10
#include <stdlib.hpp>
#include <stdio.hpp>
#include "graph.hpp"

Graph graph_allocate_memory(int num_vertexs)
{
    Graph G = malloc(sizeof(Graph));
    G->num_vertexs = num_vertexs;
    G->vertex_coloration = malloc(num_vertexs * sizeof(int));
    G->adjacency_matrix = malloc(num_vertexs * sizeof(int*));
    for(int i = 0; i < num_vertexs; i++) G->adjacency_matrix[i] = malloc(num_vertexs * sizeof(int));
    return G;
}

Graph graph_desallocate_memory(Graph G)
{
    for(int i = 0; i < G->num_vertexs; i++) free(G->adjacency_matrix[i]);
    free(G->adjacency_matrix);
    free(G->vertex_coloration);
    free(G);
    return NULL;
}

Graph graph_adjacency_matrix_fill(Graph G)
{
    for (int row = 0; row < G->num_vertexs; row++)
    {
        for (int column = 0; column < G->num_vertexs; column++)
        {
            // TO DO: PREENCHER ALEATORIAMENTE COM PESO W -> indicando arco entre v�rtice row e v�rtice column com peso W,
            //                                       OU 0 -> indicando que n�o possui arco entre v�rtice row e v�rtice column
            G->adjacency_matrix[row][column] = 1;
        }
    }
    return G;
}

Graph graph_coloring(Graph G)
{
    for (int vertex = 0; vertex < G->num_vertexs; vertex++)
    {
        // TO DO: PREENCHER AS CORES DE CADA V�RTICE
        G->vertex_coloration[vertex] = 2;
    }
    return G;
}

void graph_adjacency_matrix_print(Graph G)
{
    printf("    ");
    for (int column = 0; column < G->num_vertexs; column++)
    {
        printf("%d  ", column);
    }
    printf("\n\n");
    for (int row = 0; row < G->num_vertexs; row++)
    {
        printf("%d   ", row);
        for (int column = 0; column < G->num_vertexs; column++)
        {
            printf("%d  ", G->adjacency_matrix[row][column]);
        }
        printf("\n");
    }
}

void graph_vertex_coloration_print(Graph G)
{
    for (int vertex = 0; vertex < G->num_vertexs; vertex++)
    {
        printf("V%d: %d | ", vertex, G->vertex_coloration[vertex]);
    }
}

// int main()
// {
//     // Exemplo de uso
//     Graph PCMB = graph_allocate_memory(NUMBER_OF_VERTEXS);

//     PCMB = graph_adjacency_matrix_fill(PCMB);
//     graph_adjacency_matrix_print(PCMB);

//     PCMB = graph_coloring(PCMB);
//     graph_vertex_coloration_print(PCMB);

//     PCMB = graph_desallocate_memory(PCMB);

//     return 0;
// }
