#include <string>
#include <vector>

#include "GameState.h"
#include "../entities/GameObject.h"

#ifndef __PlayState__
#define __PlayState__

class PlayState : public GameState{
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getStateID() const;

    private:
        static const std::string s_playID;

        std::vector<GameObject*> m_gameObjects;
};


#endif