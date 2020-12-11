#include "CApp.h"

using std::cerr;
using std::endl;
 
CApp::CApp(): Running(true), screen(nullptr), renderer(nullptr), image(nullptr), image_rec() {
}
 
int CApp::OnExecute() {
    if (OnInit() == false) {
        return -1;
    }
 
    SDL_Event Event;
 
    while (Running) {
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
 
        OnLoop();
        OnRender();
    }
 
    OnCleanup();
    return 0;
}

bool CApp::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cerr << SDL_GetError() << endl;
        return false;
    }
    
    SDL_CreateWindowAndRenderer(0,0, SDL_WINDOW_MAXIMIZED, &screen, &renderer);

    if (screen == nullptr || renderer == nullptr) {
        cerr << SDL_GetError() << endl;
        return false;
    }

    SDL_Surface* temp = SDL_LoadBMP("hi.bmp");

    if (temp == nullptr) {
        cerr << SDL_GetError() << endl;
        return false;
    }

    image = SDL_CreateTextureFromSurface(renderer, temp);
    image_rec = temp->clip_rect;
    SDL_FreeSurface(temp);

    if (image == nullptr) {
        cerr << SDL_GetError() << endl;
        return false;
    }
    

    return true;
}
void CApp::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_QUIT) {
        Running = false;
    }
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, image, nullptr, &image_rec);
    SDL_RenderPresent(renderer);
}

void CApp::OnCleanup() {
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
}