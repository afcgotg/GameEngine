#include <vector>
#include <string>

#include "../game_objects/GameObject.h"
#include "GameState.h"
#include "MenuState.h"
#include "../common/Callback.h"

#ifndef __GameOverState__
#define __GameOverState__

class GameOverState : public MenuState {
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter(const char* filePath);
        virtual bool onExit();

        virtual std::string getStateID() const;

        virtual void setCallbacks(const std::vector<Callback>& callbacks);

    private:
        static void s_gameOverToMain();
        static void s_restartPlay();

        static const std::string s_gameOverID;

        std::vector<GameObject*> m_gameObjects;
};

#endif