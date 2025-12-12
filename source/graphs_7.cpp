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
            cout << "for v=" << v << " is cycle=" << r << endl;
            if (r) break;
        }
    }
    return r;
}


int main() {
    cout << "Homeworks of graphs." << endl;
    cout << "Created by Michael Kolobakhin" << endl << endl;

    vector<vector<int>> G = {
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
    cout << "1 and 2) Components or colors of graph: " << endl;
    components_of_graph(G);
    cout << endl << endl;

    cout << "3) Search of cycle if graph H: " << endl;
    vector<vector<int>> H = {
        {1},
        {2},
        {3},
        {4},
        {5},
        {}
    };
    has_cycle(H);
    cout << endl;

    cout << "3) Search of cycle if graph G: " << endl;
    has_cycle(G);



    cout << endl;
    return 0;
}