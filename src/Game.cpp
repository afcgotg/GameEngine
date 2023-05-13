#include <iostream>
#include <cstring>

#include "Game.h"

#include "GameObjectFactory.h"
#include "TextureManager.h"
#include "InputHandler.h"

#include "Player.h"
#include "Enemy.h"
#include "AnimatedGraphic.h"

#include "MainMenuState.h"
#include "PlayState.h"

#include "MenuButton.h"

#if defined(_WIN64)
    const char* slash = "\\";
#elif defined(__unix__) && defined(__x86_64__)
    const char* slash = "/";
#endif

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

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen, char** argv) {

    m_bRunning = false;
    m_argv = argv;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "SDL init succed" << std::endl;
        // if succeeded create a window

        uint32_t flags = 0;

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
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
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
    if(m_pGameStateMachine == NULL){
        m_pGameStateMachine = new GameStateMachine();
        *strrchr(m_argv[0], slash[0]) = '\0';    
        m_pGameStateMachine->setPath(m_argv[0]);
    }
    return m_pGameStateMachine;
}