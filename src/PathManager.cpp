#include <cstring>

#include "PathManager.h"

PathManager* PathManager::mInstance = nullptr;

PathManager* PathManager::Instance()
{
    if(!mInstance)
    {
        mInstance = new PathManager();
    }
    return mInstance;
}

void PathManager::SetExecutionPath(char* path)
{
    char* lastSlash = strrchr(path, mSlash[0]);
    if(lastSlash != nullptr) 
        *lastSlash = '\0';

    mExecutionPath = std::string(path);
}

std::string PathManager::GetExecutionPath() const
{
    return mExecutionPath;
}

std::string PathManager::GetAssetsPath() const
{
    return mExecutionPath + std::string(mSlash) + "assets";
}