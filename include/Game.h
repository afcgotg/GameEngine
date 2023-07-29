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
        void SetExecutionPath(const char* path);
        const char* GetExecutionPath() const;
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

        static Game* _instance;

        char* _executionPath;

        bool _isRunning;
};

typedef Game TheGame;

#endif