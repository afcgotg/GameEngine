#include "GameWindow.h"
#include "FileManager.h"
#include "XMLFile.h"

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

void GameWindow::CenterWindow()
{
    mX = SDL_WINDOWPOS_CENTERED;
    mY = SDL_WINDOWPOS_CENTERED;
}

bool GameWindow::LoadSettings()
{
    XMLFile xml;
    if(xml.LoadDocument(TheFileManager::Instance()->GetSettingsFilePath()))
    {
        if(xml.GoToElement("WINDOW"))
        {
            if(xml.GoToElement("values"))
            {
                xml.GetIntAttribute("width", &mWidth);
                xml.GetIntAttribute("height", &mHeight);
                xml.GetStringAttribute("title", &mTitle);
                xml.GetIntAttribute("fps", &mFps);
                xml.GoBack();
            }
            else
            {
                return false;
            }

            if(xml.GoToElement("flags"))
            {
                xml.GetBoolAttribute("fullScreen", &mIsFullScreen);
                xml.GoBack();
            }
            else
            {
                return false;
            }

            if(xml.GoToElement("backgroundColor"))
            {
                xml.GetIntAttribute("red", &mBackgroundColor.red);
                xml.GetIntAttribute("green", &mBackgroundColor.green);
                xml.GetIntAttribute("blue", &mBackgroundColor.blue);
                xml.GetIntAttribute("alpha", &mBackgroundColor.alpha);
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    
    return true;
}

bool GameWindow::Create()
{
    CenterWindow();
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