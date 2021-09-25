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
    int indice;
    int indHeap;
    int custo;
    int prev;
    bool visitado;
    adjacencia *cab_lista;
} vertice;

typedef struct grafo
{
    int n; //numero de vertices
    int m; //numero de arestas
    vertice *adj;

} grafo;

typedef struct HEAP
{
    int size;
    int max_size;
    vertice **vert;

} HEAP;
/*************************************/

int get_parent_index(int i)
{
    return (i / 2);
}

int get_cost(HEAP *h, int index)
{
    return ((vertice *)h->vert[index])->custo;
}

void swap_vertex(void **item_1, void **item_2)
{
    void *aux = *item_1;
    *item_1 = *item_2;
    *item_2 = aux;
}

void bubble_up(HEAP *heap, int i)
{
    if (i == 0)
    {
        return;
    }

    int parent_index = get_parent_index(i);
    if (heap->vert[parent_index]->custo > heap->vert[i]->custo)
    {
        heap->vert[parent_index]->indHeap = i;
        heap->vert[i]->indHeap = parent_index;
        swap_vertex((void *)&heap->vert[parent_index], (void *)&heap->vert[i]);
        bubble_up(heap, parent_index);
    }
}

void enqueue(HEAP *heap, vertice *newVertex)
{
    //printf("i %d\n", newVertex->indice);

    if (heap->size >= heap->max_size - 1)
    {
        printf("Heap overflow!\n");
    }
    else
    {

        heap->vert[++heap->size] = newVertex;
        newVertex->indHeap = heap->size;

        int key_index = heap->size;

        int parent_index = get_parent_index(key_index);

        while (parent_index >= 1 && get_cost(heap, key_index) < get_cost(heap, parent_index))
        {
            heap->vert[parent_index]->indHeap = key_index;
            heap->vert[key_index]->indHeap = parent_index;
            swap_vertex((void *)&heap->vert[parent_index], (void *)&heap->vert[key_index]);

            key_index = parent_index;

            parent_index = get_parent_index(key_index);
        }
    }
}

int get_left_index(int i)
{
    return (2 * i);
}

int get_right_index(int i)
{
    return (2 * i + 1);
}

void min_heapify(HEAP *heap, int i)
{
    int smallest;
    int left_index = get_left_index(i);
    int right_index = get_right_index(i);

    vertice *t = heap->vert[i];
    vertice *t_l = heap->vert[left_index];
    vertice *t_r = heap->vert[right_index];

    if (left_index <= heap->size && t_l->custo < t->custo)
    {
        smallest = left_index;
    }
    else
    {
        smallest = i;
    }

    vertice *t_s = heap->vert[smallest];

    if (right_index <= heap->size && t_r->custo < t_s->custo)
    {
        smallest = right_index;
        t_s = heap->vert[smallest];
    }

    if (t != t_s)
    {
        heap->vert[i]->indHeap = smallest;
        heap->vert[smallest]->indHeap = i;
        swap_vertex((void *)&heap->vert[i], (void *)&heap->vert[smallest]);
        min_heapify(heap, smallest);
    }
}

void *dequeue(HEAP *heap)
{
    if (!(heap->size))
    {
        printf("Heap underflow.\n");
        return NULL;
    }
    else
    {
        vertice *item = (vertice *)heap->vert[1];

        heap->vert[1] = heap->vert[heap->size];
        heap->vert[1]->indHeap = 1;

        heap->vert[heap->size] = NULL;

        heap->size -= 1;

        min_heapify(heap, 1);

        return item;
    }
}

HEAP *create_heap(int size, vertice *vertex_list)
{
    printf("VL %d \n", vertex_list[3].indice);
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));

    heap->vert = (vertice **)malloc((size + 1) * sizeof(vertice *));

    heap->size = 0;
    heap->max_size = size + 1;

    for (int i = 0; i < size; ++i)
    {
        enqueue(heap, &vertex_list[i]);

        //printf("voltoi %d\n", vertex_list[i].indice);
    }

    return heap;
}
/*************************************/

void imprimeGrafo(grafo *g)
{
    printf("vertices: %d. Arestas: %d.\n", g->n, g->m);

    for (int i = 0; i < g->n; i++)
    {
        printf("v%d: ", i);
        adjacencia *ad = g->adj[i].cab_lista;
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
        g->adj[i].indice = i;
        g->adj[i].custo = INT_MAX;
        g->adj[i].prev = -1;
        g->adj[i].visitado = false;
        g->adj[i].cab_lista = NULL;
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
    novo->prox = g->adj[u].cab_lista;
    g->adj[u].cab_lista = novo;

    novo = criAdj(v, u, peso);
    novo->prox = g->adj[v].cab_lista;
    g->adj[v].cab_lista = novo;

    g->m++;

    return true;
}

/* adjacencia *insereNaLista(adjacencia *cabLista, adjacencia *no)
{
    no->prox = cabLista;
    cabLista = no;
    return cabLista; 
}
*/

void print_MST(vertice **vertex, int size)
{
    int total_cost = 0;
    for (int i = 0; i < size; i++)
    {
        if (vertex[i]->indice != vertex[i]->prev)
        {
            printf("%lld %lld\n", vertex[i]->indice, vertex[i]->prev);
        }
        //total_cost += vertex[i]->cost;
    }
    printf("Total Cost: %d\n", total_cost);
}

grafo *prim(grafo *g, int v_ini)
{
    vertice **adj = g->adj;
    g->adj[v_ini].custo = 0;
    g->adj[v_ini].prev = v_ini;

    //printf("%d", g->adj[v_ini].custo);

    HEAP *heap = create_heap(g->n, adj);
    printf("tam mx %d\n ", heap->vert[1]->custo);

    while (heap->size > 0)
    {
        vertice *v = dequeue(heap);
        v->visitado = true;

        if (v->cab_lista == NULL)
        {
            printf("nuloo\n");
        }
        else
        {
            printf("%d "), v->cab_lista->vert_dest;
        }

        //printf("visitado %d ", v->cab_lista);
        adjacencia *no = v->cab_lista;

        //printf("v.id = %d ", v->indice);

        while (no)
        {
            int aux = no->vert_dest;
            printf("no ver_dest: %d \n", adj[++aux]->indice);
            //vertice *u = adj[no->vert_dest];
            //vertice *neighbor = adj[node->item];
            /*if (u->visitado == false)
            {
              //printf(" puts %d\n", u->custo);
                if (u->custo > no->peso)
                {  
                    u->custo = no->peso;
                    u->prev = v->indice;

                    bubble_up(heap, u->indHeap);
                }
            }*/

            no = no->prox;
        }
    }
    //printf printf("heap vert[1] %d", heap->vert[6]->indice);
    //print_MST(g->adj, g->n);
}

int main()
{

    FILE *in = fopen("input.in", "r");
    if (!in)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(-1);
    }

    int n, ini, u, v, p;

    printf("************ \n Observação: A numeração dos vértices inicía-se em 0.\n************\n\n");

    fscanf(in, "%d %d", &n, &ini); //nº de vertices e vértice de inicial

    grafo *g = criaGrafo(n);

    while (fscanf(in, "%d", &u) != EOF)
    {
        fscanf(in, "%d %d", &v, &p);
        criaArestas(g, u, v, p);
    }

    imprimeGrafo(g);

    prim(g, n);
}