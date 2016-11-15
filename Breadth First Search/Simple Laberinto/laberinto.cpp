#include <windows.h>
#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <iostream>
#include <stdio.h>

using namespace std;

void gotoxy(int x, int y, char c){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
	cout << c;
}

struct state {
	int r, c;
	state() {}
	state(int _r, int _c) : r(_r), c(_c) {}
};

const int MX = 100, UNVISITED = -1;
int n, m;
state  path[MX + 10][MX + 10];
char board[MX + 10][MX + 10];

int mi[10] = {0, -1, 0, 1};
int mj[10] = {-1, 0, 1, 0};

int breadthFirstSearch(state s, state t) {
  vector< vector<int> > dist(n, vector<int>(m, UNVISITED)); dist[s.r][s.c] = 0;
  queue<state> q;	q.push(s);
  while (!q.empty()) {
	  state u = q.front(); q.pop();
	  for (int j = 0; j < 4; j++) {
			state v = state(u.r + mi[j], u.c + mj[j]);
			if (v.r < 0 || v.r >= n || v.c < 0 || v.c >= m) v = u;
			if (board[v.r][v.c] == '#') v = u;
			if (dist[v.r][v.c] == UNVISITED) {
				dist[v.r][v.c] = dist[u.r][u.c] + 1;
				path[v.r][v.c] = u;
				q.push(v);
			}
	  }
  }
  return dist[t.r][t.c];
}

int main() {
	ifstream cin("laberinto.txt");
	state source, target;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c; cin >> c;
			if (c == 'E') source = state(i, j);
			if (c == 'S') target = state(i, j);
			board[i][j] = c;
		}
	}

	int lengthPath = breadthFirstSearch(source, target);

	state curr;
	curr = target;
	vector<state> ans(lengthPath + 1);
	for (int i = lengthPath; i >= 1; i--) {
		ans[i] = curr;
		curr = path[curr.r][curr.c];
	}
	ans[0] = source;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			gotoxy(j, i, board[i][j]);

	cout << lengthPath << endl;

	curr = ans[1];
	for (int i = 1; i < ans.size(); i++) {
		gotoxy(curr.c, curr.r, '.');
		curr = ans[i];
		gotoxy(curr.c, curr.r, '*');
		Sleep(800);
	}

	gotoxy(0, n, ' ');
	getchar();

  return 0;
}
