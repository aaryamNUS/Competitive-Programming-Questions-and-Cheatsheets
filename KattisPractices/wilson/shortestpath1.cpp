#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <list>
#define INF 0x3f3f3f3f

using namespace std;

class Graph {
private:
    int V;
    typedef pair<int, int> vertex;
    list<pair<int, int> > *adj_weight;

    vector<int> *distances;
public:
    Graph (int size) {
        V = size;
        adj_weight = new list<vertex> [V]; // array of lists
    }
    
    void makePair (int u, int v, int w) {
        // u = vertice 1
        // v = vertice 2
        // w = weight
        //adj_weight[v].push_back(make_pair(w, u)); // Commented out to make it uni directional
        adj_weight[u].push_back(make_pair(w, v));
    }
    
    void printWeights () {
        for (int i = 0; i < V; i++) {
            if (!adj_weight[i].empty()) {
                printf("Node: %d\n", i);
                printf("----------------------\n");
                for (auto d = adj_weight[i].begin(); d != adj_weight[i].end() ; d++) {
                    printf("%d %d\n", d->second, d->first);
                }
                printf("----------------------\n");
            }
            
        }
    }
    
    void generateShortestPath (int src) {
        // Note: We will indirectly find the shortest distance to all the nodes in the process
        
        priority_queue< vertex, vector <vertex> , greater<vertex> > pq;
        distances = new vector<int> (V, INF);
        //vector<int> dist(V, INF); // Initialise all vertices distances to infinite
        pq.push(make_pair(0, src)); // 0 weight
        distances->at(src) = 0;

        
        while (!pq.empty())
        {
            
            int u = pq.top().second;
            pq.pop();
            
            // 'i' is used to get all adjacent vertices of a vertex
            for (auto i = adj_weight[u].begin(); i != adj_weight[u].end(); ++i)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = i->second;
                int weight = i->first;
                
                //  If there is shorter path to v through u.
                
                // Extremely crucial
                if (distances->at(v) > distances->at(u) + weight)
                {
                    // Updating distance of v
                    distances->at(v) = distances->at(u) + weight;
                    pq.push(make_pair(distances->at(v), v));
                }
            }
        }
    }
    
    int returnDist (int src, int dest) {
        if (distances->at(dest) == INF)
            return -1;
        else
            return distances->at(dest);
    }
    
};


int main () {
    int n, m ,q, s, first = 0;

    do {
        scanf("%d %d %d %d", &n, &m, &q, &s);
        if (!n) continue; // stop the program
        Graph myGraph(n);
        
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            myGraph.makePair(u, v, w);
        }
        
        myGraph.generateShortestPath(s);
        if (first)
            printf("\n");

        for (int i = 0; i < q; i++) {
            int target;
            scanf("%d", &target);
            if (myGraph.returnDist(s, target) != -1)
                printf("%d\n", myGraph.returnDist(s, target));
            else
                printf("Impossible\n");
        }
        first = 1;
    }while (n);
    

}
