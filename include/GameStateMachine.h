#include <vector>

#include "GameState.h"

#ifndef __GameStateMachine__
#define __GameStateMachine__

class GameStateMachine{
    public:
        
        virtual ~GameStateMachine(){};

        static GameStateMachine* Instance();

        void pushState(GameState* pState);
        void changeState(GameState* pState);
        void popState();

        void update();
        void render();

        void setStateChanged(bool change);
        bool getStateChanged();

    private:

        GameStateMachine(){};

        static GameStateMachine* _instance;

        static std::vector<GameState*> m_gameStates;

        bool m_bStateChanged;
};

typedef GameStateMachine TheGameStateMachine;

#endif