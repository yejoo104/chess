#include <iostream>
#include <vector>
#include <string>
using namespace std;

void printboard(vector <vector <int> > board);
vector <int> stringtocoord (string input);
vector <char> coordtostring(vector <int> coord);
vector <vector <int> > possiblemoves (vector <vector <int> > board, int row, int col);

int main(int argc, char** argv)
{
  vector <vector <int> > board { {-2, -3, -4, -5, -6, -4, -3, -2},
                                 {-1, -1, -1, -1, -1, -1, -1, -1},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {1, 1, 1, 1, 1, 1, 1, 1},
                                 {2, 3, 4, 5, 6, 4, 3, 2} };
  printboard(board);

  cout << "Select piece to move (ex. A1) ";
  string grid;
  cin >> grid;
  vector <int> coord = stringtocoord(grid);
  int row = coord[0];
  int col = coord[1];

  cout << "Here are possible moves:\n";
  vector <vector <int> > possible = possiblemoves(board, row, col);
  for (int i = 0; i < possible.size(); i++)
  {
    vector<char> coord = coordtostring(possible[i]);
    cout << coord[0] << coord[1] << " ";
  }
  cout << endl;
}

void printboard(vector <vector <int> > board)
{
  for (int i = 0; i < board[0].size(); i++) cout << char('A' + i) << "\t";
  cout << endl;
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == 0) cout << "_";
      if (abs(board[i][j]) == 1) cout << "p";
      if (abs(board[i][j]) == 2) cout << "r";
      if (abs(board[i][j]) == 3) cout << "k";
      if (abs(board[i][j]) == 4) cout << "b";
      if (abs(board[i][j]) == 5) cout << "q";
      if (abs(board[i][j]) == 6) cout << "k";
      if (board[i][j] > 0) cout << "(w)";
      if (board[i][j] < 0) cout << "(b)";
      cout << "\t";
    }
    cout << board.size() - i << endl;
  }
}

vector <int> stringtocoord (string input)
{
  int row = 8 - (input[1] - '0');
  int col = input[0] - 'A';
  return {row, col};
}

vector <char> coordtostring(vector <int> coord)
{
  vector<char> s(2);
  s[0] = char(coord[1] + 'A');
  s[1] = 8 - coord[0] + '0';
  return s;
}

vector <vector <int> > possiblemoves (vector <vector <int> > board, int row, int col)
{
  vector <vector <int> > possible;

  // Pawn
  if (abs(board[row][col]) == 1)
  {
    // Direction of movement (based on whether white or black)
    int dir = board[row][col] > 0 ? -1 : 1;

    // If there is no piece directly in front
    if (row + dir >= 0 && board[row + dir][col] == 0)
    {
      possible.push_back({row + dir, col});

      // If there is no piece two steps in front
      if (row + 2 * dir >= 0 && board[row + 2 * dir][col] == 0)
        possible.push_back({row + 2 * dir, col});
    }

    // If there are opponent pieces to the front diagonal
    if (col + 1 < board[0].size() && board[row][col] * board[row + dir][col + 1] < 0) possible.push_back({row + dir, col + 1});
    if (col - 1 >= 0 && board[row][col] * board[row + dir][col - 1] < 0) possible.push_back({row + dir, col - 1});
  }

  // Rook and Queen: sides
  if (abs(board[row][col]) == 2 || abs(board[row][col]) == 5)
  {
    // Sides
    int xdir[4] = {1, -1, 0, 0};
    int ydir[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      while (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
             board[x][y] == 0)
      {
        possible.push_back({x, y});
        x += xdir[i];
        y += ydir[i];
      }
      if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
          board[row][col] * board[x][y] < 0) possible.push_back({x, y});
    }
  }

  // Knight
  if (abs(board[row][col]) == 3)
  {
    int xdir[8] = {2, 2, 1, 1, -1, -1, -2, -2};
    int ydir[8] = {1, -1, 2, -2, 2, -2, 1, -1};

    for (int i = 0; i < 8; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
          board[row][col] * board[x][y] <= 0)
        possible.push_back({x, y});
    }
  }

  // Bishop and Queen: Diagonals
  if (abs(board[row][col]) == 4 || abs(board[row][col]) == 5)
  {
    int xdir[4] = {1, 1, -1, -1};
    int ydir[4] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      while (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
             board[x][y] == 0)
      {
        possible.push_back({x, y});
        x += xdir[i];
        y += ydir[i];
      }
      if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
          board[row][col] * board[x][y] < 0) possible.push_back({x, y});
    }
  }

  // King
  if (abs(board[row][col]) == 6)
  {
    int xdir[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int ydir[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
          board[row][col] * board[x][y] <= 0) possible.push_back({x, y});
    }
  }

  return possible;
}
