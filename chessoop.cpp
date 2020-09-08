#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;

class Piece;
class Square;
class Board;
class Move;
enum piecetype {NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};

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
    vector <Square> possiblemoves(Board board, Square location);
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
    void movePiece (int startrow, int startcol, int endrow, int endcol)
    {
      Piece p = board[startrow][startcol].getPiece();
      board[endrow][endcol] = Square(p, endrow, endcol);
      board[startrow][startcol] = Square(None(true), startrow, startcol);
    }
};

/*class Move
{
  private:
    bool white;
    Square start;
    Square end;
  public:
    Move (bool white, Square start, Square end)
    {
      this->setWhite(white);
      this->setStart(start);
      this->setEnd(end);
    }
    bool getWhite()
    {
      return this->white;
    }
    void setWhite(bool white)
    {
      this->white = white;
    }
    Square getStart()
    {
      return this->start;
    }
    void setStart(Square start)
    {
      this->start = start;
    }
    Square getEnd()
    {
      return this->end;
    }
    void setEnd(Square end)
    {
      this->end = end;
    }
};*/

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

  Board board = Board();
  int w = 90;
  RenderWindow app(VideoMode(8 * w, 8 * w), "Chess");

  bool alternate = true;
  int row;
  int col;
  while (app.isOpen())
  {
    Vector2i pos = Mouse::getPosition(app);
    int x = pos.x / w;
    int y = pos.y / w;

    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();

      if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
      {
        if (alternate)
        {
          col = x;
          row = y;
        }
        else
        {
          board.movePiece(row, col, y, x);
        }
        alternate = !alternate;
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

    app.display();
  }

}
