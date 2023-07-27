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

Game* Game::_instance = 0;

Game* Game::Instance(){
    if(_instance == 0){
        _instance = new Game();
    }
    return _instance;
}

bool Game::Init() {

    _isRunning = false;

    if(!InitSDL())
        return false;

    if(!TheGameWindow::Instance()->Create())
        return false;
    
    TheInputHandler::Instance()->InitialiseJoysticks();
    
    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

    TheGame::Instance()->GetStateMachine()->changeState(new MainMenuState());
    _isRunning = true;
    return true;
}

bool Game::InitSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL init succed" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Error to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }
}

void Game::GameLoop()
{
    uint32_t frameStart, frameTime;
    while(_isRunning)
    {
        frameStart = SDL_GetTicks();

        HandleEvent();
        Update();
        Render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < TheGameWindow::Instance()->GetDelayTime())
            SDL_Delay(TheGameWindow::Instance()->GetDelayTime() - frameTime);
    }
}

void Game::Render(){
    SDL_RenderClear(TheGameWindow::Instance()->GetRenderer()); //clear to the draw color
    _gameStateMachine->render();
    SDL_RenderPresent(TheGameWindow::Instance()->GetRenderer()); // draw to the screen
}

void Game::Update(){
    _gameStateMachine->update();
}

void Game::HandleEvent(){
    TheInputHandler::Instance()->HandleEvent();
}

void Game::Clean(){
    _isRunning = false;
    std::cout << "cleaning game..." << std::endl;
    TheInputHandler::Instance()->clean();
    TheGameWindow::Instance()->Destroy();
    SDL_Quit();
}

GameStateMachine* Game::GetStateMachine(){
    if(_gameStateMachine == NULL){
        _gameStateMachine = new GameStateMachine();
        *strrchr(_argv[0], slash[0]) = '\0';    
        _gameStateMachine->setPath(_argv[0]);
    }
    return _gameStateMachine;
}