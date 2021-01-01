#include "CApp.h"

using std::cerr;
using std::endl;

static const char STEP = 7;
static const bool KEY_DOWN = true;
static void updateKeyboard(bool* keys_state, SDL_Keycode key, bool state);
static void moveRect(SDL_Rect& rect, bool* keys_state);

enum Directions {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

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

    SDL_Surface* Loading_Surf = SDL_LoadBMP("hi.bmp");

    if (Loading_Surf == nullptr) {
        cerr << SDL_GetError() << endl;
        return false;
    }

    image = SDL_CreateTextureFromSurface(renderer, Loading_Surf);
    image_rec = Loading_Surf->clip_rect;
    SDL_FreeSurface(Loading_Surf);

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
    else if (Event->type == SDL_KEYDOWN) {
        updateKeyboard(keys_state, Event->key.keysym.sym, KEY_DOWN);
    }
    else if (Event->type == SDL_KEYUP) {
        updateKeyboard(keys_state, Event->key.keysym.sym, !KEY_DOWN);
    }

    moveRect(image_rec, keys_state);
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

static void updateKeyboard(bool* keys_state, SDL_Keycode key, bool state) {
    switch (key)
    {
    case SDLK_UP:
        keys_state[UP] = state;
        break;

    case SDLK_DOWN:
        keys_state[DOWN] = state;
        break;

    case SDLK_RIGHT:
        keys_state[RIGHT] = state;
        break;

    case SDLK_LEFT:
        keys_state[LEFT] = state;
        break;
    
    default:
        break;
    }
}

static void moveRect(SDL_Rect& rect, bool* keys_state){
    if (keys_state[UP] == KEY_DOWN) {
        if (keys_state[DOWN] == !KEY_DOWN){
            rect.y -= STEP;
        }
        if (keys_state[RIGHT] == KEY_DOWN) {
            rect.x += STEP;
        }
        else if (keys_state[LEFT] == KEY_DOWN) {
            rect.x -= STEP;
        }
    }
    else if (keys_state[DOWN] == KEY_DOWN) {
        if (keys_state[UP] == !KEY_DOWN){
            rect.y += STEP;
        }
        if (keys_state[RIGHT] == KEY_DOWN) {
            rect.x += STEP;
        }
        else if (keys_state[LEFT] == KEY_DOWN) {
            rect.x -= STEP;
        }
    }
    else if (keys_state[RIGHT] == KEY_DOWN) {
        if (keys_state[LEFT] == !KEY_DOWN){
            rect.x += STEP;
        }
        if (keys_state[UP] == KEY_DOWN) {
            rect.y -= STEP;
        }
        else if (keys_state[DOWN] == KEY_DOWN) {
            rect.y += STEP;
        }
    }    
    else if (keys_state[LEFT] == KEY_DOWN) {
        if (keys_state[RIGHT] == !KEY_DOWN){
            rect.x -= STEP;
        }
        if (keys_state[UP] == KEY_DOWN) {
            rect.y -= STEP;
        }
        else if (keys_state[DOWN] == KEY_DOWN) {
            rect.y += STEP;
        }
    }
}