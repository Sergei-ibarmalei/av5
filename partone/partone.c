#include "partone.h"

void partOne(sdl_type* sdl, tc* tc, ship_t* hero, status_t* status)
{
    while (!sdl->gameQuit)
    {
        if (status->mainMenu) return;
        SDL_RenderClear(sdl->gRenderer);
        playerAction(sdl, hero, tc, status);
        moveHero(hero);
        showSky(sdl);
        moveSky();
        renderComplexObject(sdl, hero->shipObject);
        showBorder(sdl);
        showScoreBanner(sdl);
        showHeroBanner(sdl, status);
        if (status->pause) pauseIsPressed(sdl, hero, status); 
        SDL_RenderPresent(sdl->gRenderer);
        
    }
}

