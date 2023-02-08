#include <SDL2/SDL.h>
#include <vector>

#include "Vector2D.h"

class InputHandler{
    public:
        static InputHandler* Instance();

        void update();
        void clean();

        void initialiseJoysticks();
        bool joysticksInitialised();

        int xValue(int joy, int stick);
        int yValue(int joy, int stick);

    private:

        InputHandler();
        ~InputHandler();

        std::vector<SDL_Joystick*> m_joysticks;
        bool m_bJoysticksInitialised;

        std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
        const int m_joystickDeadZone = 10000;

        static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;