#include "GameObjectFactory.h"
#include "Player.h"
#include "Enemy.h"

GameObjectFactory* GameObjectFactory::mpInstance = 0;

GameObjectFactory* GameObjectFactory::Instance(){
    if(mpInstance == 0){
        mpInstance = new GameObjectFactory();
    }
    return mpInstance;
}
GameObject* GameObjectFactory::createGameObject(std::string typeID)
{
    std::map<std::string, BaseCreator*>::iterator it = mCreators.find(typeID);
    if(it == mCreators.end())
    {
        std::cout << "could not find type: " << typeID << std::endl;
        return 0;
    }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
    std::map<std::string, BaseCreator*>::iterator it = mCreators.find(typeID);
    if(it != mCreators.end())
    {
        delete pCreator;
        return false;
    }
    mCreators[typeID] = pCreator;
    return true;
}