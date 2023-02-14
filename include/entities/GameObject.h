#include <iostream>
#include <SDL2/SDL.h>

#include "../gears/LoaderParams.h"

#ifndef __GameObject__
#define __GameObject__

class GameObject{
    public:

        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean() = 0;

    protected:
        GameObject(const LoaderParams* pParams){}
        virtual ~GameObject(){}
};

#endif