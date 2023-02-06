#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>

class Game{
    public:
        Game();
        ~Game();

        bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
        void render();
        void update();
        void handleEvent();
        void clean();

        bool running();

    private:
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;

        SDL_Texture* m_pTexture;
        SDL_Rect m_sourceRectangle;
        SDL_Rect m_destinationRectangle;

        bool m_bRunning;

};

#endif /*defined(__Game__) */