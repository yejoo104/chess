#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <random>
using namespace std;
using namespace sf;

set <vector <int> > possiblemoves (vector <vector <int> > board, int row, int col);
vector <int> computerrandom (vector <vector <int>> board, bool white);

int main (int arg, char** argv)
{
  // Staring Chess Board
  vector <vector <int> > board { {-5, -4, -3, -2, -1, -3, -4, -5},
                                 {-6, -6, -6, -6, -6, -6, -6, -6},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {6, 6, 6, 6, 6, 6, 6, 6},
                                 {5, 4, 3, 2, 1, 3, 4, 5} };

  // Board Sprite
  Texture t1;
  t1.loadFromFile("board.png");
  Sprite chessboard(t1);

  // Pieces Sprite
  Texture t2;
  t2.loadFromFile("pieces.png");
  Sprite pieces(t2);

  // Dot Sprite
  Texture t3;
  t3.loadFromFile("potential.jpg");
  Sprite dot(t3);

  // Window
  int w = 90;
  RenderWindow app(VideoMode(8 * w, 8 * w), "Chess");

  // Winner Message
  Font font;
  font.loadFromFile("Ka Blam.ttf");
  Text winner;
  winner.setFont(font);
  winner.setCharacterSize(w);
  winner.setFillColor(Color::Black);
  winner.setStyle(Text::Bold);

  // Variables for Game to Run
  int row;
  int col;
  set <vector <int> > possible;
  bool white = true;
  bool win = false;

  // Game Runs
  while (app.isOpen())
  {
    Vector2i pos = Mouse::getPosition(app);
    int x = pos.x / w;
    int y = pos.y / w;

    Event e;
    while(app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();

      if (!win && e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
      {
        if (white && possible.find({y, x}) != possible.end())
        {
          if (board[y][x] == -1) win = true;
          board[y][x] = board[row][col];
          board[row][col] = 0;
          possible = set <vector <int> > ();
          white = !white;
        }
        else if (white && board[y][x] > 0)
        {
          col = x;
          row = y;
          possible = possiblemoves(board, row, col);
        }
        else possible = set <vector <int> > ();
      }
    }

    app.clear(Color::White);
    app.draw(chessboard);

    for (int i = 0; i < board.size(); i++)
      for (int j = 0; j < board[i].size(); j++)
      {
        if (board[i][j] == 0) continue;
        int piece = abs(board[i][j]);
        int side = board[i][j] > 0 ? 0 : 1;
        pieces.setTextureRect(IntRect(w * (piece - 1), w * side, w, w));
        pieces.setPosition(j * w, i * w);
        app.draw(pieces);
      }

    for (auto elem : possible)
    {
      dot.setScale(0.05, 0.05);
      dot.setPosition((elem[1] + 0.5) * w - 11.25, (elem[0] + 0.5) * w - 11.25);
      app.draw(dot);
    }

    if (win)
    {
      if (white) winner.setString("BLACK WINS");
      else winner.setString("WHITE WINS");
      winner.setPosition(4 * w, 4 * w);
      winner.setOrigin(winner.getLocalBounds().width / 2.0f, winner.getLocalBounds().height / 2.0f);
      app.draw(winner);
    }

    app.display();

    // If black's turn, computer makes move
    if (!win && !white)
    {
      vector<int> newmove = computerrandom(board, false);
      if (board[newmove[2]][newmove[3]] == 1) win = true;
      board[newmove[2]][newmove[3]] = board[newmove[0]][newmove[1]];
      board[newmove[0]][newmove[1]] = 0;
      white = !white;
    }
  }
}

set <vector <int> > possiblemoves (vector <vector <int> > board, int row, int col)
{
  set <vector <int> > possible;

  // Pawn
  if (abs(board[row][col]) == 6)
  {
    // Direction of movement (based on whether white or black)
    int dir = board[row][col] > 0 ? -1 : 1;

    // If there is no piece directly in front
    if (row + dir >= 0 && board[row + dir][col] == 0)
    {
      possible.insert({row + dir, col});

      // If pawn is at starting point there is no piece two steps in front
      bool starting = (dir == 1 && row == 1) || (dir == -1 && row == 6);
      if (starting && row + 2 * dir >= 0 && board[row + 2 * dir][col] == 0)
        possible.insert({row + 2 * dir, col});
    }

    // If there are opponent pieces to the front diagonal
    if (col + 1 < board[0].size() && board[row][col] * board[row + dir][col + 1] < 0) possible.insert({row + dir, col + 1});
    if (col - 1 >= 0 && board[row][col] * board[row + dir][col - 1] < 0) possible.insert({row + dir, col - 1});
  }

  // Rook and Queen: sides
  if (abs(board[row][col]) == 5 || abs(board[row][col]) == 2)
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
        possible.insert({x, y});
        x += xdir[i];
        y += ydir[i];
      }
      if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
          board[row][col] * board[x][y] < 0) possible.insert({x, y});
    }
  }

  // Knight
  if (abs(board[row][col]) == 4)
  {
    int xdir[8] = {2, 2, 1, 1, -1, -1, -2, -2};
    int ydir[8] = {1, -1, 2, -2, 2, -2, 1, -1};

    for (int i = 0; i < 8; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
          board[row][col] * board[x][y] <= 0)
        possible.insert({x, y});
    }
  }

  // Bishop and Queen: Diagonals
  if (abs(board[row][col]) == 3 || abs(board[row][col]) == 2)
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
        possible.insert({x, y});
        x += xdir[i];
        y += ydir[i];
      }
      if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
          board[row][col] * board[x][y] < 0) possible.insert({x, y});
    }
  }

  // King
  if (abs(board[row][col]) == 1)
  {
    int xdir[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int ydir[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
          board[row][col] * board[x][y] <= 0) possible.insert({x, y});
    }
  }

  return possible;
}

vector <int> computerrandom (vector <vector <int>> board, bool white)
{
  // Find all possible moves from the side
  vector <vector <int> > possible;
  for (int i = 0; i < board.size(); i++)
    for (int j = 0; j < board[i].size(); j++)
      if ((white && board[i][j] > 0) || (!white && board[i][j] < 0))
      {
        set <vector <int> > possiblehere = possiblemoves(board, i, j);
        for (auto elem : possiblehere) possible.push_back({i, j, elem[0], elem[1]});
      }

  // Choose Random Move
  random_device device;
  mt19937 generator(device());
  uniform_int_distribution<> dis(0, possible.size() - 1);

  int random = dis(generator);

  return possible[random];
}
