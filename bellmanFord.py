class Graph: 

    def __init__(self, vertices): 
        self.V = vertices  
        self.graph = [] 

    def addEdge(self, u, v, w): 
        self.graph.append([u, v, w]) 
        
    def printArr(self, dist): 
        for i in range(self.V): 
            print(dist[i], end=" ")
    
    def BellmanFord(self, src): 

        dist = [float("Inf")] * self.V 
        dist[src] = 0

        for _ in range(self.V - 1): 
            for u, v, w in self.graph: 
                if dist[u] != float("Inf") and dist[u] + w < dist[v]: 
                        dist[v] = dist[u] + w 

        for u, v, w in self.graph: 
                if dist[u] != float("Inf") and dist[u] + w < dist[v]: 
                        print("Graph contains negative weight cycle") 
                        return
                        
        self.printArr(dist) 


V = int(input("Enter number of vertices: "))
mat = []

print("Enter graph:")

for _ in range(V):
    mat.append(list(map(int, input().split())))

g = Graph(V)

for i in range(V):
    for j in range(V):
        if mat[i][j] != 0:
            g.addEdge(i, j, mat[i][j])

g.BellmanFord(0) 
