all:
	g++ src/*.cpp src/engine/*.cpp src/game/*.cpp -o build/skywatch.exe -Isrc/common -Isrc/engine -Idependencies/include -Ldependencies/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf