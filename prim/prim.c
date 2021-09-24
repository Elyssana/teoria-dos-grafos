#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define true 1
#define false 0
typedef int bool;

typedef struct adjacencia
{
    int vert_orig;           //vertice de origem
    int vert_dest;           //vertice de destino
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
            printf("v%d(%d) ", ad->vert_dest, ad->peso);
            ad = ad->prox;
        }

        printf("\n");
    }
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

adjacencia *criAdj(int u, int v, int peso)
{
    adjacencia *aux = (adjacencia *)malloc(sizeof(adjacencia));
    aux->vert_orig = u;
    aux->vert_dest = v;
    aux->peso = peso;
    aux->prox = NULL;
    return aux;
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

    adjacencia *novo = criAdj(u, v, peso);
    novo->prox = g->adj[u].cab;
    g->adj[u].cab = novo;

    g->m++;

    return true;
}

/*************************************/

/*************************************/


grafo *prim(grafo *g, int v_ini){

 
    
    
}


int main()
{
    
    FILE *in = fopen("input.in", "r");
    if (!in)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(-1);
    }

    int n, u, v, p;

    printf("************ \n Observação: A numeração dos vértices inicía-se em 0.\n************\n\n");

    fscanf(in, "%d", &n); //nº de vertices

    grafo *g = criaGrafo(n);

    while (fscanf(in, "%d", &u) != EOF)
    {
        fscanf(in, "%d %d", &v, &p);
        criaArestas(g, u, v, p);
    }

    imprimeGrafo(g);
}