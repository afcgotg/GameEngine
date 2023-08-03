#include <string>
#include <vector>

#ifndef __GameState__
#define __GameState__

class GameState{
    public:
        virtual void update() = 0;
        virtual void render() = 0;

        virtual bool onEnter(std::string filePath) = 0;
        virtual bool onExit() = 0;

        virtual std::string getStateID() const = 0;
    
    protected:
        std::vector<std::string> m_textureIDList;
};

#endif