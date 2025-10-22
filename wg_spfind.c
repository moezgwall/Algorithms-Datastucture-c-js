#include <stdio.h>
#include <stdbool.h>

#define NVERTICES 5
#define INFINITY 99999

int minimalDistance(int dist[] ,bool visited[]){
    int mindis = INFINITY;
    int minidx = -1;

    for (int v=0;v < NVERTICES;v++){
        if (!visited[v] && dist[v] < mindis){
            mindis = dist[v];
            minidx = v;
        }
    }

    return minidx;

}

void dijkstra(int graph[NVERTICES][NVERTICES], int source){
    int dist[NVERTICES];
    bool visited[NVERTICES] = {false};

    for (int i = 0; i < NVERTICES; i++ ){
        dist[i] = INFINITY;
    }
    dist[source] = 0;


    for (int i = 0; i < NVERTICES-1;i++){
        int d = minimalDistance(dist,visited);
        visited[d] = true;

        for (int j = 0; j < NVERTICES;j++){
            if (!visited[j] && graph[d][j] && dist[d] +graph[d][j] < dist[j]){
                dist[j] = dist[d] + graph[d][j];
            }
        }
    }

    for (int i = 0; i < NVERTICES;i++){
        printf(" vertex: (%d) distance from source : (%d) \n",i,dist[i]);
    }


}



int main(){
    // init graph 
     int graph[NVERTICES][NVERTICES] = {
        {0, 4, 0, 0, 8},
        {4, 0, 8, 0, 0},
        {0, 8, 0, 7, 2},
        {0, 0, 7, 0, 9},
        {8, 0, 2, 9, 0}
    };

dijkstra(graph, 0);



}