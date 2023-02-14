#include <vector>

#include "../states/GameState.h"

#ifndef __GameStateMachine__
#define __GameStateMachine__

class GameStateMachine{
    public:
        void pushState(GameState* pState);
        void changeState(GameState* pState);
        void popState();

        void update();
        void render();

        void setStateChanged(bool change);
        bool getStateChanged();

    private:
        std::vector<GameState*> m_gameStates;

        bool m_bStateChanged;
};

#endif