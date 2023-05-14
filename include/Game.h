#include <vector>

#if __SIZEOF_POINTER__ == 4
    #include "SDL/x32/include/SDL2/SDL.h"
#elif __SIZEOF_POINTER__ == 8
    #include "SDL/x64/include/SDL2/SDL.h"
#endif

#include "GameObject.h"
#include "GameStateMachine.h"

#ifndef __Game__
#define __Game__

class Game{
    public:
        static Game* Instance();
        ~Game();

        SDL_Renderer* getRenderer() const;

        bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen, char** argv);
        void render();
        void update();
        void handleEvent();
        void clean();

        bool running();

        GameStateMachine* getStateMachine();

    private:
        Game();

        static Game* s_pInstance;

        char** m_argv;

        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;

        bool m_bRunning;

        GameStateMachine* m_pGameStateMachine;

        std::vector<GameObject*> m_gameObjects;
};

typedef Game TheGame;

#endif