#include <vector>

#include "GameState.h"

#ifndef __GameStateMachine__
#define __GameStateMachine__

class GameStateMachine{
    public:
        void pushState(GameState* pState);
        void changeState(GameState* pState);
        void popState();

    private:
        std::vector<GameState*> m_gameStates;
};

#endif