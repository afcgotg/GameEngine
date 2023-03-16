#include "SDLGameObject.h"
#include "../common/Callback.h"

#ifndef __MenuButton__
#define __MenuButton__

class MenuButton : public SDLGameObject{
    public:
        MenuButton();

        virtual void load(const LoaderParams* pParams);

        virtual void draw();
        virtual void update();
        virtual void clean();

        virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
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

#endif