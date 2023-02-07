#include <iostream>

#include "Game.h"

#include "Player.h"
#include "Enemy.h"

Game* Game::s_pInstance = 0;

Game* Game::Instance(){
    if(s_pInstance == 0){
        s_pInstance = new Game();
    }
    return s_pInstance;
}

Game::Game(){}

Game::~Game(){}

SDL_Renderer* Game::getRenderer() const{
    return m_pRenderer;
}

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
                SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
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

    if(!TheTextureManager::Instance()->load("assets/img/GraveRobber/GraveRobber_idle.png", "animate", m_pRenderer)){
        return false;
    }

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 48, 48, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(100, 100, 48, 48, "animate")));

    return true;
}

void Game::render(){
    SDL_RenderClear(m_pRenderer); //clear to the draw color

    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }

    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update(){
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++){
        m_gameObjects[i]->update();
    }
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