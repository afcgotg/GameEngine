#include "StateParser.h"
#include "../Game.h"
#include "../gears/TextureManager.h"
#include "../gears/GameObjectFactory.h"
#include "../gears/LoaderParams.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs){
    tinyxml2::XMLDocument xmlDoc;

    std::cout << stateFile << std::endl;
    std::cin.get();

    if(xmlDoc.LoadFile(stateFile)){
        std::cout << xmlDoc.ErrorStr() << std::endl;
        return false;
    }

    tinyxml2::XMLElement* pRoot = xmlDoc.RootElement(); // <STATES>
    tinyxml2::XMLElement* pStateRoot = 0;

    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == stateID){
            std::cout << "State encontrado" << std::endl;
            std::cin.get();
            pStateRoot = e;
            break;
        }
    }

    tinyxml2::XMLElement* pTextureRoot = 0;
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == std::string("TEXTURES")) pTextureRoot = e;
    }
    parseTextures(pTextureRoot, pTextureIDs);
    std::cout << "Texturas cargadas" << std::endl;
    std::cin.get();

    tinyxml2::XMLElement* pObjectRoot = 0;
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == std::string("OBJECTS")) pObjectRoot = e;
    }
    parseObjects(pObjectRoot, pObjects);
        std::cout << "Objetos cargados" << std::endl;
    std::cin.get();

    return true;
}
    
void StateParser::parseTextures(tinyxml2::XMLElement* pTextureRoot, std::vector<std::string>* pTextureIDs){
    for(tinyxml2::XMLElement* e = pTextureRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        std::cout << "Entra" << std::endl;
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute);
        if(!TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer())){
            std::cout << "Error al cargar la textura " << idAttribute << " located in: " << filenameAttribute << std::endl;
            std::cin.get();
        }else{
            pTextureIDs->push_back(idAttribute);
        }
    }
}

void StateParser::parseObjects(tinyxml2::XMLElement* pObjectRoot, std::vector<GameObject*>* pObjects){
    for(tinyxml2::XMLElement* e = pObjectRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        int x, y, width, height, numFrames, callbackID, animSpeed;
        std::string textureID;

        e->QueryIntAttribute("x", &x);
        e->QueryIntAttribute("y", &y);
        e->QueryIntAttribute("width", &width);
        e->QueryIntAttribute("height", &height);
        e->QueryIntAttribute("numFrames", &numFrames);
        e->QueryIntAttribute("callbackID", &callbackID);
        e->QueryIntAttribute("animSpeed", &animSpeed);
        textureID = e->Attribute("textureID");

        GameObject* pGameObject = TheGameObjectFactory::Instance()->createGameObject(e->Attribute("type"));

        pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
        pObjects->push_back(pGameObject);
        
    }
}
