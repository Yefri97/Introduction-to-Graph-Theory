#include <windows.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

typedef pair<int, int> ii;

const int MX = 1000, UNVISITED = -1;
ii path[MX + 10];

int breadthFirstSearch(int s, int t) {
  vector<int> dist(MX, UNVISITED); dist[s] = 0;
  queue<int> q; q.push(s);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (u == t) return dist[u];
    int neighbor[10] = {u * 2, u * 3, u / 2, u / 3, u + 7, u - 7};
    for (int i = 0; i < 6; i++) {
      int v = neighbor[i];
      if (v < 0 || v >= MX) continue;
      if (dist[v] == UNVISITED) {
        dist[v] = dist[u] + 1;
        path[v] = ii(u, i);
        q.push(v);
      }
    }
  }
}

int main() {

  ifstream cin("minOpe.in");

  vector<string> vs;
  vs.push_back(" * 2");
  vs.push_back(" * 3");
  vs.push_back(" / 2");
  vs.push_back(" / 3");
  vs.push_back(" + 7");
  vs.push_back(" - 7");

  int a, b;
  while (cin >> a >> b) {

    int numOperations = breadthFirstSearch(a, b);

    cout << a << " -> " << b << endl;
    cout << "El minimo numero de operaciones es " << numOperations << endl;

    vector<ii> ans(numOperations);
    ii curr;
    ans[numOperations - 1] = curr = path[b];
    for (int i = numOperations - 2; i >= 0; i--) {
      curr = path[curr.first];
      ans[i] = curr;
    }
    ans.push_back(ii(b, -1));

    for (int i = 0; i < ans.size() - 1; i++)
      cout << ans[i].first << vs[ans[i].second] << " = " << ans[i + 1].first << endl;

  }

  return 0;
}
