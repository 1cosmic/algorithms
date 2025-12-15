#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <ranges>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

vector<int> component, used;

template<typename T>
void print_array(vector<T> array) {
    cout << "[ ";
    for (auto n : array)
        cout << n << ' ';
    cout << ']' << endl;
}

void dfs_components(auto G, int v, int num) {
    component[v] = num;
    for (auto u: G[v])
        if (!component[u])
            dfs_components(G, u, num);
}

auto components_of_graph(auto G) {
    auto num = 0;
    component.clear();
    component.resize(G.size(), 0);

    for (auto v = 0; v < G.size(); v++) {
        if (!component[v])
            dfs_components(G, v, ++num);
        cout << "for v=" << v << " is component=" << component[v] << endl;
    }

    return num, component;
}


bool dfs_cycle(auto G, int v) {
    if (used[v]) return 1;
    used[v] = 1;
    // cout << "for v=" << v << "set used." << endl;

    for (auto u: G[v])
        if (u != v) return dfs_cycle(G, u);

    return 0;
}


auto has_cycle(auto G) {
    used.clear();
    used.resize(G.size(), 0);
    int r = 0;

    for (auto v = 0; v < G.size(); v++) {

        if (!used[v]) {
            r = dfs_cycle(G, v);
            // cout << "for v=" << v << " is cycle=" << r << endl;
            if (r) break;
        }
    }
    return r;
}


bool is_tree(auto G, int start) {
    deque <int> q;
    q.push_back(start);

    auto r = 1;
    auto cur = 0;

    while(!q.empty() and r) {
        cur = q.front();
        q.pop_front();
        for (auto v: q) if (cur == v) {
            // cout << "finded v in itself: " << v << endl;
            r = 0; break;
        }
        for (auto v: G[cur]) {
            if (v != cur) q.push_back(v);
        }
    }

    return r;
}


vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    
    vector<int> distances(n, 1e7);
    distances[start] = 0;
    
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> pq;
    
    pq.push(make_pair(0, start));
    
    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();
        
        if (current_distance > distances[current_vertex]) {
            continue;
        }
        
        for (int i = 0; i < graph[current_vertex].size(); i++) {
            int neighbor = graph[current_vertex][i].first;
            int weight = graph[current_vertex][i].second;
            int new_distance = current_distance + weight;
            
            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                pq.push(make_pair(new_distance, neighbor));
            }
        }
    }
    
    return distances;
}

void dijkstra() {
    int V1 = 4;
    vector<vector<pair<int, int>>> graph1(V1);
    
    // Build graph: pair(neighbor, weight)
    graph1[0].push_back(make_pair(1, 4));
    graph1[0].push_back(make_pair(2, 1));
    graph1[1].push_back(make_pair(3, 1));
    graph1[2].push_back(make_pair(1, 2));
    graph1[2].push_back(make_pair(3, 5));
    
    vector<int> dist1 = dijkstra(graph1, 0);
    print_array(dist1);
}

bool dfs_colors(auto G, int v, int color=-1) {
    used[v] = color;
    
    int r = 1;

    for (auto u: G[v]) {
        if (!used[u]) {
            r = dfs_colors(G, u, -color);
        } 
        if (used[u] != -color or !r)
        {
            // cout << "Graph isn't bipartite" << endl;
            r = 0;
        }
    }
    return r;
}

bool is_bipartite(auto G) {
    used.clear(); used.resize(G.size());
    
    int r = 1;
    for (auto v = 0; v < G.size(); v++) {
        if (!used[v]) r = dfs_colors(G, v);
        if (!r) return 0;
    }

    return r;
}


int main() {
    cout << "Homeworks of graphs." << endl;
    cout << "Created by Michael Kolobakhin" << endl << endl;

    int r;

    vector<vector<int>> cycled = {
        {},           // vertex 0 (isolated)
        {2, 3},       // vertex 1 connected to 2, 3
        {1, 3},       // vertex 2 connected to 1, 3
        {1, 2},       // vertex 3 connected to 1, 2
        {6, 7},       // vertex 4 connected to 6, 7
        {6, 7},       // vertex 5 connected to 6, 7
        {4, 5, 7},    // vertex 6 connected to 4, 5, 7
        {4, 5, 6},    // vertex 7 connected to 4, 5, 6
        {11},         // vertex 8 connected to 11
        {10, 11},     // vertex 9 connected to 10, 11
        {9},          // vertex 10 connected to 9
        {8, 9}        // vertex 11 connected to 8, 9
    };
    vector<vector<int>> tree = {
        {1},
        {2},
        {3},
        {4},
        {5},
        {}
    };

    cout << "1 and 2) Components or colors of graph 'cycled': " << endl;
    components_of_graph(cycled);
    cout << endl << endl;

    cout << "3) and 4) Search of cycle if graph 'cycled': " << endl;
    r = has_cycle(cycled);
    cout << "cycled?: " << r << endl;
    r = is_tree(cycled, 1);
    cout << "is tree?: " << r << endl;
    cout << endl;

    cout << "3) and 4) Search of cycle if graph 'tree': " << endl;
    r = has_cycle(tree);
    cout << "cycled?: " << r << endl;
    r = is_tree(tree, 0);
    cout << "is tree?: " << r << endl;
    cout << endl << endl;

    // see in aggregator-func
    cout << "5) Test dijsktra Simple graph with 4 vertices from root=0:" << endl;
    dijkstra(); cout << endl << endl;

    r = is_bipartite(cycled);
    cout << "6) Is bipartite 'cycled': " << r << endl;
    r = is_bipartite(tree);
    cout << "6) Is bipartite 'tree': " << r << endl;


    cout << endl;
    return 0;
}