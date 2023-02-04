app_name = main
windows_32src = src/i686-w64-mingw32
windows_64src = src/x86_64-w64-mingw32

all:

windows_32bits:
	g++ -I ${windows_32src}/include -L ${windows_32src}/lib -o ${windows_32src}/bin/${app_name}32.exe main.cpp -lmingw32 -lSDL2main -lSDL2

windows_64bits:
	g++ -I ${windows_64src}/include -L ${windows_64src}/lib -o ${windows_64src}/bin/${app_name}64.exe main.cpp -lmingw32 -lSDL2main -lSDL2

linux:
	g++ -o src/linux64/bin/${app_name}64 main.cpp -lSDL2main -lSDL2
	