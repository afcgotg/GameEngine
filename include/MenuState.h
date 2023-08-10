#include <vector>

#include "GameState.h"
#include "Callback.h"

#ifndef __MenuState__
#define __MenuState__

class MenuState : public GameState{
    protected:

    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> mCallbacks;
};

#endif