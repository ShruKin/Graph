#include<stdio.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lds.c"

int **init_adj_mat(int);
void add_edge(int **adj, int n, int src, int desti, int wt);
// void add_vertex(int **adj, int n);
void read_from_file(int **adj, int n, char filename[]);
void create_graph(int**,int);
int count_edges(int**,int);
void display(int**,int);
void check_graph(int**,int);
void complete(int**,int);
void even_odd(int**,int);
void BFS(int **adj, int n, int start);
void DFS(int **adj, int n, int start);
int is_cyclic(int **adj, int n);
int calc_out_degree(int **adj, int n, int v);
int calc_in_degree(int **adj, int n, int v);
void topological_sort(int **adj, int n);

int main()
{ 
	int n, e, **adj, i, j, src, desti, wt, choice;
	char filename[100];
    
    while (1) {
    	printf("1. Initialize the graph \n");
    	printf("2. Create graph edgewise \n");
    	printf("3. Read graph from a csv file \n");
    	printf("4. Add edge \n");
    	// printf("5. Add Vertex \n");
        printf("6. Display Adjacency Matrix\n");
        printf("7. BFS\n");
        printf("8. DFS\n");
        printf("9. Count edges \n");
        printf("10. Check graph\n");
        printf("11. Check for complete graph\n");
        printf("12. Count even and odd degree vertices\n");
        printf("13. Detect cycle in graph\n");
        printf("14. Topological Sort\n");
        printf("0.EXIT\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);
		printf("\n");

        switch (choice) 
	   	{
			case 0:	exit(0);	break;

			case 1: 
				printf("Enter number of vertices : ");
				scanf("%d", &n);
				adj = init_adj_mat(n);
				break;

        	case 2:	create_graph(adj, n);	break;

			case 3: 
				// printf("Enter filename: ");
				// scanf("%s", filename);
				strcpy(filename, "adjmats\\hackerearth_topo_sort.csv");
				read_from_file(adj, n, filename);

				break;

			case 4:
				printf("Enter source vertex: ");
                scanf("%d", &src);
                printf("Enter destination vertex: ");
                scanf("%d", &desti);
                printf("Enter weight: ");
                scanf("%d", &wt);
                add_edge(adj, n, src, desti, wt);
                break;

			// case 5:
			// 	add_vertex(adj, n);
			// 	n++;
			// 	break;

        	case 6:	display(adj,n);			break;

			case 7: 
				printf("Enter source vertex: ");
                scanf("%d", &src);
                BFS(adj, n, src); 
                break;

			case 8:
				printf("Enter source vertex: ");
                scanf("%d", &src);
                DFS(adj, n, src); 
                break;

       		case 9:	e = count_edges(adj,n);	break;	

     		case 10:	check_graph(adj,n);	break;

			case 11:	complete(adj,n);	break;

			case 12:	even_odd(adj,n);	break;

			case 13:	
				if(is_cyclic(adj, n))
                    printf("The graph has a cycle!");
                else
                    printf("The graph doesnt have a cycle!");
                break;

			case 14:	topological_sort(adj, n);	break; 
	
     		default:	printf("Wrong choice\n");	break;
        }
		printf("\n\n");
    }
    getch();
}

int **init_adj_mat(int n){
	int **adj=(int**)calloc(n,sizeof(int));
	for(int i=0; i<n; i++)
		adj[i]=(int*)calloc(n,sizeof(int));

	return adj;
}

void add_edge(int **adj, int n, int src, int desti, int wt){
	if(src >= n || desti >= n || src < 0 || desti < 0){
		printf("Source/Destination vertices are out of bounds");
		return;
	}

	if(wt == 0)	//	if the graph is unweigted
		wt = 1;	//	adj matrix should have 1

	adj[src][desti] = wt;
}

// void add_vertex(int **adj, int n){
// 	n++;
// 	printf("%d", n);
// 	adj = (int **)realloc(adj, n*sizeof(int));
// 	for(int i=0; i<n; i++)
// 		adj[i]=(int*)realloc(adj[i], n*sizeof(int));

// 	for(int i=0; i<n; i++)
// 		adj[i][n-1] = 0;

// 	for(int i=0; i<n; i++)
// 		adj[n-1][i] = 0;
// }

void read_from_file(int **adj, int n, char filename[]){
	FILE *fileptr;
	fileptr = fopen(filename, "r");
	char *record;
	int j;
	for(int i=0; i<n; i++){
		char line[1024];
		fgets(line, 1024, fileptr);

		record = strtok(line,",");
		j=0;
		while(record != NULL){
			adj[i][j++] = atoi(record) ;
			record = strtok(NULL,",");
		}
	}
}
 
void create_graph(int **adj, int n)
{
    int i, max_edges, origin, destin, wt;
    max_edges = n * (n - 1);

	printf("Enter edges in source, destination, weight format(space seperated)\n");
	printf("Enter (-1 -1 -1) to quit entering more edges\n");
    for (i = 0; i < max_edges; i++)
    {
        printf("Enter edge %d: ", i);
        scanf("%d %d %d", &origin, &destin, &wt);

        if((origin == -1) || (destin == -1) || (wt == -1))	//	any one -1, and break
            break;

        else if(origin >= n || destin >= n || origin < 0 || destin < 0){
            printf("Invalid edge!\n");
            i--;
        } 

	   	else
            adj[origin][destin] = wt;
    }
}
 
void display(int **adj, int n) 
{
    int i, j;
	printf("    ");
	for(int i=0; i<n; i++)
		printf("[%d] ", i);
	printf("\n");

    for (i = 0; i < n; i++) 
    {
		printf("[%d] ", i);
        for (j = 0; j < n; j++)
            printf("%2d  ", adj[i][j]);
        printf("\n");
    }
}

int count_edges(int **adj, int n)
{
	printf("\n The number of vertices are %d",n);
	int i,j,e=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(adj[i][j])
			e=e+1;
		}
	}
	printf("\n The number of edges are %d \n",e);
	return e;
}

