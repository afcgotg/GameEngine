#include <iostream>
#include "include/Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]){

    Uint32 frameStart, frameTime;

    if(TheGame::Instance()->init("Game title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, false, argv)){
        while(TheGame::Instance()->running()){

            frameStart = SDL_GetTicks();

            TheGame::Instance()->handleEvent();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            frameTime = SDL_GetTicks() - frameStart;

            if(frameTime < DELAY_TIME){
                SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
            }
        }
    }else{
        std::cout << "fail to init game: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    return 0;
}