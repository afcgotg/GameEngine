#include "StateParser.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"
#include "FileManager.h"

bool StateParser::parseState(std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs){
    XMLFile xml;
    
    if(xml.LoadDocument(TheFileManager::Instance()->GetStatesFilePath()))
    {
        if(xml.GoToElement(stateID))
        {
            if(xml.GoToElement("TEXTURES"))
            {
                parseTextures(xml, pTextureIDs);
                xml.GoBack();
                if(xml.GoToElement("OBJECTS"))
                {
                    parseObjects(xml, pObjects);
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}
    
void StateParser::parseTextures(XMLFile &xml, std::vector<std::string>* pTextureIDs){
    while(xml.IterateOverElement("texture"))
    {
        std::string fileName;
        xml.GetStringAttribute("filename", &fileName);
        
        std::string id;
        xml.GetStringAttribute("ID", &id);

        if(!TheTextureManager::Instance()->load(fileName, id, TheGameWindow::Instance()->GetRenderer()))
            std::cout << "Error al cargar la textura " << id << " located in: " << fileName << std::endl;
        else
            pTextureIDs->push_back(id);        
    }
    xml.GoBack();
}

void StateParser::parseObjects(XMLFile &xml, std::vector<GameObject*>* pObjects){
    while(xml.IterateOverElement("object"))
    {
        int x, y, width, height;
        int numFrames, callbackID, animSpeed;
        std::string textureID, type;

        xml.GetIntAttribute("x", &x);
        xml.GetIntAttribute("y", &y);
        xml.GetIntAttribute("width", &width);
        xml.GetIntAttribute("height", &height);
        xml.GetIntAttribute("numFrames", &numFrames);
        xml.GetIntAttribute("callbackID", &callbackID);
        xml.GetIntAttribute("animSpeed", &animSpeed);
        xml.GetStringAttribute("textureID", &textureID);
        xml.GetStringAttribute("type", &type);

        GameObject* pGameObject = TheGameObjectFactory::Instance()->createGameObject(type);

        pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
        pObjects->push_back(pGameObject);
    }
    xml.GoBack();
}

