#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <random>
using namespace std;
using namespace sf;

class Move;
class Piece;
class Square;
class Board;
enum piecetype {NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};

class Move
{
  private:
    bool white;
    int startrow;
    int startcol;
    int endrow;
    int endcol;
    bool castling = false;
  public:
    Move (bool white, int startrow, int startcol, int endrow, int endcol)
    {
      this->setWhite(white);
      this->setStart(startrow, startcol);
      this->setEnd(endrow, endcol);
    }
    bool getWhite()
    {
      return this->white;
    }
    void setWhite(bool white)
    {
      this->white = white;
    }
    vector<int> getStart()
    {
      return {this->startrow, this->startcol};
    }
    void setStart(int startrow, int startcol)
    {
      this->startrow = startrow;
      this->startcol = startcol;
    }
    vector<int> getEnd()
    {
      return {this->endrow, this->endcol};
    }
    void setEnd(int endrow, int endcol)
    {
      this->endrow = endrow;
      this->endcol = endcol;
    }
    bool getCastling()
    {
      return this->castling;
    }
    void setCastling(bool castling)
    {
      this->castling = castling;
    }
};

class Piece
{
  private:
    bool alive = true;
    bool white;
  protected:
    piecetype type;
  public:
    Piece(bool white)
    {
      this->setWhite(white);
    }
    bool getWhite()
    {
      return this->white;
    }
    void setWhite(bool white)
    {
      this->white = white;
    }
    bool getAlive()
    {
      return this->alive;
    }
    void setAlive(bool alive)
    {
      this->alive = alive;
    }
    piecetype getPiecetype()
    {
      return this->type;
    }
};

class None: public Piece
{
  public:
    None (bool white) : Piece(white)
    {
      type = NONE;
    }
};

class Pawn: public Piece
{
  public:
    Pawn(bool white) : Piece(white)
    {
      type = PAWN;
    }
};

class Rook: public Piece
{
  public:
    Rook(bool white) : Piece(white)
    {
      type = ROOK;
    }
};

class Knight: public Piece
{
  public:
    Knight(bool white) : Piece(white)
    {
      type = KNIGHT;
    }

};

class Bishop: public Piece
{
  public:
    Bishop(bool white) : Piece(white)
    {
      type = BISHOP;
    }
};

class Queen: public Piece
{
  public:
    Queen(bool white) : Piece(white)
    {
      type = QUEEN;
    }
};

class King: public Piece
{
  public:
    King(bool white) : Piece(white)
    {
      type = KING;
    }
};

class Square
{
  private:
    Piece piece = Piece(true);
    int row;
    int col;
  public:
    Square()
    {
      this->setPiece(None(true));
      this->setRow(0);
      this->setCol(0);
    }
    Square(Piece piece, int row, int col)
    {
      this->setPiece(piece);
      this->setRow(row);
      this->setCol(col);
    }
    Piece getPiece()
    {
      return this->piece;
    }
    void setPiece(Piece piece)
    {
      this->piece = piece;
    }
    int getRow()
    {
      return this->row;
    }
    void setRow(int row)
    {
      this->row = row;
    }
    int getCol()
    {
      return this->col;
    }
    void setCol(int col)
    {
      this->col = col;
    }
};

class Board
{
  private:
    vector <vector <Square> > board;
  public:
    Board()
    {
      this->resetBoard();
    }
    Square getLocation(int row, int col)
    {
      return board[row][col];
    }
    void resetBoard()
    {
      for (int i = 0; i < 8; i++) board.push_back({});
      board[0].push_back(Square(Rook(false), 0, 0));
      board[0].push_back(Square(Knight(false), 0, 1));
      board[0].push_back(Square(Bishop(false), 0, 2));
      board[0].push_back(Square(Queen(false), 0, 3));
      board[0].push_back(Square(King(false), 0, 4));
      board[0].push_back(Square(Bishop(false), 0, 5));
      board[0].push_back(Square(Knight(false), 0, 6));
      board[0].push_back(Square(Rook(false), 0, 7));
      for (int i = 0; i < 8; i ++)
      {
        board[1].push_back(Square(Pawn(false), 1, i));
        board[6].push_back(Square(Pawn(true), 6, i));
      }
      board[7].push_back(Square(Rook(true), 7, 0));
      board[7].push_back(Square(Knight(true), 7, 1));
      board[7].push_back(Square(Bishop(true), 7, 2));
      board[7].push_back(Square(Queen(true), 7, 3));
      board[7].push_back(Square(King(true), 7, 4));
      board[7].push_back(Square(Bishop(true), 7, 5));
      board[7].push_back(Square(Knight(true), 7, 6));
      board[7].push_back(Square(Rook(true), 7, 7));
      for (int i = 2; i < 6; i++)
        for (int j = 0; j < 8; j++)
          board[i].push_back(Square(None(true), i, j));
    }
    void movePiece (Move move)
    {
      vector<int> start = move.getStart();
      vector<int> end = move.getEnd();
      Piece p = board[start[0]][start[1]].getPiece();
      board[end[0]][end[1]] = Square(p, end[0], end[1]);
      board[start[0]][start[1]] = Square(None(true), start[0], start[1]);
    }
    int evaluate()
    {
      int value = 0;
      for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
          Piece p = this->getLocation(i, j).getPiece();
          int side = p.getWhite() ? 1 : -1;
          int pieceval = 0;
          switch (p.getPiecetype())
          {
            case NONE:
              break;
            case PAWN:
              pieceval = 10;
              break;
            case ROOK:
              pieceval = 50;
              break;
            case KNIGHT:
              pieceval = 30;
              break;
            case BISHOP:
              pieceval = 30;
              break;
            case QUEEN:
              pieceval = 90;
              break;
            case KING:
              pieceval = 900;
              break;
          }
          value += side * pieceval;
        }

