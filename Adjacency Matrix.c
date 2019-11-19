#include<stdio.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

void create_graph(int**,int);
int count_edges(int**,int);
void display(int**,int);
void check_graph(int**,int);
void complete(int**,int);
void even_odd(int**,int);

int main()
{ 
	int n,e,**adj,i,j;
	printf("Enter number of vertices : ");
    scanf("%d", &n);

   	adj=(int**)calloc(n,sizeof(int));
	for( i=0;i<n;i++)
		adj[i]=(int*)calloc(n,sizeof(int));
		
    int choice;
    int node, origin, destin;
    int cycle;
    
    while (1) {
    	printf("0. Create a graph \n");
        printf("1.BFS\n");
        printf("2.DFS\n");
        printf("3.Display\n");
        printf("4.Count edges \n");
        printf("6.Check graph\n");
        printf("7.Check for complete graph\n");
         printf("8.Count even and odd degree vertices\n");
        // printf(" 9. detect cycle in graph\n");
        printf("5.Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice) 
	   	{
        	case 0:
        		create_graph(adj,n);
        		break;
        	case 3:
            	display(adj,n);
            	break;
       		case 4:
           		e= count_edges(adj,n);
		  		break;	
     		case 5:
            	exit(0); 
     		case 6:
     			check_graph(adj,n);
				break;
			case 7:
				complete(adj,n);
				break;
			case 8:
             	even_odd(adj,n);
				break;
	
     		default:
            	printf("Wrong choice\n");
            	break;
        }
    }
    getch();
}
 
void create_graph(int **adj,int n)
{

    int i, max_edges, origin, destin;
    max_edges = n * (n - 1);
 
    for (i = 0; i < max_edges; i++)
    {
        printf("Enter edge %d . Enter( 0 0 ) to quit : ", i);
        scanf("%d %d", &origin, &destin);
        if ((origin == 0) && (destin == 0))
            break;
        if (origin > n || destin > n || origin<=0 || destin <=0)
	    {
            printf("Invalid edge!\n");
            i--;
        } 
	   	else
            adj[origin-1][destin-1] = 1;
    }
}
 
 void display(int **adj,int n) 
 {
    int i, j;
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++)
            printf("%4d", adj[i][j]);
        printf("\n");
    }
}
int count_edges(int **adj,int n)
{
	printf("\n The number of vertices are %d",n);
	int i,j,e=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(adj[i][j]==1)
			e=e+1;
		}
	}
	printf("\n The number of edges are %d \n",e);
	return e;
}
void check_graph(int **adj,int n)
{
	int i,edge,sum=0,d;
	for(i=0;i<n;i++)
	{
		printf("\n Enter the degree for node %d  :",i);
		scanf("%d",&d);
		sum=sum+d;	
	}
	edge=count_edges(adj,n);
	if(sum== (2*edge))
		printf("\n Graph is valid \n");
	else
	   printf("\n Graph is invalid \n");
}
void complete(int **adj,int n)
{
	int e;
	e=count_edges(adj,n);
	if(e==(n*(n-1)/2))
		printf("\n graph is complete \n");
	else
		printf("\n graph is incomplete \n");
}
void even_odd(int **adj,int n)
{
	int i,j,even=0,odd=0,deg=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(adj[i][j]==1)
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