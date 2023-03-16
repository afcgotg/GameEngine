#include <iostream>
#include <vector>

#include "../common/tinyxml2.h"
#include "../game_objects/GameObject.h"

class StateParser
{
    public:
        bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);
    
    private:
        void parseObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*>* pObjects);
        void parseTextures(tinyxml2::XMLElement* pTextureRoot, std::vector<std::string>* pTextureIDs);
};