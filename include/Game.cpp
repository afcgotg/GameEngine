#include <iostream>
#include <SDL2/SDL.h>

#include "Game.h"

Game::Game(){};
Game::~Game(){};

void Game::init(const char* title, int xpos, int ypos, int height, int width, int flags) {
    m_bRunning = true;

    g_pWindow = 0;
    g_pRenderer = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
        // if succeeded create a window
        g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

        // if the window creation succeeded create our render
        if(g_pWindow != 0){
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
        }else{
            std::cout << "SDL initialized, but error when create the window: " << SDL_GetError() << std::endl;
        }
    }else{
        std::cout << "Error to initialize SDL: " << SDL_GetError() << std::endl;
        m_bRunning = false; //SDL could not initialize
    }
    m_bRunning = true;
}

void Game::render(){};

void Game::update(){};

void Game::handleEvent(){};

void Game::clean(){};

bool Game::running() {
    return m_bRunning;
}