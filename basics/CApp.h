#ifndef _CAPP_H_
#define _CAPP_H_
 
#include "SDL2/SDL.h"
#include <iostream>

class CApp {
 
    private:
        bool Running;
        SDL_Window* screen = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* image = nullptr;
        SDL_Rect image_rec;
 
    public:
        CApp();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
};
 
#endif