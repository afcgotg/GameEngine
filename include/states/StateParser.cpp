#include "StateParser.h"

bool StateParser::parserState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects)
{
    tinyxml2::XMLDocument xmlDoc;
    if(!xmlDoc.LoadFile(stateFile))
    {
        return false;
    }
    tinyxml2::XMLElement* pRoot = xmlDoc.RootElement();
    
    tinyxml2::XMLElement* pStateRoot = 0;
    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == stateID) pStateRoot = e;
    }

    tinyxml2::XMLElement* pTextureRoot = 0;
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("TEXTURES")) pTextureRoot = e;
    }

    parseTextures(pTextureRoot, pTextureIDs);

    tinyxml2::XMLElement* pObjectRoot = 0;
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("OBJECTS")) pObjectRoot = e;
    }

    parseObjects(pObjectRoot, pObjects);

    return true;
}
    
void StateParser::parserObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*>* pObjects)
{

}

void StateParser::parseTexture(tinyxml2::XMLElement* pTextureRoot, std::vector<std::string>* pTextureIDs)
{

}