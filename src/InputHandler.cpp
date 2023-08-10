#include <iostream>
#include <math.h>

#include "InputHandler.h"
#include "Game.h"
 
InputHandler* InputHandler::s_pInstance = 0;
 
InputHandler* InputHandler::Instance(){
    if(s_pInstance == 0){
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
}

void InputHandler::InitialiseJoysticks(){
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if(SDL_NumJoysticks() > 0){
        for(int i = 0; i < SDL_NumJoysticks(); i++){
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if(joy != NULL){
                mJoysticks.push_back(joy);
                mJoystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
                mTriggerValues.push_back(std::make_pair(new int(0), new int(0)));
                mDpadValues.push_back(std::make_pair(new int(0), new int(0)));

                std::vector<bool> tempButtons;
                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++){
                    tempButtons.push_back(false);
                }
                mButtonStates.push_back(tempButtons);

                std::cout << "Joystick " << i + 1 << " has " << SDL_JoystickNumButtons(joy) << " buttons." << std::endl;
            }else{
                std::cout << "Error to add a controler: " << SDL_GetError() << std::endl;
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        mJoysticksInitialised = true;

        std::cout << "Initialised " << mJoysticks.size() << " joysticks(s)" << std::endl;
    }else{
        mJoysticksInitialised = false;
    }
}

bool InputHandler::joysticksInitialised(){
    return mJoysticksInitialised;
}

bool InputHandler::getButtonState(size_t joy, size_t buttonNumber){
    return mButtonStates[joy][buttonNumber];
}

void InputHandler::HandleEvent(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        
        switch(event.type){
            case SDL_QUIT:
                TheGame::Instance()->Clean();
                break;

            case SDL_JOYAXISMOTION:
                onJoystickAxisMove(event);
                break;

            case SDL_JOYHATMOTION:
                onJoystickHatMove(event);
                break;
            
            case SDL_JOYBUTTONDOWN:
                onJoystickButtonDown(event);
                break;

            case SDL_JOYBUTTONUP:
                onJoystickButtonUp(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;
            
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;

            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;
            default:
                break;
        }

    }
}

void InputHandler::clean(){
    if(mJoysticksInitialised){
        for(unsigned int i = 0; i < mJoysticks.size(); i++){
            SDL_JoystickClose(mJoysticks[i]);
        }
    }
}

int InputHandler::xValue(size_t joy, int stick){
    if(mJoystickValues.size() > 0){
        if(stick == 1){
            return mJoystickValues[joy].first->getX();
        }else if(stick == 2){
            return mJoystickValues[joy].second->getX();
        }
    }
    return 0;
}
int InputHandler::yValue(size_t joy, int stick){
    if(mJoystickValues.size() > 0){
        if(stick == 1){
            return mJoystickValues[joy].first->getY();
        }else if(stick == 2){
            return mJoystickValues[joy].second->getY();
        }
    }
    return 0;
}

int InputHandler::dpad_xValue(size_t joy){
    if(mJoystickValues.size() > 0){
        return *mDpadValues[joy].first;
    }
    return 0;
}

int InputHandler::dpad_yValue(size_t joy){
    if(mJoystickValues.size() > 0){
        return *mDpadValues[joy].second;
    }
    return 0;
}

int InputHandler::ltValue(size_t joy){
    if(mTriggerValues.size() > 0){
        return *mTriggerValues[joy].first;
    }else{
        return 0;
    }
}


int InputHandler::rtValue(size_t joy){
    if(mTriggerValues.size() > 0){
        return *mTriggerValues[joy].second;
    }else{
        return 0;
    }
}

bool InputHandler::getMouseButtonState(size_t buttonNumber){
    return mMouseButtonStates[buttonNumber];
}

void InputHandler::reset(){

}

Vector2D* InputHandler::getMousePosition(){
    return mMousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key){
    if(mKeystates != NULL){
        return mKeystates[key] == 1;
    }
    return false;
}

void InputHandler::onMouseMove(SDL_Event& event){
    mMousePosition->setX(event.motion.x);
    mMousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event){
    if(event.button.button == SDL_BUTTON_LEFT){
        mMouseButtonStates[LEFT] = true;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE){
        mMouseButtonStates[MIDDLE] = true;
    }
    
    if(event.button.button == SDL_BUTTON_RIGHT){
        mMouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& event){
    if(event.button.button == SDL_BUTTON_LEFT){
        mMouseButtonStates[LEFT] = false;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE){
        mMouseButtonStates[MIDDLE] = false;
    }
    
    if(event.button.button == SDL_BUTTON_RIGHT){
        mMouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::onJoystickAxisMove(SDL_Event& event){
    size_t whichOne = static_cast<size_t>(event.jaxis.which); //get which controller
    // std::cout << (int)event.jaxis.axis << ": " << event.jaxis.value << std::endl;

    // left stick move left or right
    if(static_cast<size_t>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_LEFTX){
        if(event.jaxis.value > mJoystickDeadZone){
            mJoystickValues[whichOne].first->setX(1);
        }else if(event.jaxis.value < -mJoystickDeadZone){
            mJoystickValues[whichOne].first->setX(-1);
        }else{
            mJoystickValues[whichOne].first->setX(0);
        }
    }

    // left stick move up or down
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_LEFTY){
        if(event.jaxis.value > mJoystickDeadZone){
            mJoystickValues[whichOne].first->setY(1);
        }else if(event.jaxis.value < -mJoystickDeadZone){
            mJoystickValues[whichOne].first->setY(-1);
        }else{
            mJoystickValues[whichOne].first->setY(0);
        }
    }

    // right stick move left or right
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_RIGHTX){
        if(event.jaxis.value > mJoystickDeadZone){
            mJoystickValues[whichOne].second->setX(1);
        }else if(event.jaxis.value < -mJoystickDeadZone){
            mJoystickValues[whichOne].second->setX(-1);
        }else{
            mJoystickValues[whichOne].second->setX(0);
        }
    }

    // right stick move up or down
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_RIGHTY){
        if(event.jaxis.value > mJoystickDeadZone){
            mJoystickValues[whichOne].second->setY(1);
        }else if(event.jaxis.value < -mJoystickDeadZone){
            mJoystickValues[whichOne].second->setY(-1);
        }else{
            mJoystickValues[whichOne].second->setY(0);
        }
    }

    // LT
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_TRIGGERLEFT){
        Uint32 tempValue = event.jaxis.value + pow(2, 15);
        if(tempValue > mTriggerDeadZone){
            *(mTriggerValues[whichOne].first) = 1;
        }else{
            *(mTriggerValues[whichOne].first) = 0;
        }
    }

    // RT
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_TRIGGERRIGHT){
        uint32_t tempValue = event.jaxis.value + pow(2, 15);
        if(tempValue > mTriggerDeadZone){
            *(mTriggerValues[whichOne].second) = 1;
        }else{
            *(mTriggerValues[whichOne].second) = 0;
        }
    }
}

