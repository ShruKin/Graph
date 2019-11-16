#include <stdio.h>
#include <malloc.h>
#include "lds.c"

struct gnode{
    int desti, weight;
    struct gnode *next;
};

struct list{
    struct gnode *head;
};

struct graph{
    struct list *adj;
    int V;
};

struct graph init_graph(struct graph g, int v);
struct graph addEdge(struct graph g, int src, int desti, int wt);
void print_adj_list(struct graph g);
struct graph addVertex(struct graph g);
int count_edges(struct graph g);
int calc_out_degree(struct graph g, int vertex);
int calc_in_degree(struct graph g, int vertex);
int is_complete(struct graph g);

struct graph init_graph(struct graph g, int v){
    g.adj  = (struct list*)malloc(sizeof(struct list) * v);
    g.V = v;

    for(int i=0; i<v; i++)
        g.adj[i].head = NULL;

    return g;
}

struct graph addEdge(struct graph g, int src, int desti, int wt){
    struct gnode *newNode = (struct gnode*)malloc(sizeof(struct gnode));
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
        struct gnode *ptr = g.adj[src].head;
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
    struct gnode *ptr;
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

int count_edges(struct graph g){
    int e = 0;
    struct gnode *ptr;
    for(int i=0; i<g.V; i++){
        ptr = g.adj[i].head;

        while(ptr != NULL){
            e++;
            ptr = ptr->next;
        }
    }

    return e;
}

int calc_out_degree(struct graph g, int vertex){
    int d = 0;
    struct gnode *ptr = g.adj[vertex].head;
    while(ptr != NULL){
        d++;
        ptr = ptr->next;
    }
    return d;
}

int calc_in_degree(struct graph g, int vertex){
    int d = 0;
    struct gnode *ptr;
    for(int i=0; i<g.V; i++){
        ptr = g.adj[i].head;

        while(ptr != NULL){
            if(ptr->desti == vertex)
                d++;
            ptr = ptr->next;
        }
    } 
    return d;
}

// TODO: Think of a programatic approach over mathematical
int is_complete(struct graph g){
    if(g.adj == NULL)
        return 0;   //  false

    else if(count_edges(g) == (g.V*(g.V-1))/2)
        return 1;   //  true
    
    else
        return 0;   //  false
}

void BFS(struct graph g, int start){
    if(g.adj == NULL){
        printf("Graph does not exists!");
        return;
    }

    if(start < 0 || start >= g.V){
        printf("Source vertex out of bounds");
        return;
    }

    int *visited;
    visited = (int *)calloc(g.V, sizeof(int));

    struct Queue q = {NULL, NULL};

    visited[start] = 1;
    enqueue(&q, start);

    int curr;
    struct gnode *ptr;
    while(!is_queueEmpty(q)){
        curr = dequeue(&q);
        printf("%d ", curr);

        ptr = g.adj[curr].head;
        while(ptr != NULL){
            if(!visited[ptr->desti]){
                visited[ptr->desti] = 1;
                enqueue(&q, ptr->desti);
            }
            ptr = ptr->next;
        }
    }
}

void DFS(struct graph g, int start){
    if(g.adj == NULL){
        printf("Graph does not exists!");
        return;
    }

    if(start < 0 || start >= g.V){
        printf("Source vertex out of bounds");
        return;
    }

    int *visited;
    visited = (int *)calloc(g.V, sizeof(int));

    struct Stack s = {NULL};

    visited[start] = 1;
    push(&s, start);

    int curr;
    struct gnode *ptr;
    while(!is_stackEmpty(s)){
        curr = pop(&s);
        printf("%d ", curr);

        ptr = g.adj[curr].head;
        while(ptr != NULL){
            if(!visited[ptr->desti]){
                visited[ptr->desti] = 1;
                push(&s, ptr->desti);
            }
            ptr = ptr->next;
        }
    }
}

int is_cyclic(struct graph g){
    if(g.adj == NULL){
        printf("Graph does not exists!");
        return 0;
    }

    struct gnode *ptr;
    int *visited, curr;
    visited = (int *)calloc(g.V, sizeof(int));

    struct Stack s = {NULL};

    for(int i=0; i<g.V; i++){
        for(int j=0; j<g.V; j++)    //  clearing the visited array for a new DFS traversal
            visited[j] = 0;
        while(!is_stackEmpty(s))    //  clearing stack for each new DFS traversal
            pop(&s);

        /*  DFS traversal begins here   */
        visited[i] = 1;
        push(&s, i);

        while(!is_stackEmpty(s)){
            curr = pop(&s);
            ptr = g.adj[curr].head;
            while(ptr != NULL){
                if(visited[ptr->desti]) //  this node is already visited?
                    return 1;   //  then a cycle is present
                if(!visited[ptr->desti]){   //  this node isnt visited?
                    visited[ptr->desti] = 1;    //  visit the node once
                    push(&s, ptr->desti);
                }
                ptr = ptr->next;
            }
        }
    }
    return 0;
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
        printf("\n5. Count Vertex");
        printf("\n6. Count Edge");
        printf("\n7. Degree Sequence");
        printf("\n8. Check whether the graph is complete");
        printf("\n9. BFS traversal");
        printf("\n10. DFS traversal");
        printf("\n11. Is the graph cyclic");
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

            case 5: printf("There are %d no. of vertices present!", g.V);   break;

            case 6: printf("There are %d no. of vertices present!", count_edges(g));    break;

            case 7: 
                for(int i=0; i<g.V; i++){
                    int indeg = calc_in_degree(g, i);
                    int outdeg = calc_out_degree(g, i);
                    printf("%d:- In degree: %d\tOut degree: %d\tTotal Degree: %d\n", i,  indeg, outdeg, indeg+outdeg);
                }
                break;

            case 8:
                if(is_complete(g))
                    printf("The graph is complete");
                else
                    printf("The graph is not complete");
                break;

            case 9:
                printf("Enter source vertex: ");
                scanf("%d", &src);
                BFS(g, src); 
                break;

            case 10:
                printf("Enter source vertex: ");
                scanf("%d", &src);
                DFS(g, src); 
                break;

            case 11:
                if(is_cyclic(g))
                    printf("The graph has a cycle!");
                else
                    printf("The graph doesnt have a cycle!");
                break;
        }

        printf("\n\n");
    }

    return 0;
}
