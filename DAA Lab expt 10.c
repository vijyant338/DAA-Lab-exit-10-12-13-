//Name : Vijyant
//  Roll no : 25/DA/063

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a weighted edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a directed graph
struct Graph {
    int V, E;          // V -> number of vertices, E -> number of edges
    struct Edge* edge; // Array of edges
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// A utility function to print the calculated shortest distances
void printArr(int dist[], int n) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INT_MAX)
            printf("%d \t\t INFINITY\n", i);
        else
            printf("%d \t\t %d\n", i, dist[i]);
    }
}

// The main function that finds shortest paths from src to all other
// vertices using Bellman-Ford algorithm and detects negative-weight cycles
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int* dist = (int*)malloc(V * sizeof(int));

    // Step 1: Initialize distances from src to all other vertices as INFINITY
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times.
    // A simple shortest path from src to any other vertex can have at most |V| - 1 edges.
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles.
    // If we get a shorter path in the |V|-th iteration, then there is a negative-weight cycle.
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("\nGraph contains a negative-weight cycle!\n");
            free(dist);
            return;
        }
    }

    printf("\nNo negative-weight cycle detected. Shortest distances from source:\n");
    printArr(dist, V);

    free(dist);
}

int main() {
    int V = 5; // Number of vertices in graph
    int E = 8; // Number of edges in graph
    struct Graph* graph = createGraph(V, E);

    // Adding directed edges (src, dest, weight)
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = -1;

    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 4;

    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;

    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 2;

    graph->edge[4].src = 1;
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 2;

    graph->edge[5].src = 3;
    graph->edge[5].dest = 2;
    graph->edge[5].weight = 5;

    graph->edge[6].src = 3;
    graph->edge[6].dest = 1;
    graph->edge[6].weight = 1;

    graph->edge[7].src = 4;
    graph->edge[7].dest = 3;
    graph->edge[7].weight = -3;

    // Run Bellman-Ford algorithm starting from source vertex 0
    BellmanFord(graph, 0);

    // Free allocated memory
    free(graph->edge);
    free(graph);

    return 0;
}