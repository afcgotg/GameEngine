#include <iostream>

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

Game* Game::mInstance = nullptr;

Game* Game::Instance(){
    if(!mInstance)
        mInstance = new Game();
    return mInstance;
}

bool Game::Init() {

    mIsRunning = false;

    if(!InitSDL())
        return false;

    if(!TheGameWindow::Instance()->Create())
        return false;
    
    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

    TheInputHandler::Instance()->InitialiseJoysticks();

    TheGameStateMachine::Instance()->changeState(new MainMenuState());

    mIsRunning = true;

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
    while(mIsRunning)
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
    TheGameStateMachine::Instance()->render();
    SDL_RenderPresent(TheGameWindow::Instance()->GetRenderer()); // draw to the screen
}

void Game::Update(){
    TheGameStateMachine::Instance()->update();
}

void Game::HandleEvent(){
    TheInputHandler::Instance()->HandleEvent();
}

void Game::Clean(){
    mIsRunning = false;
    std::cout << "cleaning game..." << std::endl;
    TheInputHandler::Instance()->clean();
    TheGameWindow::Instance()->Destroy();
    SDL_Quit();
}