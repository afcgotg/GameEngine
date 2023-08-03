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
        void SetExecutionPath(char* path);
        std::string GetExecutionPath() const;
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

        std::string _executionPath;

        bool _isRunning;
};

typedef Game TheGame;

#endif