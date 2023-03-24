#include <string>
#include <vector>

#include "MenuState.h"
#include "../game_objects/GameObject.h"

#ifndef __MainMenuState__
#define __MainMenuState__

class MainMenuState : public MenuState {
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getStateID() const;

    private:
        virtual void setCallbacks(const std::vector<Callback> &callbacks);
        
        static const std::string s_menuID;

        std::vector<GameObject*> m_gameObjects;

        static void s_menuToPlay();
        static void s_exitFromMenu();

};


#endif