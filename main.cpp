#include <iostream>
#include <SDL2/SDL.h>

#include "include/Game.h"

Game* g_game = 0;

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]){
    g_game = new Game();
    g_game->init("Game title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    while(g_game->running()){
        g_game->handleEvent();
        g_game->update();
        g_game->render();
    }

    g_game->clean();

    return 0;
}