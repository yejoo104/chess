chessoop: chessoop.cpp
	g++ -std=c++17 -o chessoop chessoop.cpp -lsfml-graphics -lsfml-window -lsfml-system

chess3: chess3.cpp
	g++ -std=c++17 -o chess3 chess3.cpp -lsfml-graphics -lsfml-window -lsfml-system

chess2: chess2.cpp
	g++ -std=c++17 -o chess2 chess2.cpp -lsfml-graphics -lsfml-window -lsfml-system

chess: chess.cpp
	g++ -std=c++17 -o chess chess.cpp
