#include <iostream>

#include "Game.h"

#include "gears/GameObjectFactory.h"
#include "gears/TextureManager.h"
#include "gears/InputHandler.h"

#include "game_objects/Player.h"
#include "game_objects/Enemy.h"

#include "states/MenuState.h"
#include "states/PlayState.h"

#include "game_objects/MenuButton.h"

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
                SDL_SetRenderDrawColor(m_pRenderer, 110, 160, 180, 255);
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

    TheInputHandler::Instance()->initialiseJoysticks();

    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("enemy", new EnemyCreator());

    m_bRunning = true;
    return true;
}

void Game::render(){
    SDL_RenderClear(m_pRenderer); //clear to the draw color

    m_pGameStateMachine->render();

    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update(){
    m_pGameStateMachine->update();
};

void Game::handleEvent(){
    TheInputHandler::Instance()->update();
}

void Game::clean(){
    m_bRunning = false;
    std::cout << "cleaning game..." << std::endl;
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

bool Game::running() {
    return m_bRunning;
}

GameStateMachine* Game::getStateMachine(){
    return m_pGameStateMachine;
}