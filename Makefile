release:
	g++ -std=c++17 src/*.cpp src/common/*.cpp src/engine/*.cpp src/game/*.cpp -o build/skywatch.exe -Isrc/common -Isrc/engine -Idependencies/include -Ldependencies/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows

debug:
	g++ -std=c++17 -O0 -g src/*.cpp src/common/*.cpp src/engine/*.cpp src/game/*.cpp -o build/skywatch.exe -Isrc/common -Isrc/engine -Idependencies/include -Ldependencies/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf