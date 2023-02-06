gamename = main
win32src = ./src/i686-w64-mingw32
win64src = ./src/x86_64-w64-mingw32

include_files = ./include

all:

#win32:
#	g++ -I ${win32src}/include -L ${win32src}/lib -o ${win32src}/bin/${gamename}32.exe main.cpp -lmingw32 -lSDL2main -lSDL2

win64:
	g++ -I ${win64src}/include -L ${win64src}/lib -o ${win64src}/bin/${gamename}64.exe main.cpp ${include_files}/*.cpp -lmingw32 -lSDL2main -lSDL2

# linux32:
#	g++ -o src/linux32/${gamename}32 main.cpp -lSDL2main -lSDL2

linux64:
	g++ -o src/linux64/${gamename}64 main.cpp ${include_files}/*.cpp -lSDL2main -lSDL2
	