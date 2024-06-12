#include <iostream>
#include <math.h>

#include "InputHandler.h"
#include "Game.h"
 
InputHandler* InputHandler::s_pInstance = nullptr;
 
InputHandler* InputHandler::Instance(){
    if(!s_pInstance){
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
}

void InputHandler::AddXBOXController(){
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if(SDL_NumJoysticks() > 0){
        do{
            XBOXController XBOXController(mXBOXControllersVector.size());
            SDL_JoystickEventState(SDL_ENABLE);
            if(XBOXController.Initialise()){
                mXBOXControllersVector.push_back(XBOXController);
            }
        }while(static_cast<int>(mXBOXControllersVector.size()) < SDL_NumJoysticks());
    }
}

void InputHandler::HandleEvent()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {    
        switch(event.type)
        {
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
    for(unsigned int i = 0; i < mXBOXControllersVector.size(); i++){
        mXBOXControllersVector[i].Close();
    }
}

bool InputHandler::getMouseButtonState(size_t buttonNumber){
    return mMouseButtonStates[buttonNumber];
}

void InputHandler::reset(){

}

Vector2D* InputHandler::getMousePosition()
{
    return mMousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if(mKeystates != NULL)
        return mKeystates[key] == 1;
    return false;
}

void InputHandler::onMouseMove(SDL_Event& event)
{
    mMousePosition->setX(event.motion.x);
    mMousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
        mMouseButtonStates[LEFT] = true;
    
    if(event.button.button == SDL_BUTTON_MIDDLE)
        mMouseButtonStates[MIDDLE] = true;
    
    if(event.button.button == SDL_BUTTON_RIGHT)
        mMouseButtonStates[RIGHT] = true;
}

void InputHandler::onMouseButtonUp(SDL_Event& event){
    if(event.button.button == SDL_BUTTON_LEFT)
        mMouseButtonStates[LEFT] = false;

    if(event.button.button == SDL_BUTTON_MIDDLE)
        mMouseButtonStates[MIDDLE] = false;
    
    if(event.button.button == SDL_BUTTON_RIGHT)
        mMouseButtonStates[RIGHT] = false;
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
    XBOXController controller = mXBOXControllersVector[event.jaxis.which]; //get which controller
    
    // left stick move left or right
    if(static_cast<size_t>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_LEFTX)
    {
        if(event.jaxis.value > controller.GetJoystickDeadZone())
            controller.SetLXValue(1);
        else if(event.jaxis.value < -controller.GetJoystickDeadZone())
            controller.SetLXValue(-1);
        else
            controller.SetLXValue(0);
    }

    // left stick move up or down
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_LEFTY){
        if(event.jaxis.value > controller.GetJoystickDeadZone()){
            controller.SetLYValue(1);
        }else if(event.jaxis.value < -controller.GetJoystickDeadZone()){
            controller.SetLYValue(-1);
        }else{
            controller.SetLYValue(0);
        }
    }

    // right stick move left or right
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_RIGHTX){
        if(event.jaxis.value > controller.GetJoystickDeadZone()){
            controller.SetRXValue(1);
        }else if(event.jaxis.value < -controller.GetJoystickDeadZone()){
            controller.SetRXValue(-1);
        }else{
            controller.SetRXValue(0);
        }
    }

    // right stick move up or down
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_RIGHTY){
        if(event.jaxis.value > controller.GetJoystickDeadZone()){
            controller.SetRYValue(1);
        }else if(event.jaxis.value < -controller.GetJoystickDeadZone()){
            controller.SetRYValue(-1);
        }else{
            controller.SetRYValue(0);
        }
    }

    // LT
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_TRIGGERLEFT){
        Uint32 tempValue = event.jaxis.value + pow(2, 15);
        if(tempValue > controller.GetTriggerDeadZone()){
            controller.SetLTValue(1);
        }else{
            controller.SetLTValue(0);
        }
    }

    // RT
    if(static_cast<int>(event.jaxis.axis) == SDL_CONTROLLER_AXIS_TRIGGERRIGHT){
        uint32_t tempValue = event.jaxis.value + pow(2, 15);
        if(tempValue > controller.GetTriggerDeadZone()){
            controller.SetRTValue(1);
        }else{
            controller.SetRTValue(0);
        }
    }
}

void InputHandler::onJoystickHatMove(SDL_Event& event)
{
    XBOXController controller = mXBOXControllersVector[event.jhat.which]; //get which controller
    switch (event.jhat.value){
        case SDL_HAT_LEFT:
            controller.SetDpadXValue(-1);
            controller.SetDpadYValue(0);
            break;
        case SDL_HAT_LEFTDOWN:
            controller.SetDpadXValue(-1);
            controller.SetDpadYValue(1);
            break;
        case SDL_HAT_DOWN:
            controller.SetDpadXValue(0);
            controller.SetDpadYValue(1);
            break;
        case SDL_HAT_RIGHTDOWN:
            controller.SetDpadXValue(1);
            controller.SetDpadYValue(1);
            break;
        case SDL_HAT_RIGHT:
            controller.SetDpadXValue(1);
            controller.SetDpadYValue(0);
            break;
        case SDL_HAT_RIGHTUP:
            controller.SetDpadXValue(1);
            controller.SetDpadYValue(-1);
            break;
        case SDL_HAT_UP:
            controller.SetDpadXValue(0);
            controller.SetDpadYValue(-1);
            break;
        case SDL_HAT_LEFTUP:
            controller.SetDpadXValue(-1);
            controller.SetDpadYValue(-1);
            break;
        case SDL_HAT_CENTERED:
            controller.SetDpadXValue(0);
            controller.SetDpadYValue(0);
            break;
        default:
            break;
    }
}

void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
    mXBOXControllersVector[event.jbutton.which].SetButtonState(static_cast<size_t>(event.jbutton.button), true);
}

void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
    mXBOXControllersVector[event.jbutton.which].SetButtonState(static_cast<size_t>(event.jbutton.button), false);
}

InputHandler::InputHandler(){
    for(int i = 0; i < 3; i++){
        mMouseButtonStates.push_back(false);
    }
    mMousePosition = new Vector2D(0,0);

    mKeystates = SDL_GetKeyboardState(0);
}