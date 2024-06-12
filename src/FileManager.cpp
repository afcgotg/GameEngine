#include <cstring>

#include "FileManager.h"

FileManager* FileManager::mInstance = nullptr;

FileManager* FileManager::Instance()
{
    if(!mInstance)
        mInstance = new FileManager();
    return mInstance;
}

void FileManager::SetExecutionPath(char* path)
{
    char* lastSlash = strrchr(path, mSlash[0]);
    if(lastSlash != nullptr) 
        *lastSlash = '\0';
    mExecutionPath = std::string(path);
}

std::string FileManager::GetStatesFilePath() const
{
    return mExecutionPath + std::string(mSlash) + "assets" + std::string(mSlash) + "states.xml";
}

std::string FileManager::GetSettingsFilePath() const
{
    return mExecutionPath + std::string(mSlash) + "assets" + std::string(mSlash) + "settings.xml";
}