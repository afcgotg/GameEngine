#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>

class Game{
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int height, int width, int flags);
        void render();
        void update();
        void handleEvent();
        void clean();

        bool running();

    private:
        SDL_Window* g_pWindow;
        SDL_Renderer* g_pRenderer;

        bool m_bRunning;

};

#endif /*defined(__Game__) */