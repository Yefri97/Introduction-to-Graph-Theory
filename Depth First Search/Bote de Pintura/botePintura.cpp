#include <windows.h>
#include <vector>
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

const int MX = 100;
int height, width;
char board[MX + 10][MX + 10];

int movi[10] = {0, -1, 0, 1};
int movj[10] = {-1, 0, 1, 0};

int floodFill(int r, int c, char c1, char c2) {
  if (r < 0 || r >= height || c < 0 || c >= width) return 0;
  if (board[r][c] != c1) return 0;
  int ans = 1;
  board[r][c] = c2;
  gotoxy(c, r); cout << c2;
  Sleep(200);
  for (int k = 0; k < 4; k++) 
    ans += floodFill(r + movi[k], c + movj[k], c1, c2);
  return ans;
}

int main() {

  ifstream cin("botePintura.in");

  cin >> height >> width;
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      cin >> board[i][j];

  hideCursor();

  for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) {
    gotoxy(j, i); cout << board[i][j];
  }

  int qi, qj; cin >> qi >> qj;
  char c; cin >> c;
  int numCellsPrinted = floodFill(qi, qj, board[qi][qj], c);

  gotoxy(0, height);

  cout << "Se pintaron " << numCellsPrinted << " celdas." << endl;

  return 0;
}