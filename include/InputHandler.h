#include <../SDL2/include/SDL2/SDL.h>
#include <vector>

#include "Vector2D.h"

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

        void HandleEvent();
        void clean();

        void InitialiseJoysticks();
        bool joysticksInitialised();

        bool getButtonState(size_t joy, size_t buttonNumber);

        int xValue(size_t joy, int stick);
        int yValue(size_t joy, int stick);

        int dpad_xValue(size_t joy);
        int dpad_yValue(size_t joy);

        int ltValue(size_t joy);
        int rtValue(size_t joy);

        bool getMouseButtonState(size_t buttonNumber);
        void reset();

        Vector2D* getMousePosition();

        bool isKeyDown(SDL_Scancode key);

    private:

        InputHandler();
        ~InputHandler(){};

        std::vector<SDL_Joystick*> mJoysticks;
        bool mJoysticksInitialised;

        std::vector<std::pair<Vector2D*, Vector2D*>> mJoystickValues;
        const int mJoystickDeadZone = 10000;

        std::vector<std::pair<int*, int*>> mTriggerValues;
        const uint32_t mTriggerDeadZone = 10000;

        std::vector<std::pair<int*, int*>> mDpadValues;

        std::vector<std::vector<bool>> mButtonStates;

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

