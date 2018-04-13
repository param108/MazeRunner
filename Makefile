mazeServer:	main.cpp maze.h room.h cell.h
	g++ main.cpp -g -o mazeServer -lncurses -lmicrohttpd -std=c++11
