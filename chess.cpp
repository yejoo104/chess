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
                                 {0, 2, 0, 0, 0, 0, 0, 0},
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
    cout << char(possible[i][1] + 'A') << board.size() - possible[i][0] << " ";
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
      if (row + 2 * dir >= 0 && board[row + 2 * dir][col] == 0) possible.push_back({row + 2 * dir, col});
    }

    // If there are opponent pieces to the front diagonal
    if (col + 1 < board[0].size() && board[row][col] * board[row + dir][col + 1] < 0) possible.push_back({row + dir, col + 1});
    if (col - 1 >= 0 && board[row][col] * board[row + dir][col - 1] < 0) possible.push_back({row + dir, col - 1});
  }

  // Rook
  if (abs(board[row][col]) == 2)
  {
    int movement = 1;

    // Moves to the Left
    while (col - movement >= 0 && board[row][col - movement] == 0)
    {
      possible.push_back({row, col - movement});
      movement++;
    }
    if (col - movement >= 0 && board[row][col] * board[row][col - movement] < 0)
      possible.push_back({row, col - movement});

    // Moves to the Right
    movement = 1;
    while (col + movement < board[0].size() && board[row][col + movement] == 0)
    {
      possible.push_back({row, col + movement});
      movement++;
    }
    if (col + movement < board[0].size() && board[row][col] * board[row][col + movement] < 0)
      possible.push_back({row, col + movement});

    // Moves Up
    movement = 1;
    while (row - movement >= 0 && board[row - movement][col] == 0)
    {
      possible.push_back({row - movement, col});
      movement++;
    }
    if (row - movement >= 0 && board[row][col] * board[row - movement][col] < 0)
      possible.push_back({row - movement, col});

    // Moves Down
    movement = 1;
    while (row + movement < board.size() && board[row + movement][col] == 0)
    {
      possible.push_back({row + movement, col});
      movement++;
    }
    if (row + movement < board.size() && board[row][col] * board[row + movement][col] < 0)
      possible.push_back({row + movement, col});
  }

  // Knight
  if (abs(board[row][col]) == 3)
  {
    int x[8] = {2, 2, 1, 1, -1, -1, -2, -2};
    int y[8] = {1, -1, 2, -2, 2, -2, 1, -1};

    for (int i = 0; i < 8; i++)
      if (row + x[i] >= 0 && row + x[i] < board.size() &&
          col + y[i] >= 0 && col + y[i] < board[0].size() &&
          board[row][col] * board[row + x[i]][col + y[i]] <= 0)
        possible.push_back({row + x[i], col + y[i]});
  }

  return possible;
}
