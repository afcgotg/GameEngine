#include <vector>
#include <string>

#include "../game_objects/GameObject.h"
#include "GameState.h"

class GameOverState : public GameState{
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getStateID() const;

    private:
        static void s_gameOverToMain();
        static void s_restartPlay();

        static const std::string s_gameOverID;

        std::vector<GameObject*> m_gameObjects;
};