      return value;
    }
};

set<vector <int> > possiblemoves (Board board, int row, int col);
Move computerrandom (Board board, bool white);
Move computernexteval (Board board, bool white);
Move minimaxmove (Board board, int depth, bool white);

int main (int arg, char** argv)
{
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

  Board board = Board();
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
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();

      if (!win && e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
      {
        Piece p = board.getLocation(y, x).getPiece();
        if (white && possible.find({y, x}) != possible.end())
        {
          Move move = Move(white, row, col, y, x);
          if (board.getLocation(y, x).getPiece().getPiecetype() == KING) win = true;
          board.movePiece(move);
          possible = set <vector <int> > ();
          white = !white;
        }
        else if (white == p.getWhite())
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

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
      {
        int piece = -1;
        Piece p = board.getLocation(i, j).getPiece();
        int side = p.getWhite() ? 0 : 1;
        if (p.getPiecetype() == NONE) continue;
        switch(p.getPiecetype())
        {
          case PAWN:
            piece = 5;
            break;
          case ROOK:
            piece = 4;
            break;
          case KNIGHT:
            piece = 3;
            break;
          case BISHOP:
            piece = 2;
            break;
          case QUEEN:
            piece = 1;
            break;
          case KING:
            piece = 0;
            break;
          case NONE:
            break;
        }
        pieces.setTextureRect(IntRect(w * piece, w * side, w, w));
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
      winner.setPosition (4 * w, 4 * w);
      winner.setOrigin(winner.getLocalBounds().width / 2.0f, winner.getLocalBounds().height / 2.0f);
      app.draw(winner);
    }

    app.display();

    // If black's turn computer makes move
    if (!win && !white)
    {
      Move newmove = minimaxmove(board, 2, false);
      if (board.getLocation(newmove.getEnd()[0], newmove.getEnd()[1]).getPiece().getPiecetype() == KING) win = true;
      board.movePiece(newmove);
      white = !white;
    }
  }

}

set<vector <int> > possiblemoves (Board board, int row, int col)
{
  Piece p = board.getLocation(row, col).getPiece();
  piecetype type = p.getPiecetype();
  bool white = p.getWhite();

  set <vector <int> > possible;
  if (type == PAWN)
  {
    // Direction of movement
    int dir = white ? -1 : 1;

    // If there is no piece directly in front
    if (row + dir >= 0 && row + dir < 8 &&
        board.getLocation(row + dir, col).getPiece().getPiecetype() == NONE)
    {
      possible.insert({row + dir, col});

      // If pawn is at starting point and there is no piece for two steps
      bool starting = (white && row == 6) || (!white && row == 1);
      if (starting && board.getLocation(row + 2 * dir, col).getPiece().getPiecetype() == NONE)
        possible.insert({row + 2 * dir, col});
    }

    // If there are opponent pieces to the front diagonal
    for (int i = -1; i < 2; i = i + 2)
    {
      if (row + dir < 0 || row + dir > 8 || col + i < 0 || col + i >= 8) continue;
      Piece diag = board.getLocation(row + dir, col + i).getPiece();
      if (diag.getPiecetype() != NONE && diag.getWhite() != white)
        possible.insert({row + dir, col + i});
    }
  }

  // Rook and Queen: sides
  if (type == ROOK || type == QUEEN)
  {
    int xdir[4] = {1, -1, 0, 0};
    int ydir[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      while (x >= 0 && x < 8 && y >= 0 && y < 8 &&
            board.getLocation(x, y).getPiece().getPiecetype() == NONE)
      {
        possible.insert({x, y});
        x += xdir[i];
        y += ydir[i];
      }

      if (x >= 0 && x < 8 && y >= 0 && y < 8 &&
          board.getLocation(x, y).getPiece().getWhite() != white)
        possible.insert({x, y});
    }
  }

  // Knight
  if (type == KNIGHT)
  {
    int xdir[8] = {2, 2, 1, 1, -1, -1, -2, -2};
    int ydir[8] = {1, -1, 2, -2, 2, -2, 1, -1};

    for (int i = 0; i < 8; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      if (x >= 0 && x < 8 && y >= 0 && y < 8)
      {
        Piece poten = board.getLocation(x, y).getPiece();
        if (poten.getPiecetype() == NONE) possible.insert({x, y});
        else if (poten.getWhite() != white) possible.insert({x, y});
      }
    }
  }

  // Bishop and Queen: Diagonals
  if (type == BISHOP || type == QUEEN)
  {
    int xdir[4] = {1, 1, -1, -1};
    int ydir[4] = {-1, 1, -1, 1};
    for (int i = 0; i < 4; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      while (x >= 0 && x < 8 && y >= 0 && y < 8 &&
            board.getLocation(x, y).getPiece().getPiecetype() == NONE)
      {
        possible.insert({x, y});
        x += xdir[i];
        y += ydir[i];
      }

      if (x >= 0 && x < 8 && y >= 0 && y < 8 &&
          board.getLocation(x, y).getPiece().getWhite() != white)
        possible.insert({x, y});
    }
  }

  // King
  if (type == KING)
  {
    int xdir[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int ydir[8] = {1, 0, -1, 1, -1, 1, 0, -1};

    for (int i = 0; i < 8; i++)
    {
      int x = row + xdir[i];
      int y = col + ydir[i];
      if (x >= 0 && x < 8 && y >= 0 && y < 8)
      {
        Piece poten = board.getLocation(x, y).getPiece();
        if (poten.getPiecetype() == NONE) possible.insert({x, y});
        else if (poten.getWhite() != white) possible.insert({x, y});
      }
    }
  }

  return possible;
}

vector <Move> possiblefromboard (Board board, bool white)
{
  // Find all possible moves from the side
  vector <Move> possible;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
      Piece p = board.getLocation(i, j).getPiece();
      if (p.getPiecetype() != NONE && p.getWhite() == white)
      {
        set <vector <int> > possiblehere = possiblemoves(board, i, j);
        for (auto elem : possiblehere)
        {
          if (board.getLocation(elem[0], elem[1]).getPiece().getPiecetype() != NONE)
            possible.insert(possible.begin(), Move (white, i, j, elem[0], elem[1]));
          else possible.push_back(Move(white, i, j, elem[0], elem[1]));
        }
      }
    }

  return possible;
}

Move computerrandom (Board board, bool white)
{
  vector <Move> possible = possiblefromboard(board, white);

  // Choose Random Move
  random_device device;
  mt19937 generator(device());
  uniform_int_distribution<> dis(0, possible.size() - 1);

  int random = dis(generator);
  return possible[random];
}

Move computernexteval (Board board, bool white)
{
  vector <Move> possible = possiblefromboard(board, white);

  vector <int> values;
  int val = white ? -1300 : 1300;
  for (int i = 0; i < possible.size(); i++)
  {
    Board hypothetical = board;
    hypothetical.movePiece(possible[i]);
    int evaluation = hypothetical.evaluate();
    values.push_back(evaluation);
    if ((white && evaluation > val) || (!white && evaluation < val)) val = evaluation;
  }

  vector <int> indices;
  for (int i = 0; i < values.size(); i++)
  {
    if (val == values[i]) indices.push_back(i);
  }

  // Choose Random Move
  random_device device;
  mt19937 generator(device());
  uniform_int_distribution<> dis (0, indices.size() - 1);

  return possible[indices[dis(generator)]];
}

int minimax (Board board, int depth, int alpha, int beta, bool isMax)
{
  if (depth == 0) return board.evaluate();
  vector <Move> possible = possiblefromboard(board, isMax);

  if (isMax)
  {
    int value = -1300;
    for (int i = 0 ; i < possible.size(); i++)
    {
      Board hypothetical = board;
      hypothetical.movePiece(possible[i]);
      int eval = minimax (hypothetical, depth - 1, alpha, beta, false);
      value = max (value, eval);
      alpha = max (alpha, eval);
      if (beta <= alpha) break;
    }
    return value;
  }

  else
  {
    int value = 1300;
    for (int i = 0; i < possible.size(); i++)
    {
      Board hypothetical = board;
      hypothetical.movePiece(possible[i]);
      int eval = minimax (hypothetical, depth - 1, alpha, beta, true);
      value = min (value, eval);
      beta = min (beta, eval);
      if (beta <= alpha) break;
    }
    return value;
  }
}

Move minimaxmove (Board board, int depth, bool white)
{
  vector <Move> possible = possiblefromboard(board, white);

  vector <int> values;
  int val = white ? -1300 : 1300;

  for (int i = 0; i < possible.size(); i++)
  {
    Board hypothetical = board;
    hypothetical.movePiece(possible[i]);
    int minimaxval = minimax(hypothetical, depth, -1300, 1300, !white);
    values.push_back(minimaxval);
    if ((white && minimaxval > val) || (!white && minimaxval < val)) val = minimaxval;
  }

  vector <int> indices;
  for (int i = 0; i < values.size(); i++)
  {
    if (val == values[i]) indices.push_back(i);
  }

  // Choose Random Move
  random_device device;
  mt19937 generator(device());
  uniform_int_distribution<> dis (0, indices.size() - 1);

  return possible[indices[dis(generator)]];
}
