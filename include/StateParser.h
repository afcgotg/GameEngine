#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>

#include "tinyxml2.h"
#include "GameObject.h"

class StateParser{
    public:
        bool parseState(std::string stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);
    
    private:
        void parseObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*>* pObjects);
        void parseTextures(tinyxml2::XMLElement* pTextureRoot, std::vector<std::string>* pTextureIDs);
};

#endif