#ifndef __PlayState__
#define __PlayState__

#include <string>
#include <vector>

#include "GameState.h"
#include "../game_objects/GameObject.h"
#include "../game_objects/SDLGameObject.h"

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

        bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
};


#endif