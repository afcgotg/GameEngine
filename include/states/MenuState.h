#ifndef __ManuState__
#define __MenuState__

#include <vector>

#include "GameState.h"
#include "../common/Callback.h"



class MenuState : public GameState{
    protected:

    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;
};

#endif