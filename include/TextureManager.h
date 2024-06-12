#include <string>
#include <map>

#include <../SDL2/include/SDL2/SDL.h>
#include <../SDL2/include/SDL2/SDL_image.h>

#ifndef __TextureManager__
#define __TextureManager__

class TextureManager{
    public: 
        static TextureManager* Instance();

        ~TextureManager();
    
        bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

        void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip=SDL_FLIP_NONE);

        void drawFrame(std::string id, int x, int y, int width, int height, uint32_t currentRow, uint32_t currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip=SDL_FLIP_NONE);

        void clearFromTextureMap(std::string id);

    private:
        TextureManager();

        static TextureManager* mpInstance;

        std::map<std::string, SDL_Texture*> mTextureMap;
};

typedef TextureManager TheTextureManager;

#endif