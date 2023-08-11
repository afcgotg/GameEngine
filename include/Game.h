#include <vector>

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

    private:
        Game(){};

        bool InitSDL();

        void Render();
        void Update();
        void HandleEvent();

        static Game* mInstance;

        bool mIsRunning;
};

typedef Game TheGame;

#endif