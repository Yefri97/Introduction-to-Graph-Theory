#include <windows.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

void gotoxy(int x, int y){
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD dwPos = {x, y + 1};
  SetConsoleCursorPosition(hCon, dwPos);
}

void hideCursor() {
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  cci.dwSize = 2;
  cci.bVisible = false;
  SetConsoleCursorInfo(hCon, &cci);
}

struct node {
  int r1, c1, r2, c2;
  node() {}
  node(int _r1, int _c1, int _r2, int _c2) : r1(_r1), c1(_c1), r2(_r2), c2(_c2) {}
};

int mi1[10] = { 0,  1,  0, -1};
int mj1[10] = {-1,  0,  1,  0};
int mi2[10] = { 0,  1,  0, -1};
int mj2[10] = { 1,  0, -1,  0};

const int MX = 40, INF = -1;
int height, width, tr, tc;
int dist[MX + 10][MX + 10][MX + 10][MX + 10];
node path[MX + 10][MX + 10][MX + 10][MX + 10];
char board[MX + 10][MX + 10];

int breadthFirstSearch(node s, node t) {
  memset(dist, INF, sizeof dist); dist[s.r1][s.c1][s.r2][s.c2] = 0;
  queue<node> q; q.push(s);
  while (!q.empty()) {
    node u = q.front(); q.pop();
    if (u.r1 == t.r1 && u.r2 == t.r2 && u.c1 == t.c1 && u.c2 == t.c2) return dist[u.r1][u.c1][u.r2][u.c2];
    for (int i = 0; i < 4; i++) {
      node v = node(u.r1 + mi1[i], u.c1 + mj1[i], u.r2 + mi2[i], u.c2 + mj2[i]);
      if (v.r1 < 0 || v.r1 >= height || v.c1 < 0 || v.c1 >= width || board[v.r1][v.c1] == '#') {
        v.r1 = u.r1;
        v.c1 = u.c1;
      }
      if (v.r2 < 0 || v.r2 >= height || v.c2 < 0 || v.c2 >= width || board[v.r2][v.c2] == '#') {
        v.r2 = u.r2;
        v.c2 = u.c2;
      }
      if (dist[v.r1][v.c1][v.r2][v.c2] == INF) {
        dist[v.r1][v.c1][v.r2][v.c2] = dist[u.r1][u.c1][u.r2][u.c2] + 1;
        path[v.r1][v.c1][v.r2][v.c2] = u;
        q.push(v);
      }
    }
  }
  return -1;
}

int main() {

  ifstream cin("binaryLand.in");

  cin >> height >> width;

  int r1, c1, r2, c2, tr, tc;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      char c; cin >> c;
      if (c == '1') { r1 = i; c1 = j; }
      if (c == '2') { r2 = i; c2 = j; }
      if (c == '3') { tr = i; tc = j; }
      board[i][j] = c;
    }
  }

  node source = node(r1, c1, r2, c2), target = node(tr, tc, tr, tc);

  // Halla el camino mas corto del source al target mediante un BFS
  int lengthPath = breadthFirstSearch(source, target);

  // Reconstruyendo la respuesta
  node curr;
  curr = target;
  vector<node> ans(lengthPath);
  for (int i = lengthPath - 1; i >= 0; i--) {
    ans[i] = curr;
    curr = path[curr.r1][curr.c1][curr.r2][curr.c2];
  }

  cout << "La longitud del camino mas corto es " << lengthPath << endl;

  // Dibujando el tablero
  hideCursor();
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      gotoxy(j, i);
      cout << board[i][j];
    }
  }

  // Mostrando las respuesta
  gotoxy(source.c1, source.r1); cout << ".";
  gotoxy(source.c2, source.r2); cout << ".";
  curr = ans[0];
  gotoxy(curr.c1, curr.r1); cout << "1";
  gotoxy(curr.c2, curr.r2); cout << "2";
  for (int i = 0; i < ans.size(); i++) {
    gotoxy(curr.c1, curr.r1); cout << ".";
    gotoxy(curr.c2, curr.r2); cout << ".";
    curr = ans[i];
    gotoxy(curr.c1, curr.r1); cout << "1";
    gotoxy(curr.c2, curr.r2); cout << "2";
    Sleep(500);
  }
  gotoxy(target.c1, target.r1); cout << "3";

  gotoxy(0, height);
  getchar();

  return 0;
}
