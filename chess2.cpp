#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
using namespace sf;

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

  // Window
  int w = 90;
  RenderWindow app(VideoMode(8 * w, 8 * w), "Chess");

  // Game Runs
  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();
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
    app.display();
  }
}
