#include <string>

#include "GameState.h"

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
};


#endif