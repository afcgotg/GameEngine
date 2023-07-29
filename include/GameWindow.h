#include <memory>
#include <string>
#include <iostream>

#if __SIZEOF_POINTER__ == 4
    #include "SDL/x32/include/SDL2/SDL.h"
#elif __SIZEOF_POINTER__ == 8
    #include "SDL/x64/include/SDL2/SDL.h"
#endif

#ifndef __GameWindow__
#define __GameWindow__

class GameWindow
{
    private:
        GameWindow(){};
        static GameWindow* _instance;

        std::string _title;
        int _xpos;
        int _ypos;
        int _height;
        int _width;
        uint32_t _flags;
        bool _isFullScreen;

        uint8_t _fps;
        uint32_t _delayTime;

        static SDL_Window* _window;
        static SDL_Renderer* _renderer;

        void ApplyFlags();

    public:
        ~GameWindow(){};

        static GameWindow* Instance();

        bool Create();
        void Destroy();

        uint32_t GetDelayTime() const;
        
        SDL_Window* GetWindow() const;
        SDL_Renderer* GetRenderer() const;
};

typedef GameWindow TheGameWindow;

#endif