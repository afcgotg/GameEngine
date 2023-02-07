gamename = game

win32 = i686-w64-mingw32
win64 = x86_64-w64-mingw32

all:

#win32:
#	g++ -I $./src/{win32}/include -L $./src/{win32}/lib -o bin/${win32}/${gamename}32.exe main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
#	xcopy "assets" ".\bin\${win32}\assets" //e //y //q

win64:
	g++ -I ./src/${win64}/include -L ./src/${win64}/lib -o ./bin/${win64}/${gamename}64.exe main.cpp ./include/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	xcopy "assets" ".\bin\${win64}\assets" //e //y //q

# linux32:
#	g++ -o src/linux32/${gamename}32 main.cpp -lSDL2main -lSDL2 -lSDL2_image

linux64:
	g++ -o bin/linux64/${gamename}64 main.cpp ./include/*.cpp -lSDL2main -lSDL2 -lSDL2_image
	cp -r assets bin/linux64/