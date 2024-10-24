/*
Rafael Rocha Maciel
Mestrado em ciência e tecnologia da computação (UNIFEI)
Data Structures and Algorithms - Topological sorting
*/

/**
 * 
 * 
 * @file graph.cpp
 * @brief Implements a Directed Acyclic Graph (DAG) and performs topological sorting using Depth-First Search (DFS).
 *
 * This program simulates the order of dressing using a directed acyclic graph (DAG). Each vertex in the graph 
 * represents an article of clothing, and an edge between two vertices (u, v) indicates that clothing item u 
 * must be worn before v. The graph is traversed using DFS to find a topological order of dressing.
 *
 * The vertices are mapped as follows:
 * 0 -> undershorts
 * 1 -> socks
 * 2 -> shoes
 * 3 -> pants
 * 4 -> watch
 * 5 -> belt
 * 6 -> shirt
 * 7 -> tie
 * 8 -> jacket
 *
 * The output of the program displays the order in which to put on the clothes, ensuring that prerequisites are met.
 *
 * Classes:
 * - Graph: Represents a graph using an adjacency list and provides methods for adding edges, 
 *   performing DFS, and finding the topological sorting.
 *
 * Methods:
 * - Graph::Graph(): Initializes the graph, marking all vertices as not visited.
 * - void Graph::addEdge(int u, int v): Adds a directed edge from vertex u to vertex v.
 * - void Graph::dfs(int source): Recursive method to perform DFS from a given vertex and populate 
 *   the topological order list.
 * - void Graph::dfs_explore(): Iterates through all vertices, performing DFS on unvisited nodes.
 * - void Graph::topologicalSorting(): Generates the topological order, mapping vertices to their corresponding 
 *   clothing items and printing the sorted order.
 *
 * Example usage:
 * ```
 * Graph g;
 * g.addEdge(0, 3); // Add an edge from 'undershorts' to 'pants'
 * g.addEdge(0, 2); // Add an edge from 'undershorts' to 'shoes'
 * // Additional edges...
 * g.topologicalSorting();
 * ```
 *
 * Output:
 * ```
 * Order to wear clothes:
 * shirt -> tie -> watch -> socks -> undershorts -> pants -> belt -> jacket -> shoes
 * ```
 */


#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#define VERT 9

class Graph{
    private:
        std::vector<int> adj[VERT];  // Adjacency list for storing edges
        bool visited[VERT];          // Array to keep track of visited nodes during DFS
        std::list<int> topological_list;  // List to store the topological order

    public:
        Graph();                     // Constructor to initialize the graph
        void addEdge(int, int);      // Adds a directed edge from u to v
        void dfs(int);               // Recursive DFS function to explore the graph
        void dfs_explore();          // Initiates DFS from all unvisited nodes
        void topologicalSorting();   // Performs topological sorting and prints the order
};

Graph::Graph(){
    for(int i = 0; i < VERT; i++)
        visited[i] = false;          // Initialize all vertices as not visited
}

void Graph::addEdge(int u, int v){
    adj[u].push_back(v);             // Add v to the adjacency list of u
}

void Graph::dfs(int source){
    visited[source] = true;          // Mark the current node as visited
    for(int v : adj[source]){        // Explore all adjacent nodes
        if(!visited[v])
            dfs(v);                  // Recursively visit unvisited adjacent nodes
    }
    topological_list.push_front(source);  // Add the node to the front of the list to maintain topological order
}

void Graph::dfs_explore(){
    for(int i = 0; i < VERT; i++)
        if(!visited[i]) dfs(i);      // Start DFS for each unvisited vertex
}

void Graph::topologicalSorting(){
    bool aux_print = false;          // Helper variable for formatting output with " -> "
    std::unordered_map<int, std::string> matchingElements = {
        {0, "undershorts"}, {1, "socks"}, {2, "shoes"},
        {3, "pants"}, {4, "watch"}, {5, "belt"},
        {6, "shirt"}, {7, "tie"}, {8, "jacket"}
    };

    dfs_explore();                   // Perform DFS and fill topological_list

    std::cout << "Order to wear clothes:\n";
    for(int elem : topological_list){
        if(aux_print) 
            std::cout << " -> " << matchingElements[elem];  // Print element with separator
        else{
            std::cout << matchingElements[elem];  // Print the first element without separator
            aux_print = true;  // Set flag to true to use separator for subsequent elements
        }
    }
}

int main(){
    Graph g;
    // Add directed edges based on dependency constraints

    g.addEdge(0, 3); // undershorts -> pants
    g.addEdge(0, 2); // undershorts -> shoes
    g.addEdge(1, 2); // socks -> shoes
    g.addEdge(3, 2); // pants -> shoes
    g.addEdge(3, 5); // pants -> belt
    g.addEdge(6, 5); // shirt -> belt
    g.addEdge(6, 7); // shirt -> tie
    g.addEdge(5, 8); // belt -> jacket
    g.addEdge(7, 8); // tie -> jacket

    g.topologicalSorting();  // Output the order in which to wear clothes
    return 0;
}