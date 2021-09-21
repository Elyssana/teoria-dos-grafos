#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define true 1
#define false 0
typedef int bool;

typedef struct adjacencia
{
    int vert;                //vertice onde a aresta chega
    int peso;                //peso da aresta
    struct adjacencia *prox; //proximo na lista de adj.
} adjacencia;

typedef struct vertice
{
    int item;
    adjacencia *cab;
} vertice;

typedef struct grafo
{
    int n; //numero de vertices
    int m; //numero de arestas
    vertice *adj;

} grafo;

void imprimeGrafo(grafo *g)
{
    printf("vertices: %d. Arestas: %d.\n", g->n, g->m);

    for (int i = 0; i < g->n; i++)
    {
        printf("v%d: ", i);
        adjacencia *ad = g->adj[i].cab;
        while (ad)
        {
            printf("v%d(%d) ", ad->vert, ad->peso);
            ad = ad->prox;
        }

        printf("\n");
    }
}

adjacencia *criAdj(int v, int peso)
{
    adjacencia *aux = (adjacencia *)malloc(sizeof(adjacencia));
    aux->vert = v;
    aux->peso = peso;
    aux->prox = NULL;
    return aux;
}

grafo *criaGrafo(int n)
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->n = n;
    g->m = 0;
    g->adj = (vertice *)malloc(n * sizeof(vertice));
    for (int i = 0; i < n; i++)
    {
        g->adj[i].cab = NULL;
    }
    return g;
}

bool criaArestas(grafo *g, int u, int v, int peso)
{
    if (u < 0 || u > g->n)
    {
        return false;
    }
    if (v < 0 || v > g->n)
    {
        return false;
    }

    //adjacencia de v em u
    adjacencia *novo = criAdj(v, peso);
    novo->prox = g->adj[u].cab;
    g->adj[u].cab = novo;

    g->m++;

    return true;
}

int main()
{
    int v = 6;

    grafo *g = criaGrafo(v);

    criaArestas(g, 0, 1, 5);
    criaArestas(g, 0, 2, 4);
    criaArestas(g, 0, 3, 2);
    criaArestas(g, 0, 5, 6);
    criaArestas(g, 1, 3, 1);
    criaArestas(g, 1, 4, 7);
    criaArestas(g, 2, 4, 6);
    criaArestas(g, 3, 5, 1);

    imprimeGrafo(g);

    //kruskal(g)
}