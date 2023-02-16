gamename = game

g++32 = i686-w64-mingw32-g++
w32 = i686-w64-mingw32

g++64 = x86_64-w64-mingw32-g++
w64 = x86_64-w64-mingw32

include_directories = ./include/*.cpp ./include/assistant/*.cpp ./include/entities/*.cpp ./include/gears/*.cpp ./include/states/*.cpp

all:

win32:
	${g++32} -I ./src/${w32}/include -L ./src/${w32}/lib -o ./bin/${w32}/${gamename}32.exe main.cpp ${include_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m32 `sdl2-config --static-libs` -static
	xcopy "assets" ".\bin\${w32}\assets" //e //y //q

debug32:
	${g++32} -I ./src/${w32}/include -L ./src/${w32}/lib -o ./bin/${w32}/debug/${gamename}32.exe main.cpp ${include_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -m32 
	xcopy "assets" ".\bin\${w32}\debug\assets" //e //y //q

win64:
	${g++64} -I ./src/${w64}/include -L ./src/${w64}/lib -o ./bin/${w64}/${gamename}64.exe main.cpp ${include_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m64 `sdl2-config --static-libs` -static
	xcopy "assets" ".\bin\${w64}\assets" //e //y //q

debug64:
	${g++64} -I ./src/${w64}/include -L ./src/${w64}/lib -o ./bin/${w64}/debug/${gamename}64.exe main.cpp ${include_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -m64
	xcopy "assets" ".\bin\${w64}\debug\assets" //e //y //q

#linux32:
#	g++ -o bin/linux32/${gamename}32 main.cpp ${include_directories} -lSDL2_image -m32 `sdl2-config --static-libs --cflags`
#	cp -r assets bin/linux32/

linux64:
	g++ -o bin/linux64/${gamename}64 main.cpp ${include_directories} -lSDL2_image -m64 `sdl2-config --static-libs --cflags`
	cp -r assets bin/linux64/