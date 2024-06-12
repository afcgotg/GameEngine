#include <memory>
#include <string>
#include <iostream>
#include <../SDL2/include/SDL2/SDL.h>

#ifndef __GameWindow__
#define __GameWindow__

struct RGBaColor
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
        RGBaColor mBackgroundColor;

        int mFps;
        uint32_t mDelayTime;

        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        void ApplyFlags();
        void CenterWindow();

    public:
        ~GameWindow(){};

        static GameWindow* Instance();

        bool Create();
        void Destroy();

        bool LoadSettings();

        uint32_t GetDelayTime() const;
        
        SDL_Renderer* GetRenderer() const;
};

typedef GameWindow TheGameWindow;

#endif