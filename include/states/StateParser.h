#include <iostream>
#include <vector>

#include "../common/tinyxml2.h"
#include "../game_objects/GameObject.h"

class StateParser
{
    public:
        bool parserState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects);
    
    private:
        void parserObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*>* pObjects);
        void parseTexture(tinyxml2::XMLElement* pTextureRoot, std::vector<std::string>* pTextureIDs);
};