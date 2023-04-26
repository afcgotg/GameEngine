#include "SDLGameObject.h"
#include "Callback.h"
#include "GameObjectFactory.h"

#ifndef __MenuButton__
#define __MenuButton__

class MenuButton : public SDLGameObject{
    public:
        MenuButton();

        virtual ~MenuButton();

        virtual void load(const LoaderParams* pParams);

        virtual void draw();
        virtual void update();
        virtual void clean();

        void setCallback(void(*callback)());
        int getCallbackID();

    private:
        enum button_state{
            MOUSE_OUT = 0,
            MOUSE_OVER = 1,
            CLICKED = 2
        };

        void (*m_callback)();

        bool m_bPressed;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* createGameObject() const{
        return new MenuButton();
    }
};

#endif