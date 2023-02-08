#include <iostream>

#include "include/Game.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]){

    if(TheGame::Instance()->init("Game title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, false)){
        std::cout << "game init succed" << std::endl;
        while(TheGame::Instance()->running()){
            TheGame::Instance()->handleEvent();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            SDL_Delay(10);
        }
    }else{
        std::cout << "fail to init game: " << SDL_GetError() << std::endl;
        return -1;
    }

    TheGame::Instance()->clean();

    return 0;
}