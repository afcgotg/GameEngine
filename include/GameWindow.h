#include <memory>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>

#ifndef __GameWindow__
#define __GameWindow__

class GameWindow
{
    private:
        std::string _title;
        int _xpos;
        int _ypos;
        int _height;
        int _width;
        uint32_t _flags;
        bool _isFullScreen;

        uint8_t _fps;
        uint32_t _delayTime;

        SDL_Window* _window;
        SDL_Renderer* _renderer;

        void ApplyFlags();

        GameWindow();
        static GameWindow* _instance;

    public:
        ~GameWindow(){};

        static GameWindow* Instance();

        bool Create();
        void Destroy();

        uint32_t GetDelayTime() const;
        
        SDL_Renderer* GetRenderer() const;

};

typedef GameWindow TheGameWindow;

#endif