#include "XBOXController.h"

XBOXController::XBOXController(int id)
{
    mID = id;
}

void XBOXController::Close()
{
    SDL_JoystickClose(mController);
}

bool XBOXController::Initialise()
{
    mController = SDL_JoystickOpen(mID);
    if(mController)
    {
        mLJoystick = Vector2D(0,0);
        mRJoystick = Vector2D(0,0);
        mLTrigger = 0;
        mRTrigger = 0;
        mDpadX = 0;
        mDpadY = 0;

        std::vector<bool> mButtonStates;
        for(int j = 0; j < SDL_JoystickNumButtons(mController); j++)
        {
            mButtonStates.push_back(false);
        }
        return true;
    }

    std::cout << "Error to add controler " << mID << ": " << SDL_GetError() << std::endl;
    return false;

}

bool XBOXController::IsInitialised()
{
    return mIsInitialised;
}

const int XBOXController::GetJoystickDeadZone(){
    return mJoystickDeadZone;
}

const uint32_t XBOXController::GetTriggerDeadZone(){
    return mTriggerDeadZone;
}

bool XBOXController::GetButtonState(size_t buttonNumber)
{
    return mButtonStates[buttonNumber];
}

void XBOXController::SetButtonState(size_t buttonNumber, bool state){
    mButtonStates[buttonNumber] = state;
}

int XBOXController::GetLXValue(){
        return mLJoystick.getX();
}

int XBOXController::GetLYValue(){
        return mLJoystick.getY();
}

int XBOXController::GetRXValue(){
        return mRJoystick.getX();
}

int XBOXController::GetRYValue(){
        return mRJoystick.getY();
}

int XBOXController::GetDpadXValue(){
    return mDpadX;
}

int XBOXController::GetDpadYValue(){
    return mDpadY;
}

int XBOXController::GetLTValue(){
    return mLTrigger;
}

int XBOXController::GetRTValue(){
    return mRTrigger;
}

void XBOXController::SetLXValue(int value){
    mLJoystick.setX(value);
}

void XBOXController::SetLYValue(int value){
    mLJoystick.setY(value);
}

void XBOXController::SetRXValue(int value){
    mRJoystick.setX(value);
}

void XBOXController::SetRYValue(int value){
    mRJoystick.setY(value);
}

void XBOXController::SetDpadXValue(int value){
    mDpadX = value;
}

void XBOXController::SetDpadYValue(int value){
    mDpadY = value;
}

void XBOXController::SetLTValue(int value){
    mLTrigger = value;
}

void XBOXController::SetRTValue(int value){
    mRTrigger = value;
}