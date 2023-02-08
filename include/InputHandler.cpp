#include <iostream> 

 #include "InputHandler.h"
 #include "Game.h"
 
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
            if(joy == NULL){
                std::cout << "Error to add a controler: " << SDL_GetError() << std::endl;
            }else{
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
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
            if((int)event.jaxis.axis == 0){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joystickValues[whichOne].first->setX(1);
                }else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joystickValues[whichOne].first->setX(-1);
                }else{
                    m_joystickValues[whichOne].first->setX(0);
                }
            }

            // left stick move up or down
            if((int)event.jaxis.axis == 1){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joystickValues[whichOne].first->setY(1);
                }else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joystickValues[whichOne].first->setY(-1);
                }else{
                    m_joystickValues[whichOne].first->setY(0);
                }
            }

            // left stick move left or right
            if((int)event.jaxis.axis == 2){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joystickValues[whichOne].second->setX(1);
                }else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joystickValues[whichOne].second->setX(-1);
                }else{
                    m_joystickValues[whichOne].second->setX(0);
                }
            }

            // left stick move up or down
            if((int)event.jaxis.axis == 3){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joystickValues[whichOne].second->setY(1);
                }else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joystickValues[whichOne].second->setY(-1);
                }else{
                    m_joystickValues[whichOne].second->setY(0);
                }
            }
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

InputHandler::InputHandler(){
}

InputHandler::~InputHandler(){
}