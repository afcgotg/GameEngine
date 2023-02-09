#include <iostream>
#include <math.h>

#include "InputHandler.h"
#include "Game.h"

// WINDOWS XBOX 360 CONTROLLER

#if _WIN32

#define LT 4 // done
#define RT 5 // done

#define LJ_x 0 // done
#define LJ_y 1 // done
#define LJ_b 8 // done

#define RJ_x 2 // done
#define RJ_y 3 // done
#define RJ_b 9 // done

#define UP 5
#define DOWN 5
#define LEFT 5
#define RIGHT 5

#define A = 0 // done
#define B = 1 // done
#define X = 2 // done
#define Y = 3 // done

#define START 7 // done
#define SELECT 6 // done

#elif __linux__

#define LT 4 // done
#define RT 5 // done

#define LJ_x 0 // done
#define LJ_y 1 // done
#define LJ_b 8 // done

#define RJ_x 2 // done
#define RJ_y 3 // done
#define RJ_b 9 // done

#define UP 5
#define DOWN 5
#define LEFT 5
#define RIGHT 5

#define A = 0 // done
#define B = 1 // done
#define X = 2 // done
#define Y = 3 // done

#define START 7 // done
#define SELECT 6 // done

#endif



 
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

                std::vector<bool> tempButtons;
                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++){
                    tempButtons.push_back(false);
                }
                m_buttonStates.push_back(tempButtons);
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
        if(event.type == SDL_QUIT){
            TheGame::Instance()->clean();
        }

        if(event.type == SDL_JOYAXISMOTION){

            int whichOne = event.jaxis.which; //get which controller
            std::cout << (int)event.jaxis.axis << ": " << event.jaxis.value << std::endl;

            // left stick move left or right
            if((int)event.jaxis.axis == LJ_x){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joystickValues[whichOne].first->setX(1);
                }else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joystickValues[whichOne].first->setX(-1);
                }else{
                    m_joystickValues[whichOne].first->setX(0);
                }
            }

            // left stick move up or down
            if((int)event.jaxis.axis == LJ_y){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joystickValues[whichOne].first->setY(1);
                }else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joystickValues[whichOne].first->setY(-1);
                }else{
                    m_joystickValues[whichOne].first->setY(0);
                }
            }

            // right stick move left or right
            if((int)event.jaxis.axis == RJ_x){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joystickValues[whichOne].second->setX(1);
                }else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joystickValues[whichOne].second->setX(-1);
                }else{
                    m_joystickValues[whichOne].second->setX(0);
                }
            }

            // right stick move up or down
            if((int)event.jaxis.axis == RJ_y){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joystickValues[whichOne].second->setY(1);
                }else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joystickValues[whichOne].second->setY(-1);
                }else{
                    m_joystickValues[whichOne].second->setY(0);
                }
            }

            // LT
            if((int)event.jaxis.axis == LT){
                uint32_t tempValue = event.jaxis.value + pow(2, 15);
                std::cout << tempValue << std::endl;
                if(tempValue > m_triggerDeadZone){
                    *(m_triggerValues[whichOne].first) = 1;
                }else{
                    *(m_triggerValues[whichOne].first) = 0;
                }
            }

            // RT
            if((int)event.jaxis.axis == RT){
                uint32_t tempValue = event.jaxis.value + pow(2, 15);
                std::cout << tempValue << std::endl;
                if(tempValue > m_triggerDeadZone){
                    *(m_triggerValues[whichOne].second) = 1;
                }else{
                    *(m_triggerValues[whichOne].second) = 0;
                }
            }
        }

        if(event.type == SDL_JOYBUTTONDOWN){
            std::cout << "Button donw: " << (int)event.jbutton.button << std::endl;
            m_buttonStates[event.jaxis.which][(int)event.jbutton.button] = true;
        }

        if(event.type == SDL_JOYBUTTONUP){
            std::cout << "Button up: " << (int)event.jbutton.button << std::endl;
            m_buttonStates[event.jaxis.which][(int)event.jbutton.button] = false;
        }
    }
}

void InputHandler::clean(){
    if(m_bJoysticksInitialised){
//      for(unsigned int i = 0; i < SDL_NumJoysticks(); i++){
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

int InputHandler::ltValue(int joy){
    if(m_triggerValues.size() > 0){
        return *m_triggerValues[joy].first;
    }else{
        return 0;
    }
}


int InputHandler::rtValue(int joy){
    if(m_triggerValues.size() > 0){
        return *m_triggerValues[joy].first;
    }else{
        return 0;
    }
}

InputHandler::InputHandler(){
}

InputHandler::~InputHandler(){
}