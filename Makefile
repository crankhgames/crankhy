SRC_FILES := $(wildcard src/*/*.cpp src/*.cpp)

	
all:
	g++ -Iinclude -Iinclude/headers  -Itools  -Llib -o main $(SRC_FILES) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image