#include <vector>

#include "Vector2D.h"
#include "XBOXController.h"

#ifndef __InputHandler__
#define __InputHandler__

enum mouse_buttons{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler{
    public:
        static InputHandler* Instance();

        void AddXBOXController();

        void HandleEvent();
        void clean();

        bool getMouseButtonState(size_t buttonNumber);
        void reset();

        Vector2D* getMousePosition();

        bool isKeyDown(SDL_Scancode key);

    private:

        InputHandler();
        ~InputHandler(){};

        std::vector<XBOXController> mXBOXControllersVector;

        std::vector<bool> mMouseButtonStates;

        Vector2D* mMousePosition;

        const Uint8* mKeystates;

        // functions to handle different event types

        // keyboard events
        // void onkeyDown();
        // void onKeyUp();

        // mouse events
        void onMouseMove(SDL_Event& event);
        void onMouseButtonDown(SDL_Event& event);
        void onMouseButtonUp(SDL_Event& event);

        // joysticks events
        void onJoystickAxisMove(SDL_Event& event);
        void onJoystickHatMove(SDL_Event& event);
        void onJoystickButtonDown(SDL_Event& event);
        void onJoystickButtonUp(SDL_Event& event);

        static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;

#endif

