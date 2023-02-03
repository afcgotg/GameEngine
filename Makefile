# all: 32bits 64bits
all: 64bits
	
32src = src/i686-w64-mingw32
64src = src/x86_64-w64-mingw32

32bits:
	g++ -m32 -I ${32src}/include -L ${32src}/lib -o ${32src}/bin/main32.exe main.cpp -lmingw32 -lSDL2main -lSDL2

64bits:
	g++ -I ${64src}/include -L ${64src}/lib -o ${64src}/bin/main64.exe main.cpp -lmingw32 -lSDL2main -lSDL2
