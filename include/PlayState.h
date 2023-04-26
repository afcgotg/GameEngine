#ifndef __PlayState__
#define __PlayState__

#include <string>
#include <vector>

#include "GameState.h"
#include "GameObject.h"
#include "SDLGameObject.h"

class PlayState : public GameState{
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter(const char* filePath);
        virtual bool onExit();

        virtual std::string getStateID() const;

    private:
        static const std::string s_playID;

        std::vector<GameObject*> m_gameObjects;

        bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
};


#endif