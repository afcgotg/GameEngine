#include <string>

#include "GameState.h"

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
};


#endif