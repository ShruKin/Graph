#include <stdio.h>
#include <malloc.h>

struct node{
    int desti, weight;
    struct node *next;
};

struct list{
    struct node *head;
};

struct graph{
    struct list *adj;
    int V;
};

struct graph init_graph(struct graph g, int v){
    g.adj  = (struct list*)malloc(sizeof(struct list) * v);
    g.V = v;

    for(int i=0; i<v; i++)
        g.adj[i].head = NULL;

    return g;
}

struct graph addEdge(struct graph g, int src, int desti, int wt){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->desti = desti;
    newNode->weight = wt;
    newNode->next = NULL;

    if(g.adj == NULL){
        printf("Graph does not exists!");
        return g;
    }

    if(src < 0 || desti < 0 || src >= g.V || desti >= g.V){
        printf("Source/Destination vertex out of bounds");
        return g;
    }

    if(g.adj[src].head == NULL){
        g.adj[src].head = newNode;
    }

    else{
        struct node *ptr = g.adj[src].head;
        while(ptr->next != NULL){
            if(ptr->desti == desti){
                printf("Edge already exist!");
                return g;
            }
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }

    return g;
}

void print_adj_list(struct graph g){
    struct node *ptr;
    for(int i=0; i<g.V; i++){
        printf("%d:- ", i);

        ptr = g.adj[i].head;
        if(ptr == NULL){
            printf("NULL\n");
            continue;
        }

        while(ptr->next != NULL){
            printf("(%d, W%d) -> ", ptr->desti, ptr->weight);
            ptr = ptr->next;
        }
        printf("(%d, W%d) -> NULL\n", ptr->desti, ptr->weight);
    }
}

struct graph addVertex(struct graph g){
    if(g.V == 0)
        g.adj = (struct list *)malloc(sizeof(struct list) * ++g.V);

    else
        g.adj = (struct list *)realloc(g.adj, sizeof(struct list) * ++g.V);

    g.adj[g.V-1].head = NULL;

    return g;
}

int main(int argc, char const *argv[])
{
    struct graph g = {NULL, 0};
    int v;
    int ch, src, desti, wt;

    while(1){
        printf("MENU");
        printf("\n1. Initialise graph");
        printf("\n2. Display Adjacency adj");
        printf("\n3. Add Edge");
        printf("\n4. Add Vertex");
        printf("\n0. EXIT\n");

        printf("Enter choice: ");
        scanf("%d", &ch);
        printf("\n");

        switch(ch){
            case 0: exit(0);    break;

            case 1: 
                printf("Enter the no. of vertices: ");
                scanf("%d", &v);
                g = init_graph(g, v);
                break;

            case 2: print_adj_list(g); break;

            case 3: 
                printf("Enter source vertex: ");
                scanf("%d", &src);
                printf("Enter destination vertex: ");
                scanf("%d", &desti);
                printf("Enter weight: ");
                scanf("%d", &wt);
                g = addEdge(g, src, desti, wt);
                break;

            case 4: g = addVertex(g);   break;
        }

        printf("\n\n");
    }

    return 0;
}
