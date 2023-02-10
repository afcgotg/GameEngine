#include <vector>

#include <SDL2/SDL.h>

#include "GameObject.h"
#include "GameStateMachine.h"

#ifndef __Game__
#define __Game__

class Game{
    public:
        static Game* Instance();
        ~Game();

        SDL_Renderer* getRenderer() const;

        bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
        void render();
        void update();
        void handleEvent();
        void clean();

        bool running();

    private:
        Game();

        static Game* s_pInstance;

        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;

        bool m_bRunning;

        GameStateMachine* m_pGameStateMachine;

        std::vector<GameObject*> m_gameObjects;
};

typedef Game TheGame;

#endif