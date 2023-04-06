gamename = game

g++32 = i686-w64-mingw32-g++
w32 = i686-w64-mingw32

g++64 = x86_64-w64-mingw32-g++
w64 = x86_64-w64-mingw32

include_directories = ./include/*.cpp

all:

win32:
	${g++32} -I ./src/${w32}/include -L ./src/${w32}/lib -o ./${gamename}32.exe main.cpp ${include_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m32 `sdl2-config --static-libs` -static
	xcopy "assets" ".\bin\${w32}\assets" //e //y //q

debug32:
	${g++32} -I ./src/${w32}/include -L ./src/${w32}/lib -o ./debug/${w32}/${gamename}32.exe main.cpp ${include_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -m32
	xcopy "assets" ".\debug\${w32}\assets" //e //y //q
	xcopy "src\${w32}\SDL2.dll" ".\debug\${w32}\assets" /D
	xcopy "src\${w32}\SDL2_image.dll" ".\debug\${w32}\assets" /D

win64:
	${g++64} -I ./src/${w64}/include -L ./src/${w64}/lib -o ./${gamename}64.exe main.cpp ${include_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m64 `sdl2-config --static-libs` -static

debug64:
	${g++64} -I ./src/${w64}/include -L ./src/${w64}/lib -o ./debug/${w64}/${gamename}64.exe main.cpp ${include_directories} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -m64
	xcopy "assets" ".\debug\${w64}\assets" //e //y //q //A
	xcopy "src\${w64}\SDL2.dll" ".\debug\${w64}" //D
	xcopy "src\${w64}\SDL2_image.dll" ".\debug\${w64}" //D

#linux32:
#	g++ -o bin/linux32/${gamename}32 main.cpp ${include_directories} -lSDL2_image -m32 `sdl2-config --static-libs --cflags`
#	cp -r assets bin/linux32/

linux64:
	g++ -o bin/linux64/${gamename}64 main.cpp ${include_directories} -lSDL2_image -m64 `sdl2-config --static-libs --cflags`
	cp -r assets bin/linux64/