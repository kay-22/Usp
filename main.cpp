#include "basics/CApp.h"
#include <iostream>

using std::cerr;
using std::endl;
using std::cout;

int main( int argc, char** argv )
{
    CApp theApp;
 
    // //Start SDL
    // SDL_Init( SDL_INIT_EVERYTHING );
    
    // //Quit SDL
    // SDL_Quit();
    int exit = theApp.OnExecute();

    return exit;   
}