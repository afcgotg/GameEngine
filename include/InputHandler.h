#include <SDL2/SDL.h>
#include <vector>

#include "Vector2D.h"

enum mouse_buttons{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler{
    public:
        static InputHandler* Instance();

        void update();
        void clean();

        void initialiseJoysticks();
        bool joysticksInitialised();

        bool getButtonState(int joy, int buttonNumber);

        int xValue(int joy, int stick);
        int yValue(int joy, int stick);

        int dpad_xValue(int joy);
        int dpad_yValue(int joy);

        int ltValue(int joy);
        int rtValue(int joy);

        bool getMouseButtonState(int buttonNumber);

    private:

        InputHandler();
        ~InputHandler();

        std::vector<SDL_Joystick*> m_joysticks;
        bool m_bJoysticksInitialised;

        std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
        const int m_joystickDeadZone = 10000;

        std::vector<std::pair<int*, int*>> m_triggerValues;
        const int m_triggerDeadZone = 10000;

        std::vector<std::pair<int*, int*>> m_dpadValues;

        std::vector<std::vector<bool>> m_buttonStates;

        std::vector<bool> m_mouseButtonStates;

        static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;

