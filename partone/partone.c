#include "partone.h"

void partOne(sdl_type* sdl, tc* tc, ship_t* hero, status_t* status)
{
    while (!sdl->gameQuit)
    {
        SDL_RenderClear(sdl->gRenderer);

        playerAction(sdl, hero, tc);
        moveHero(hero);
        showSky(sdl);
        moveSky();
        renderComplexObject(sdl, hero->shipObject);
        showBorder(sdl);
        showScoreBanner(sdl);
        showHeroBanner(sdl, status);
        SDL_RenderPresent(sdl->gRenderer);
        
    }
}
