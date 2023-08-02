#include "GameWindow.h"

GameWindow* GameWindow::_instance = nullptr;
SDL_Window* GameWindow::_window = nullptr;
SDL_Renderer* GameWindow::_renderer = nullptr;

GameWindow* GameWindow::Instance()
{
    if(_instance == nullptr)
    {
        _instance = new GameWindow();
    }
    return _instance;
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
    _title = "Game title";
    _xpos, _ypos = SDL_WINDOWPOS_CENTERED;
    _width = 200;
    _height = 200;
    _isFullScreen = false;

    _fps = 60;
    _delayTime = 1000 / _fps;

    ApplyFlags();

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