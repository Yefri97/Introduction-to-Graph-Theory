#include <windows.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <stdio.h>

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
  int i, j;
  node() {}
  node(int _i, int _j) : i(_i), j(_j) {}
};

const int MX = 100, UNVISITED = -1;
int height, width;
node path[MX + 10][MX + 10];
char board[MX + 10][MX + 10];

int movi[10] = {0, -1, 0, 1};
int movj[10] = {-1, 0, 1, 0};

int breadthFirstSearch(node s, node t) {  // BFS
  // Inicializamos todos los nodos como NO VISITADOS, excepto el Source
  vector< vector<int> > dist(height, vector<int>(width, UNVISITED)); dist[s.i][s.j] = 0;
  queue<node> q; q.push(s); // Creamos la cola, y la inicializamos con Source
  while (!q.empty()) { // Mientras mi cola no este vacia
    node u = q.front(); q.pop(); // Extraemos el nodo U del frente de la cola
    for (int k = 0; k < 4; k++) { // Exploramos todos sus vecinos
      node v = node(u.i + movi[k], u.j + movj[k]);  // Vecino V
      if (v.i < 0 || v.i >= height || v.j < 0 || v.j >= width) v = u;
      if (board[v.i][v.j] == '#') v = u;
      if (dist[v.i][v.j] == UNVISITED) {  // Si ese nodo no ha sido visitado
        dist[v.i][v.j] = dist[u.i][u.j] + 1;  // Lo marcamos como visitado
        path[v.i][v.j] = u; // Guardamos el padre para reconstruir la respuesta
        q.push(v);  // Insertamos el nodo a la cola
      }
    }
  }
  return dist[t.i][t.j]; // Retornamos la distancia mas corta al Target
}

int main() {

  // Leyendo de archivo
  ifstream cin("laberinto2.in");

  // Crea el estado inicial y el objetivo
  node source, target;

  // Lee las dimensiones del tablero
  cin >> height >> width;

  // Lee el tablero
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      char c; cin >> c;
      if (c == 'E') source = node(i, j);
      if (c == 'S') target = node(i, j);
      board[i][j] = c;
    }
  }

  // Halla el camino mas corto del source al target mediante un BFS
  int lengthPath = breadthFirstSearch(source, target);

  // Reconstruyendo la respuesta
  node curr;
  curr = target;
  vector<node> ans(lengthPath);
  for (int i = lengthPath - 1; i >= 0; i--) {
    ans[i] = curr;
    curr = path[curr.i][curr.j];
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
  curr = ans[0];
  gotoxy(curr.j, curr.i); cout << "*";
  for (int i = 0; i < ans.size(); i++) {
    gotoxy(curr.j, curr.i); cout << ".";
    curr = ans[i];
    gotoxy(curr.j, curr.i); cout << "*";
    Sleep(200);
  }

  gotoxy(0, height);
  getchar();

  return 0;
}
