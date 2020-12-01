#include "CApp.h"
 
CApp::CApp(): Running(true), screen(nullptr) {
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
        return false;
    }
    
    SDL_CreateWindowAndRenderer(0,0, SDL_WINDOW_MAXIMIZED, &screen, &renderer);

    if (screen == nullptr || renderer == nullptr) {
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
}

void CApp::OnCleanup() {
    SDL_Quit();
}