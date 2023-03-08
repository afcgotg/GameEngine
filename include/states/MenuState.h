#include <string>
#include <vector>

#include "GameState.h"
#include "../game_objects/GameObject.h"

#ifndef __MenuState__
#define __MenuState__

class MenuState : public GameState{
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getStateID() const;

    private:
        static const std::string s_menuID;

        std::vector<GameObject*> m_gameObjects;

        static void s_menuToPlay();
        static void s_exitFromMenu();

};


#endif