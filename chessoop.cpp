#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;

class Piece;
class Square;
class Board;
enum piecetype {Pa, Ro, Kn, Bi, Qu, Ki};

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

class Pawn: public Piece
{
  public:
    Pawn(bool white) : Piece(white)
    {
      type = Pa;
    }
};

class Rook: public Piece
{
  public:
    Rook(bool white) : Piece(white)
    {
      type = Ro;
    }
};

class Knight: public Piece
{
  public:
    Knight(bool white) : Piece(white)
    {
      type = Kn;
    }

};

class Bishop: public Piece
{
  public:
    Bishop(bool white) : Piece(white)
    {
      type = Bi;
    }
};

class Queen: public Piece
{
  public:
    Queen(bool white) : Piece(white)
    {
      type = Qu;
    }
};

class King: public Piece
{
  public:
    King(bool white) : Piece(white)
    {
      type = Ki;
    }
};

class Square
{
  private:
    Piece piece = Piece(true);
    int row;
    int col;
  public:
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
      board[0].push_back(Square(Rook(true), 0, 0));
      board[0].push_back(Square(Knight(true), 0, 1));
      board[0].push_back(Square(Bishop(true), 0, 2));
      board[0].push_back(Square(Queen(true), 0, 3));
      board[0].push_back(Square(King(true), 0, 4));
      board[0].push_back(Square(Bishop(true), 0, 5));
      board[0].push_back(Square(Knight(true), 0, 6));
      board[0].push_back(Square(Rook(true), 0, 7));
      for (int i = 0; i < 8; i ++)
      {
        board[1].push_back(Square(Pawn(true), 1, i));
        board[6].push_back(Square(Pawn(false), 6, i));
      }
      board[7].push_back(Square(Rook(false), 7, 0));
      board[7].push_back(Square(Knight(false), 7, 1));
      board[7].push_back(Square(Bishop(false), 7, 2));
      board[7].push_back(Square(Queen(false), 7, 3));
      board[7].push_back(Square(King(false), 7, 4));
      board[7].push_back(Square(Bishop(false), 7, 5));
      board[7].push_back(Square(Knight(false), 7, 6));
      board[7].push_back(Square(Rook(false), 7, 7));
      for (int i = 2; i < 6; i++)
        for (int j = 0; j < 8; j++)
          board[i].push_back(Square(NULL, i, j));
    }
};

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

  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();
    }

    app.clear(Color::White);
    app.draw(chessboard);

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
      {
        Piece p = board.getLocation(i, j).getPiece();
        if (p.getPiecetype() == Ro && p.getWhite())
        {
          pieces.setTextureRect(IntRect(360, 0, w, w));
          pieces.setPosition(j * w, i * w);
          app.draw(pieces);
        }
      }

    app.display();
  }

}
