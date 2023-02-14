#include <iostream>
#include <math.h>

#include "InputHandler.h"
#include "../Game.h"
 
InputHandler* InputHandler::s_pInstance = 0;
 
InputHandler* InputHandler::Instance(){
    if(s_pInstance == 0){
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
}

void InputHandler::initialiseJoysticks(){
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if(SDL_NumJoysticks() > 0){
        for(int i = 0; i < SDL_NumJoysticks(); i++){
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if(joy != NULL){
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
                m_triggerValues.push_back(std::make_pair(new int(0), new int(0)));
                m_dpadValues.push_back(std::make_pair(new int(0), new int(0)));

                std::vector<bool> tempButtons;
                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++){
                    tempButtons.push_back(false);
                }
                m_buttonStates.push_back(tempButtons);

                std::cout << "Joystick " << i + 1 << " has " << SDL_JoystickNumButtons(joy) << " buttons." << std::endl;
            }else{
                std::cout << "Error to add a controler: " << SDL_GetError() << std::endl;
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;

        std::cout << "Initialised " << m_joysticks.size() << " joysticks(s)" << std::endl;
    }else{
        m_bJoysticksInitialised = false;
    }
}

bool InputHandler::joysticksInitialised(){
    return m_bJoysticksInitialised;
}

bool InputHandler::getButtonState(int joy, int buttonNumber){
    return m_buttonStates[joy][buttonNumber];
}

void InputHandler::update(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        
        switch(event.type){
            case SDL_QUIT:
                TheGame::Instance()->clean();
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
        }

    }
}

void InputHandler::clean(){
    if(m_bJoysticksInitialised){
        for(unsigned int i = 0; i < m_joysticks.size(); i++){
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

int InputHandler::xValue(int joy, int stick){
    if(m_joystickValues.size() > 0){
        if(stick == 1){
            return m_joystickValues[joy].first->getX();
        }else if(stick == 2){
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}
int InputHandler::yValue(int joy, int stick){
    if(m_joystickValues.size() > 0){
        if(stick == 1){
            return m_joystickValues[joy].first->getY();
        }else if(stick == 2){
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}

int InputHandler::dpad_xValue(int joy){
    if(m_joystickValues.size() > 0){
        return *m_dpadValues[joy].first;
    }
    return 0;
}

int InputHandler::dpad_yValue(int joy){
    if(m_joystickValues.size() > 0){
        return *m_dpadValues[joy].second;
    }
    return 0;
}

int InputHandler::ltValue(int joy){
    if(m_triggerValues.size() > 0){
        return *m_triggerValues[joy].first;
    }else{
        return 0;
    }
}


int InputHandler::rtValue(int joy){
    if(m_triggerValues.size() > 0){
        return *m_triggerValues[joy].second;
    }else{
        return 0;
    }
}

bool InputHandler::getMouseButtonState(int buttonNumber){
    return m_mouseButtonStates[buttonNumber];
}

void InputHandler::reset(){

}

Vector2D* InputHandler::getMousePosition(){
    return m_mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key){
    if(m_keystates != NULL){
        return m_keystates[key] == 1;
    }
    return false;
}

void InputHandler::onMouseMove(SDL_Event& event){
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event){
    if(event.button.button == SDL_BUTTON_LEFT){
        m_mouseButtonStates[LEFT] = true;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE){
        m_mouseButtonStates[MIDDLE] = true;
    }
    
    if(event.button.button == SDL_BUTTON_RIGHT){
        m_mouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& event){
    if(event.button.button == SDL_BUTTON_LEFT){
        m_mouseButtonStates[LEFT] = false;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE){
        m_mouseButtonStates[MIDDLE] = false;
    }
    
    if(event.button.button == SDL_BUTTON_RIGHT){
        m_mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::onJoystickAxisMove(SDL_Event& event){
    int whichOne = event.jaxis.which; //get which controller
    // std::cout << (int)event.jaxis.axis << ": " << event.jaxis.value << std::endl;

    // left stick move left or right
    if((int)event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTX){
        if(event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].first->setX(1);
        }else if(event.jaxis.value < -m_joystickDeadZone){
            m_joystickValues[whichOne].first->setX(-1);
        }else{
            m_joystickValues[whichOne].first->setX(0);
        }
    }

    // left stick move up or down
    if((int)event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTY){
        if(event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].first->setY(1);
        }else if(event.jaxis.value < -m_joystickDeadZone){
            m_joystickValues[whichOne].first->setY(-1);
        }else{
            m_joystickValues[whichOne].first->setY(0);
        }
    }

    // right stick move left or right
    if((int)event.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTX){
        if(event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].second->setX(1);
        }else if(event.jaxis.value < -m_joystickDeadZone){
            m_joystickValues[whichOne].second->setX(-1);
        }else{
            m_joystickValues[whichOne].second->setX(0);
        }
    }

    // right stick move up or down
    if((int)event.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTY){
        if(event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].second->setY(1);
        }else if(event.jaxis.value < -m_joystickDeadZone){
            m_joystickValues[whichOne].second->setY(-1);
        }else{
            m_joystickValues[whichOne].second->setY(0);
        }
    }

    // LT
    if((int)event.jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT){
        Uint32 tempValue = event.jaxis.value + pow(2, 15);
        if(tempValue > m_triggerDeadZone){
            *(m_triggerValues[whichOne].first) = 1;
        }else{
            *(m_triggerValues[whichOne].first) = 0;
        }
    }

    // RT
    if((int)event.jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT){
        Uint32 tempValue = event.jaxis.value + pow(2, 15);
        if(tempValue > m_triggerDeadZone){
            *(m_triggerValues[whichOne].second) = 1;
        }else{
            *(m_triggerValues[whichOne].second) = 0;
        }
    }
}

void InputHandler::onJoystickHatMove(SDL_Event& event){
    int whichOne = event.jhat.which;
    switch (event.jhat.value){
        case SDL_HAT_LEFT:
            *(m_dpadValues[whichOne].first) = -1;
            *(m_dpadValues[whichOne].second) = 0;
            break;
        case SDL_HAT_LEFTDOWN:
            *(m_dpadValues[whichOne].first) = -1;
            *(m_dpadValues[whichOne].second) = 1;
            break;
        case SDL_HAT_DOWN:
            *(m_dpadValues[whichOne].first) = 0;
            *(m_dpadValues[whichOne].second) = 1;
            break;
        case SDL_HAT_RIGHTDOWN:
            *(m_dpadValues[whichOne].first) = 1;
            *(m_dpadValues[whichOne].second) = 1;
            break;
        case SDL_HAT_RIGHT:
            *(m_dpadValues[whichOne].first) = 1;
            *(m_dpadValues[whichOne].second) = 0;
            break;
        case SDL_HAT_RIGHTUP:
            *(m_dpadValues[whichOne].first) = 1;
            *(m_dpadValues[whichOne].second) = -1;
            break;
        case SDL_HAT_UP:
            *(m_dpadValues[whichOne].first) = 0;
            *(m_dpadValues[whichOne].second) = -1;
            break;
        case SDL_HAT_LEFTUP:
            *(m_dpadValues[whichOne].first) = 0;
            *(m_dpadValues[whichOne].second) = -1;
            break;
        case SDL_HAT_CENTERED:
            *(m_dpadValues[whichOne].first) = 0;
            *(m_dpadValues[whichOne].second) = 0;
            break;

    }
}

void InputHandler::onJoystickButtonDown(SDL_Event& event){
    // std::cout << "Button down: " << (int)event.jbutton.button << std::endl;
    m_buttonStates[event.jbutton.which][(int)event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event){
    // std::cout << "Button up: " << (int)event.jbutton.button << std::endl;
    m_buttonStates[event.jbutton.which][(int)event.jbutton.button] = false;
}

InputHandler::InputHandler(){
    for(int i = 0; i < 3; i++){
        m_mouseButtonStates.push_back(false);
    }
    m_mousePosition = new Vector2D(0,0);

    m_keystates = SDL_GetKeyboardState(0);
}

InputHandler::~InputHandler(){
}