void InputHandler::onJoystickHatMove(SDL_Event& event){
    size_t whichOne = static_cast<size_t>(event.jhat.which);
    switch (event.jhat.value){
        case SDL_HAT_LEFT:
            *(mDpadValues[whichOne].first) = -1;
            *(mDpadValues[whichOne].second) = 0;
            break;
        case SDL_HAT_LEFTDOWN:
            *(mDpadValues[whichOne].first) = -1;
            *(mDpadValues[whichOne].second) = 1;
            break;
        case SDL_HAT_DOWN:
            *(mDpadValues[whichOne].first) = 0;
            *(mDpadValues[whichOne].second) = 1;
            break;
        case SDL_HAT_RIGHTDOWN:
            *(mDpadValues[whichOne].first) = 1;
            *(mDpadValues[whichOne].second) = 1;
            break;
        case SDL_HAT_RIGHT:
            *(mDpadValues[whichOne].first) = 1;
            *(mDpadValues[whichOne].second) = 0;
            break;
        case SDL_HAT_RIGHTUP:
            *(mDpadValues[whichOne].first) = 1;
            *(mDpadValues[whichOne].second) = -1;
            break;
        case SDL_HAT_UP:
            *(mDpadValues[whichOne].first) = 0;
            *(mDpadValues[whichOne].second) = -1;
            break;
        case SDL_HAT_LEFTUP:
            *(mDpadValues[whichOne].first) = 0;
            *(mDpadValues[whichOne].second) = -1;
            break;
        case SDL_HAT_CENTERED:
            *(mDpadValues[whichOne].first) = 0;
            *(mDpadValues[whichOne].second) = 0;
            break;
        default:
            break;
    }
}

void InputHandler::onJoystickButtonDown(SDL_Event& event){
    // std::cout << "Button down: " << (int)event.jbutton.button << std::endl;
    mButtonStates[static_cast<size_t>(event.jbutton.which)][static_cast<size_t>(event.jbutton.button)] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event){
    // std::cout << "Button up: " << (int)event.jbutton.button << std::endl;
    mButtonStates[static_cast<size_t>(event.jbutton.which)][static_cast<size_t>(event.jbutton.button)] = false;
}

InputHandler::InputHandler(){
    for(int i = 0; i < 3; i++){
        mMouseButtonStates.push_back(false);
    }
    mMousePosition = new Vector2D(0,0);

    mKeystates = SDL_GetKeyboardState(0);
}