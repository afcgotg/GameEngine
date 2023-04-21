#ifndef __PauseState__
#define __PauseState__

#include <vector>
#include <string>

#include "GameObject.h"
#include "GameState.h"
#include "Callback.h"
#include "MenuState.h"

class PauseState : public MenuState{
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter(const char* filePath);
        virtual bool onExit();

        virtual std::string getStateID() const;

        virtual void setCallbacks(const std::vector<Callback>& callbacks);

    private:
        static void s_pauseToMain();
        static void s_resumePlay();

        static const std::string s_pauseID;

        std::vector<GameObject*> m_gameObjects;
};

#endif