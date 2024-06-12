#include "TextureManager.h"

TextureManager* TextureManager::mpInstance = 0;

TextureManager* TextureManager::Instance(){
    if(mpInstance == 0){
        mpInstance = new TextureManager();
    }
    return mpInstance;
}

TextureManager::TextureManager(){

}

TextureManager::~TextureManager(){

}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer){
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if(pTempSurface == 0){
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if(pTexture != 0){
        mTextureMap[id] = pTexture;
        return true;
    }

    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip){
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, mTextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, uint32_t currentRow, uint32_t currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip){
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * static_cast<int>(currentFrame);
    srcRect.y = height * static_cast<int>(currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, mTextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id){
    mTextureMap.erase(id);
}