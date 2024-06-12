#include <vector>

#include "../SDL2/include/SDL2/SDL.h"
#include "Vector2D.h"

class XBOXController
{
    public:
        XBOXController(int id);
        ~XBOXController(){};

        bool Initialise();
        bool IsInitialised();

        const int GetJoystickDeadZone();
        const uint32_t GetTriggerDeadZone();

        bool GetButtonState(size_t buttonNumber);
        void SetButtonState(size_t buttonNumber, bool state);

        int GetLXValue();
        int GetLYValue();
        int GetRXValue();
        int GetRYValue();

        int GetDpadXValue();
        int GetDpadYValue();

        int GetLTValue();
        int GetRTValue();

        void SetLXValue(int value);
        void SetLYValue(int value);
        void SetRXValue(int value);
        void SetRYValue(int value);

        void SetDpadXValue(int value);
        void SetDpadYValue(int value);

        void SetLTValue(int value);
        void SetRTValue(int value);

        void Close();

    private:
        SDL_Joystick* mController;
        int mID;
        bool mIsInitialised;

        Vector2D mLJoystick;
        Vector2D mRJoystick;
        const int mJoystickDeadZone = 10000;

        int mLTrigger;
        int mRTrigger;
        const uint32_t mTriggerDeadZone = 10000;

        int mDpadX;
        int mDpadY;

        std::vector<bool> mButtonStates;
};