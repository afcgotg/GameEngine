#include <iostream>

#include "Game.h"
#include "PathManager.h"

int main(int argc, char* argv[])
{
    ThePathManager::Instance()->SetExecutionPath(argv[0]);
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