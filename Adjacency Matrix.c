#include<stdio.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

int **init_adj_mat(int);
void add_edge(int **adj, int n, int src, int desti, int wt);
void create_graph(int**,int);
int count_edges(int**,int);
void display(int**,int);
void check_graph(int**,int);
void complete(int**,int);
void even_odd(int**,int);

int main()
{ 
	int n, e, **adj, i, j, src, desti, wt, choice;
	// printf("Enter number of vertices : ");
    // scanf("%d", &n);

   	// adj=(int**)calloc(n,sizeof(int));
	// for( i=0;i<n;i++)
	// 	adj[i]=(int*)calloc(n,sizeof(int));
		
    // int choice;
    // int node, origin, destin;
    // int cycle;
    
    while (1) {
    	printf("1. Initialize the graph \n");
    	printf("2. Create graph edgewise \n");
    	printf("3. Add edge \n");
        printf("4. Display\n");
        // printf("5. BFS\n");
        // printf("6. DFS\n");
        printf("7. Count edges \n");
        printf("8. Check graph\n");
        printf("9. Check for complete graph\n");
        printf("10. Count even and odd degree vertices\n");
        // printf(" 9. detect cycle in graph\n");
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

        	case 2:	create_graph(adj,n);	break;

			case 3:
				printf("Enter source vertex: ");
                scanf("%d", &src);
                printf("Enter destination vertex: ");
                scanf("%d", &desti);
                printf("Enter weight: ");
                scanf("%d", &wt);
                add_edge(adj, n, src, desti, wt);
                break;

        	case 4:	display(adj,n);			break;

       		case 7:	e = count_edges(adj,n);	break;	

     		case 8:	check_graph(adj,n);	break;

			case 9:	complete(adj,n);	break;

			case 10:	even_odd(adj,n);	break;
	
     		default:
            	printf("Wrong choice\n");
            	break;
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
	if(src > n || desti > n || src < 0 || desti < 0){
		printf("Source/Destination vertices are out of bounds");
		return;
	}

	if(wt == 0)	//	if the graph is unweigted
		wt = 1;	//	adj matrix should have 1

	adj[src][desti] = wt;
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

        else if(origin > n || destin > n || origin < 0 || destin < 0){
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