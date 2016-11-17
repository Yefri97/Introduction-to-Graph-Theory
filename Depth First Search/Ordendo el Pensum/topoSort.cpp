#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

const int MX = 100, UNVISITED = -1, VISITED = 1;
vector< vector<int> > graph;
vector<int> dfs_num, ans;

int cont;
map<string, int> encode;
vector<string> decode;

void topologicalSort(int u) {
  dfs_num[u] = VISITED;
  for (int i = 0; i < graph[u].size(); i++) {
    int v = graph[u][i];
    if (dfs_num[v] == UNVISITED)
      topologicalSort(v);
  }
  ans.push_back(u);
}

int main() {

  ifstream cin("topoSort.in");

  cont = 0;
  graph.resize(MX);

  string a, b; char c;
  while (cin >> a >> c >> b) {
    
    int id_a, id_b;

    if (encode.count(a)) id_a = encode[a];
    else {
      encode[a] = id_a = cont++;
      decode.push_back(a);
    }
    
    if (encode.count(b)) id_b = encode[b];
    else {
      encode[b] = id_b = cont++;
      decode.push_back(b);
    }

    graph[id_b].push_back(id_a);

  }

  dfs_num.assign(cont, UNVISITED);

  for (int i = 0; i < cont; i++)
    if (dfs_num[i] == UNVISITED)
      topologicalSort(i);

  for (int i = 0; i < ans.size(); i++)
    cout << i + 1 << ". " << decode[ans[i]] << endl;

  return 0;
}