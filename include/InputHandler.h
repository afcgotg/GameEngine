#include <SDL2/SDL.h>
#include <vector>

class InputHandler{
    public:
        static InputHandler* Instance();

        void update();
        void clean();

        void initialiseJoysticks();
        bool joysticksInitialised();

    private:

        InputHandler();
        ~InputHandler();

        std::vector<SDL_Joystick*> m_joysticks;
        bool m_bJoysticksInitialised;

        static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;