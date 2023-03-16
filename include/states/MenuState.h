#include <vector>

#include "GameState.h"

#ifndef __ManuState__
#define __MenuState__

class MenuState : public GameState{
    protected:

    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callbacks> m_callbacks;
};


#endif