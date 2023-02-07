#include <iostream>

#include "Game.h"

Game::Game(){};
Game::~Game(){};

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen) {

    m_bRunning = false;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "SDL init succed" << std::endl;
        // if succeeded create a window

        int flags = 0;

        if(fullscreen){
            flags = SDL_WINDOW_FULLSCREEN;
        }
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

        // if the window creation succeeded create our render
        if(m_pWindow != 0){
            std::cout << "Window creation succed" << std::endl;
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if(m_pRenderer != 0){
                std::cout << "Renderer creation succed" << std::endl;
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
            }else{
                std::cout << "Error when create the renderer: " << SDL_GetError() << std::endl;
                return false;
            }
        }else{
            std::cout << "Error when create the window: " << SDL_GetError() << std::endl;
            return false;
        }
    }else{
        std::cout << "Error to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    m_bRunning = true;

    SDL_Surface* pTempSurface = IMG_Load("assets/img/GraveRobber/GraveRobber_idle.png");
    if(pTempSurface == NULL){
        std::cout << "Error al cargar la imagen: " << SDL_GetError() << std::endl; 
    }

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
    m_nAnimationSize = m_sourceRectangle.w / 4;
    m_sourceRectangle.w = m_nAnimationSize;

    m_sourceRectangle.x = m_sourceRectangle.y = 0;
    m_destinationRectangle.x = m_destinationRectangle.y = 0;

    m_destinationRectangle.w = m_sourceRectangle.w * 2;
    m_destinationRectangle.h = m_sourceRectangle.h * 2;

    return true;
}

void Game::render(){
    SDL_RenderClear(m_pRenderer);

    //SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_HORIZONTAL);

    SDL_RenderPresent(m_pRenderer);
}

void Game::update(){
    m_sourceRectangle.x = m_nAnimationSize * (int(SDL_GetTicks() / 150) % 4);
};

void Game::handleEvent(){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                m_bRunning = false;
                break;

            default:
                break;
        }
    }
}

void Game::clean(){
    std::cout << "cleaning game..." << std::endl;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

bool Game::running() {
    return m_bRunning;
}