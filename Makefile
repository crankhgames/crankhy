all:
	g++ -Iinclude -Iinclude/headers  -Iinclude/SDL2 -Llib -o main $(wildcard src/*.cpp) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image