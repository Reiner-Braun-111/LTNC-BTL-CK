all:
	g++ -Isrc/include -Lsrc/lib -o main main.cpp function.cpp button.cpp texture.cpp variables.cpp time.cpp menu.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
