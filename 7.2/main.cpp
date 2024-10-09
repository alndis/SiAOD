#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int from;
    int to;
    int weight;
};

// Structure to represent a disjoint set
struct DisjointSet {
    vector<int> parent;
    vector<int> rank;

    DisjointSet(int size) : parent(size), rank(size, 0) {
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Graph {
private:
    vector<Edge> edges;
    vector<int> vertices;
    int size;

public:
    Graph(int size) : size(size) {}

    void addVertex(int value) {
        vertices.push_back(value);
    }

    void addEdge(int from, int to, int weight) {
        Edge e;
        e.from = from;
        e.to = to;
        e.weight = weight;
        edges.push_back(e);
    }

    void printGraph() {
        cout << "Original Graph:" << endl;
        cout << "Vertices: ";
        for (int vertex : vertices) {
            cout << vertex << " ";
        }
        cout << endl;
        cout << "Edges:" << endl;
        for (Edge e : edges) {
            cout << "(" << e.from << ", " << e.to << ") with weight " << e.weight << endl;
        }
    }

    void kruskalMST() {
        vector<Edge> mst;
        DisjointSet ds(size);

        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        for (Edge e : edges) {
            int rootFrom = ds.find(e.from);
            int rootTo = ds.find(e.to);

            if (rootFrom != rootTo) {
                mst.push_back(e);
                ds.unionSets(e.from, e.to);
            }
        }

        cout << "Minimum Spanning Tree:" << endl;
        for (Edge e : mst) {
            cout << "(" << e.from << ", " << e.to << ") with weight " << e.weight << endl;
        }
    }
};

int main() {
    Graph g(7);

    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);

    g.addEdge(1, 2, 20);
    g.addEdge(1, 7, 1);
    g.addEdge(1, 6, 23);
    g.addEdge(2, 7, 4);
    g.addEdge(2, 3, 15);
    g.addEdge(3, 7, 9);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 7, 16);
    g.addEdge(4, 5, 17);
    g.addEdge(5, 7, 25);
    g.addEdge(5, 6, 28);
    g.addEdge(6, 7, 36);

    g.printGraph();
    g.kruskalMST();

    cout<<"\n\n\n";

    int size;
    cout << "Enter the number of vertices: ";
    cin >> size;

    Graph g2(size);
    cout << "Enter the vertices (separated by spaces): ";
    for (int i = 0; i < size; i++) {
        int vertex;
        cin >> vertex;
        g2.addVertex(vertex);
    }

    int edgeCount;
    cout << "Enter the number of edges: ";
    cin >> edgeCount;

    cout << "Enter the edges (from, to, weight) separated by spaces:" << endl;
    for (int i = 0; i < edgeCount; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        g2.addEdge(from, to, weight);
    }

    g2.printGraph();
    g2.kruskalMST();

    return 0;
}