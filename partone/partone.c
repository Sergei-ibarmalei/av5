#include "partone.h"

static madeShots_t madeShots;


void partOne(sdl_type* sdl, tc* tc, ship_t* hero, status_t* status)
{
    //initMadeShots(&madeShots);
    if(!initMadeShots(&madeShots, tc))
    {
        sdl->gameQuit = true;
        return;
    }
    
    while (!sdl->gameQuit)
    {
        if (status->mainMenu) return;
        SDL_RenderClear(sdl->gRenderer);
        playerAction(sdl, hero, &madeShots, status);
        moveHero(hero);
        showSky(sdl);
        moveSky();
        renderComplexObject(sdl, hero->shipObject);
        showShots(sdl, &madeShots);
        moveShots(&madeShots);
        showBorder(sdl);
        showScoreBanner(sdl);
        showHeroBanner(sdl, status);
        if (status->pause) pauseIsPressed(sdl, hero, &madeShots, status); 
        SDL_RenderPresent(sdl->gRenderer);
        
    }
}

/*TODO make closeMadeShots*/

