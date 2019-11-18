#include<stdio.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
int n;
void create_graph(int**,int);

void display(int**,int);
int main()
{ 
	int n,**adj,i,j;
	printf("Enter number of nodes : ");
    scanf("%d", &n);
   adj=(int**)calloc(n,sizeof(int));
	for( i=0;i<n;i++)
		{
		adj[i]=(int*)calloc(n,sizeof(int));
		}
    int choice;
    int node, origin, destin;
    
    while (1) {
    	   printf("0. Create a graph \n");
        printf("1.BFS\n");
        printf("2.DFS\n");
        printf("3.Display\n");
        printf("4.Exit\n");
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
            exit(0); 
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

