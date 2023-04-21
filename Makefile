gamename = game

g++32 = i686-w64-mingw32-g++
w32 = i686-w64-mingw32

g++64 = x86_64-w64-mingw32-g++
w64 = x86_64-w64-mingw32

src_directories = ./src/*.cpp
include_directories = ./include

all:

win32:
	${g++32} -I ${include_directories}/${w32}/include -L ${include_directories}/${w32}/lib -o ./windows/${gamename}32.exe main.cpp ${src_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m32 `sdl2-config --static-libs` -static

win64:
	${g++64} -I ${include_directories}/${w64}/include -L ${include_directories}/${w64}/lib -o ./bin/windows/${gamename}64.exe main.cpp ${src_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m64 `sdl2-config --static-libs` -static
debug_win64:
	${g++64} -I ${include_directories}/${w64}/include -L ${include_directories}/${w64}/lib -o ./bin/windows/debug/${gamename}64.exe main.cpp ${src_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m64 `sdl2-config --static-libs` -static -g

linux64:
	g++ -o bin/linux/${gamename}64 main.cpp ${src_directories} -lSDL2_image -m64 `sdl2-config --static-libs --cflags`
debug_linux64:
	g++ -o bin/linux/debug/${gamename}64 main.cpp ${src_directories} -lSDL2_image -m64 `sdl2-config --static-libs --cflags` -g