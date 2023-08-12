#include "GameWindow.h"
#include "FileManager.h"
#include "tinyxml2.h"

GameWindow* GameWindow::mInstance = nullptr;

GameWindow* GameWindow::Instance()
{
    if(mInstance == nullptr)
        mInstance = new GameWindow();
    return mInstance;
}

void GameWindow::ApplyFlags()
{
    mFlags = 0;
    if(mIsFullScreen)
        mFlags |= SDL_WINDOW_FULLSCREEN;
}

SDL_Renderer* GameWindow::GetRenderer() const{
    return mRenderer;
}

bool GameWindow::LoadSettings()
{
    tinyxml2::XMLDocument xmlDoc;
    std::string filePath = TheFileManager::Instance()->GetSettingsFilePath();

    if(xmlDoc.LoadFile(filePath.c_str())){
        std::cout << xmlDoc.ErrorStr() << std::endl;
        return false;
    }

    tinyxml2::XMLElement* pRoot = xmlDoc.RootElement(); // <SETTINGS>
    tinyxml2::XMLElement* pWindowRoot = 0;

    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == std::string("WINDOW")){
            std::cout << "Window settings found" << std::endl;
            pWindowRoot = e;
            break;
        }
    }

    tinyxml2::XMLElement* e = pWindowRoot->FirstChildElement();

    mX = SDL_WINDOWPOS_CENTERED;
    mY = SDL_WINDOWPOS_CENTERED;
    
    e->QueryIntAttribute("width", &mWidth);
    e->QueryIntAttribute("height", &mHeight);
    mTitle = std::string(e->Attribute("title"));
    e->QueryIntAttribute("fps", &mFps);
    e->QueryBoolAttribute("fullScreen", &mIsFullScreen);

    e = e->NextSiblingElement();

    e->QueryIntAttribute("red", &mBackgroundColor.red);
    e->QueryIntAttribute("green", &mBackgroundColor.green);
    e->QueryIntAttribute("blue", &mBackgroundColor.blue);
    e->QueryIntAttribute("alpha", &mBackgroundColor.alpha);

    return true;
}

bool GameWindow::Create()
{
    LoadSettings();

    mDelayTime = 1000 / mFps;

    ApplyFlags();

    mWindow = SDL_CreateWindow(mTitle.c_str(), mX, mY, mWidth, mHeight, mFlags);

    if(mWindow != nullptr)
    {
        std::cout << "Window creation succed" << std::endl;
        mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
        if(mRenderer != nullptr)
        {
            std::cout << "Renderer creation succed" << std::endl;
            SDL_SetRenderDrawColor(mRenderer, mBackgroundColor.red, mBackgroundColor.green, mBackgroundColor.blue, mBackgroundColor.alpha);
        }
        else
        {
            std::cout << "Error when create the renderer: " << SDL_GetError() << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Error when create the window: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void GameWindow::Destroy()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
}

uint32_t GameWindow::GetDelayTime() const
{
    return mDelayTime;
}