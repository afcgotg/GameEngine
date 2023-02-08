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
        for(int i = 0; i > SDL_NumJoysticks(); i++){
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if(joy == NULL){
                std::cout << "Error to add a controler: " << SDL_GetError() << std::endl;
            }else{
                m_joysticks.push_back(joy);
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

InputHandler::InputHandler(){
}

InputHandler::~InputHandler(){
}