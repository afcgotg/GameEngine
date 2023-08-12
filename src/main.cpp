#include <iostream>

#include "Game.h"
#include "FileManager.h"

int main(int argc, char* argv[])
{
    TheFileManager::Instance()->SetExecutionPath(argv[0]);
    if(TheGame::Instance()->Init())
    {
        TheGame::Instance()->GameLoop();
    }
    else
    {
        std::cout << "fail to init game: " << SDL_GetError() << std::endl;
        return -1;
    }
    return 0;
}