void check_graph(int **adj, int n)
{
	int i,edge,sum=0,d;
	for(i=0;i<n;i++)
	{
		printf("\n Enter the degree for node %d  :",i);
		scanf("%d",&d);
		sum=sum+d;	
	}
	edge=count_edges(adj,n);
	if(sum == (2*edge))
		printf("\n Graph is valid \n");
	else
	   printf("\n Graph is invalid \n");
}

void complete(int **adj, int n)
{
	int e;
	e=count_edges(adj,n);
	if(e==(n*(n-1)/2))
		printf("\n graph is complete \n");
	else
		printf("\n graph is incomplete \n");
}

void even_odd(int **adj, int n)
{
	int i,j,even=0,odd=0,deg=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(adj[i][j])
			deg++;
		}
		if(deg%2==0)
		 	even++;
		else 
		 	odd++;
	}
	printf("\n number of even degree vertices %d",even);
	printf("\n number of odd degree vertices %d",odd);
}

void BFS(int **adj, int n, int start){
	if(start < 0 || start >= n){
        printf("Source vertex out of bounds");
        return;
    }

	int *visited;
    visited = (int *)calloc(n, sizeof(int));

	struct Queue q = {NULL, NULL};

    visited[start] = 1;
    enqueue(&q, start);

    int curr;
	while(!is_queueEmpty(q)){
		curr = dequeue(&q);
        printf("%d ", curr);

		for (int i = 0; i < n; i++){
			if((adj[curr][i]) && (visited[i] == 0)){
				visited[i] = 1;
				enqueue(&q, i);
			}
		}
	}
}

void DFS(int **adj, int n, int start){
	if(start < 0 || start >= n){
        printf("Source vertex out of bounds");
        return;
    }

	int *visited;
    visited = (int *)calloc(n, sizeof(int));

	struct Stack s = {NULL};

    visited[start] = 1;
    push(&s, start);
	printf("%d ", start);

    int curr;
	while(!is_stackEmpty(s)){
		curr = pop(&s);

		for (int i = 0; i < n; i++){
			if((adj[curr][i]) && (visited[i] == 0)){
				visited[i] = 1;
				push(&s, i);
				printf("%d ", i);
			}
		}
	}
}

int is_cyclic(int **adj, int n){
	int *visited, curr;
    visited = (int *)calloc(n, sizeof(int));

    struct Stack s = {NULL};

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)    //  clearing the visited array for a new DFS traversal
            visited[j] = 0;
        while(!is_stackEmpty(s))    //  clearing stack for each new DFS traversal
            pop(&s);

		/*  DFS traversal begins here   */
        visited[i] = 1;
        push(&s, i);

		while(!is_stackEmpty(s)){
			curr = pop(&s);

			for (int i = 0; i < n; i++){
				if(adj[curr][i]){
					if(visited[i]) //  this node is already visited?
                    	return 1;   //  then a cycle is present
					else if(!visited[i]){   //  this node isnt visited?
						visited[i] = 1;    //  visit the node once
						push(&s, i);
					}
				}
			}
		}
	}
	return 0;
}

int calc_out_degree(int **adj, int n, int v){
	int outdegree = 0;
	for(int i=0; i<n; i++){
		if(adj[v][i])
			outdegree++;
	}
	return outdegree;
}

int calc_in_degree(int **adj, int n, int v){
	int indegree = 0;
	for(int i=0; i<n; i++){
		if(adj[i][v])
			indegree++;
	}
	return indegree;
}

void topological_sort(int **adj, int n){
	struct Queue q = {NULL, NULL};
    int curr, *visited, *indegree;

	visited = (int*)calloc(n, sizeof(int));
    indegree = (int*)calloc(n, sizeof(int));

	for(int i=0; i<n; i++){
        indegree[i] = calc_in_degree(adj, n, i);
        if(indegree[i] == 0)    //  enqueueing all 0 indegrees, as traversal must from
            enqueue(&q, i);     //  a node with zero indegree
    }

	while(!is_queueEmpty(q)){
        curr = dequeue(&q);
        printf("%d ", curr);

        for(int i=0; i<n; i++){
        	if((adj[curr][i]) && (!visited[i])){
                indegree[i]--;     //  removing edge when visited
                if(indegree[i] == 0){
                    enqueue(&q, i);
                    visited[i] = 1;
                }
            }
        }
    }
}