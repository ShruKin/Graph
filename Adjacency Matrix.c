#include<stdio.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>


int n;
void create_graph();
//void insert_node();
void display();
//void delete_node(int);
int main() { //some functions dont work for now
	int n,**adj,i;
	printf("Enter number of nodes : ");
    scanf("%d", &n);
    adj=(int**)malloc(n*sizeof(int));
	for( i=0;i<n;i++)
		{
		adj[i]=(int*)malloc(n*sizeof(int));
		}
    int choice;
    int node, origin, destin;
    
    while (1) {
    	   printf("0. Create a graph \n");
        printf("1.Insert a node\n");
        printf("2.Delete a node\n");
        printf("3.Display\n");
        printf("4.Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
        	case 0:
        		create_graph(adj,n);
        		break;
      /* case 1:
            insert_node();
            break;
        case 2:
            printf("Enter a node to be deleted : ");
            scanf("%d", &node);
            delete_node(node);
            break;*/
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
 
void create_graph(int adj[n][n],int n)
{
    int i, max_edges, origin, destin;
    max_edges = n * (n - 1);
 
    for (i = 1; i <= max_edges; i++)
     {
        printf("Enter edge %d . Enter( 0 0 ) to quit : ", i);
        scanf("%d %d", &origin, &destin);
        if ((origin == 0) && (destin == 0))
            break;
        if (origin > n || destin > n || origin <= 0 || destin <= 0)
	    {
            printf("Invalid edge!\n");
            i--;
          } 
	   else
            adj[origin][destin] = 1;
    }
}
 
 void display(int adj[n][n],int n) 
 {
    int i, j;
    for (i = 1; i <= n; i++) 
    {
        for (j = 1; j <= n; j++)
            printf("%4d", adj[i][j]);
     
        printf("\n");
    }
}

