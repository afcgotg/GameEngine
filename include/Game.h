#include <vector>

#if __SIZEOF_POINTER__ == 4
    #include "SDL/x32/include/SDL2/SDL.h"
#elif __SIZEOF_POINTER__ == 8
    #include "SDL/x64/include/SDL2/SDL.h"
#endif

#include "GameWindow.h"
#include "GameObject.h"
#include "GameStateMachine.h"

#ifndef __Game__
#define __Game__

class Game
{
    public:
        static Game* Instance();
        ~Game(){};

        void GameLoop();

        bool Init();
        
        void Clean();

        GameStateMachine* GetStateMachine();

    private:
        Game(){};

        void Render();
        void Update();
        void HandleEvent();

        bool InitSDL();

        static Game* _instance;

        char** _argv;

        bool _isRunning;

        GameStateMachine* _gameStateMachine;

        std::vector<GameObject*> _gameObjects;
};

typedef Game TheGame;

#endif