#include "mainmenu.h"




void showMainMenu(sdl_type* sdl, tc* collection, status_t* status)
{
    while (!sdl->gameQuit)
    {
        SDL_RenderClear(sdl->gRenderer);


        SDL_RenderPresent(sdl->gRenderer);
    }
}