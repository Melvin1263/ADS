#ifndef GRAPH_H
#define GRAPH_H

#include <deque>
#include <map>
#include <queue>
#include <iostream>
#include "P4_graphnode.h"

class UnionFind {
    int cnt;
    std::vector<int> id, sz;
public:
    // Create an empty union find data structure with n isolated sets.
    UnionFind(int n) {
        cnt = n; 
        id.resize(n); 
        sz.resize(n);

        for (int i = 0; i<n; i++)  
            id[i] = i, sz[i] = 0;
    }
    ~UnionFind() {  }

    // Return the id of component corresponding to object p.
    int find(int p) {
        int root = p;
        while (root != id[root])    root = id[root];
        while (p != root) { int newp = id[p]; id[p] = root; p = newp; }
        return root;
    }

    // Replace sets containing x and y with their union.
    void merge(int x, int y) {
        int i = find(x); int j = find(y); if (i == j) return;
        // make smaller root point to larger one
        if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
        else { id[j] = i, sz[i] += sz[j]; }
        cnt--;
    }

    // Are objects x and y in the same set?
    bool connected(int x, int y) { return find(x) == find(y); }

    // Return the number of disjoint sets.
    int count() { return cnt; }
};

class Graph
{
public:
    Graph();
    ~Graph();

    GraphNode* GetNodeByKey(int key);
    void setAllUnvisited();
    bool checkVisited();
    bool init(std::string path);
    bool print();

    //Implement this:
    bool depthSearchRek(int startKey);
    bool breadthSearchIter(int startKey);
    //Or this
    bool depthSearchIter(int startKey);
    bool breadthSearchRek(int startKey);

    //This must be done by you
    int getId(GraphNode* x) const;
    double prim(int startKey);

    std::vector<GraphNode::edge> getEdges();
    double kruskal();

    //They might be helpful
    int _anzKnoten;
    bool _ger, _gew;
    std::vector<GraphNode*> _nodes;
};

#endif // GRAPH_H
