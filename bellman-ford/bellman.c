#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define true 1
#define false 0
typedef int bool;

typedef struct aresta
{
    int orig; //vertice de origem
    int dest; //vertice de destino
    int peso; //peso da aresta
    //struct adjacencia *prox; //proximo na lista de adj.
} aresta;

typedef struct grafo
{
    int n; //numero de vertices
    int m; //numero de arestas
    aresta *aresta;

} grafo;

bool insereAresta(grafo *g, int u, int v, int peso, int i)
{
    g->aresta[i].orig = u;
    g->aresta[i].dest = v;
    g->aresta[i].peso = peso;
}

grafo *criaGrafo(int n, int m)
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->n = n;
    g->m = m;
    g->aresta = (aresta *)malloc(m * sizeof(aresta));
    return g;
}

void imprimeGrafo(grafo *g)
{
    for (int i = 0; i < g->m; i++)
    {
        printf("d(%d,%d) -> %d\n", g->aresta[i].orig,
               g->aresta[i].dest,
               g->aresta[i].peso);
    }
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void bellman(grafo *g, int s)
{
    int n = g->n;
    int m = g->m;
    int dist[n];

    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[s] = 0;

    for (int i = 0; i <= n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = g->aresta[j].orig;
            int v = g->aresta[j].dest;
            int p = g->aresta[j].peso;

            if (dist[u] != INT_MAX)
            {
                dist[v] = min(dist[v], dist[u] + p);
            }
        }
    }

    for (int i = 0; i <= n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = g->aresta[j].orig;
            int v = g->aresta[j].dest;
            int p = g->aresta[j].peso;

            if (dist[u] != INT_MAX && dist[v] > dist[u] + p)
            {
                printf("Contém ciclo negativo!");

                return;
            }
        }
    }

    printf("Distancias a partir do vértice %d: \n", s);
    for (int i = 0; i < n; ++i)
    {
        printf("d(%d,%d) -> %d\n", s, i, dist[i]);
    }
}

int main()
{

    FILE *in = fopen("input.in", "r");
    if (!in)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(-1);
    }

    int n, m, s, u, v, p;

    printf("************ \n Observação: A numeração dos vértices inicía-se em 0.\n************\n\n");

    fscanf(in, "%d %d %d", &n, &m, &s); //nº de vertices, nº de arestas, vertice inicial

    grafo *g = criaGrafo(n, m);

    int i = 0;
    while (fscanf(in, "%d", &u) != EOF)
    {
        fscanf(in, "%d %d", &v, &p);
        insereAresta(g, u, v, p, i);
        i++;
    }

    //imprimeGrafo(g);

    bellman(g, s);
}
