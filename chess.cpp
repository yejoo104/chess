#include <iostream>
#include <vector>
#include <string>
using namespace std;

void printboard(vector <vector <int> > board);
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
  int row = board.size() - (grid[1] - '0');
  int col = grid[0] - 'A';

  cout << "Here are possible moves:\n";
  vector <vector <int> > possible = possiblemoves(board, row, col);
  for (int i = 0; i < possible.size(); i++)
  {
    cout << char(possible[i][1] + 'A') << board.size() - possible[i][0] << endl;
  }
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

vector <vector <int> > possiblemoves (vector <vector <int> > board, int row, int col)
{
  vector <vector <int> > possible;

  // Pawn (White)
  if (board[row][col] == 1)
  {
    if (row - 1 >= 0 && board[row - 1][col] == 0)
    {
      possible.push_back({row - 1, col});
      if (row - 2 >= 0 && board[row - 2][col] == 0) possible.push_back({row - 2, col});
    }
    if (col + 1 < board[0].size() && board[row - 1][col + 1] < 0) possible.push_back({row - 1, col + 1});
    if (col - 1 >= 0 && board[row - 1][col - 1] < 0) possible.push_back({row - 1, col - 1});
  }

  return possible;
}
