#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>

#include "XMLFile.h"
#include "GameObject.h"

class StateParser{
    public:
        bool parseState(std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);
    
    private:
        void parseObjects(XMLFile &xml, std::vector<GameObject*>* pObjects);
        void parseTextures(XMLFile &xml, std::vector<std::string>* pTextureIDs);
};

#endif