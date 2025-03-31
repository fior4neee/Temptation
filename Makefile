CC = g++
CFLAGS = -I "C:\SDL2\SDL2-2.28.5\x86_64-w64-mingw32\include" \
         -I C:\Users\twtvf\OneDrive\Documents\GitHub\Temptation\src\include \
         -I ./Assets \
         -I ./Game \
         -I ./Imgs

LDFLAGS = -L "C:\SDL2\SDL2-2.28.5\x86_64-w64-mingw32\lib" \
          -L "C:\SDL2\SDL2_image-2.8.5\x86_64-w64-mingw32\lib" \
          -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

SOURCES = $(wildcard ./Game/*.cpp) $(wildcard ./Assets/*.cpp)

EXE_NAME = main.exe

all:
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(SOURCES) $(LDFLAGS)
