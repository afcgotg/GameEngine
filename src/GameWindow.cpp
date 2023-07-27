#include "GameWindow.h"

GameWindow* GameWindow::_instance = nullptr;

GameWindow* GameWindow::Instance()
{
    if(_instance == nullptr)
        _instance = new GameWindow();
    return _instance;
}

GameWindow::GameWindow()
{
    _title = "Game title";
    _xpos, _ypos = SDL_WINDOWPOS_CENTERED;
    _width = 800;
    _height = 600;
    _isFullScreen = false;

    _fps = 60;
    _delayTime = 1000 / _fps;

    ApplyFlags();
}

void GameWindow::ApplyFlags()
{
    _flags = 0;
    if(_isFullScreen)
        _flags = SDL_WINDOW_FULLSCREEN;
}

SDL_Renderer* GameWindow::GetRenderer() const{
    return _renderer;
}

bool GameWindow::Create()
{
    _window = SDL_CreateWindow(_title.c_str(), _xpos, _ypos, _height, _width, _flags);

    if(_window != nullptr)
    {
        std::cout << "Window creation succed" << std::endl;
        _renderer = SDL_CreateRenderer(_window, -1, 0);
        if(_renderer != nullptr)
        {
            std::cout << "Renderer creation succed" << std::endl;
            SDL_SetRenderDrawColor(_renderer, 110, 160, 180, 255);
        }
        else
        {
            std::cout << "Error when create the renderer: " << SDL_GetError() << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Error when create the window: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void GameWindow::Destroy()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

uint32_t GameWindow::GetDelayTime() const
{
    return _delayTime;
}