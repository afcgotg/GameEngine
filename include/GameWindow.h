#include <memory>
#include <string>
#include <iostream>
#include <../SDL2/include/SDL2/SDL.h>

#ifndef __GameWindow__
#define __GameWindow__

struct RGBa
{
    int red;
    int green;
    int blue;
    int alpha;
};

class GameWindow
{
    private:
        GameWindow(){};
        static GameWindow* mInstance;

        std::string mTitle;
        int mX;
        int mY;
        int mHeight;
        int mWidth;
        uint32_t mFlags;
        bool mIsFullScreen;
        RGBa mBackgroundColor;

        int mFps;
        uint32_t mDelayTime;

        static SDL_Window* mWindow;
        static SDL_Renderer* mRenderer;

        void ApplyFlags();



    public:
        ~GameWindow(){};

        static GameWindow* Instance();

        bool Create();
        void Destroy();

        bool LoadSettings();

        uint32_t GetDelayTime() const;
        
        SDL_Window* GetWindow() const;
        SDL_Renderer* GetRenderer() const;
};

typedef GameWindow TheGameWindow;

#endif