#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* argv[]){
   
   if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
    // if succeeded create a window
    g_pWindow = SDL_CreateWindow("Chapter 1: Settingup SDL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);

    // if the window creation succeeded create our render
    if(g_pWindow != 0){
        g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
    }else{
        std::cout << "Error when initialize the window: " << SDL_GetError() << std::endl;
    }
   }else{
    return 1; //SDL could not initialize
   }

   // everything succeeded lets draw the window

   // set to black
   // this function expects Red, Green, Blue and Alpha as colour values
   SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

   // clear the window to black
   SDL_RenderClear(g_pRenderer);
   
   // show the window
   SDL_RenderPresent(g_pRenderer);

   //set a delay before quitting
   SDL_Delay(5000);

   // clean up SDL
   SDL_Quit();

   return 0;
}