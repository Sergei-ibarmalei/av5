//#include "gamecore/gamecore.h"
#include "partone/partone.h"
#include "mainmenu/mainmenu.h"

int main()
{
    sdl_type sdl;
    font_type* gameFonts;
    tc textsColl;
    ship_t hero;
    plot   hero_start;
    status_t gameStatus;
    
    if (sdlInit(&sdl, S_W, S_H, "app") == false)
    {
        sdlClose(&sdl);
        return 1;
    }

    if (!(gameFonts = initGameFonts()))
    {
        sdlClose(&sdl);
        return 1;
    }


    if (initTextsCollection(&sdl, &textsColl, gameFonts) == false)
    {
        sdlClose(&sdl); return 1;
    }

    hero_start.x = S_W /2;
    hero_start.y = S_H/2;
    if (initHero(&textsColl, &hero, &hero_start) == false)
    {
        printf("Failed to initialize hero.\n");
        sdlClose(&sdl);
        return 1;
    }

    if (!makeNoAction(&textsColl))
    {
        closeNoAction();
        allTexturesFree(&textsColl);
        closeHero(&hero);
        sdlClose(&sdl);
        return 1;
    }

    initGameStatus(&gameStatus);

    while(!sdl.gameQuit)
    {
        SDL_RenderClear(sdl.gRenderer);
        if (gameStatus.mainMenu)
        {
            showMainMenu(&sdl, &textsColl, &gameStatus); 
        }
        if (gameStatus.partOne)
        {
           partOne(&sdl, &textsColl, &hero, &gameStatus);
        }
        continue;
        /*playerAction(&sdl, &hero, &textsColl); 
        moveHero(&hero);
        showSky(&sdl);
        moveSky();
        renderComplexObject(&sdl, hero.shipObject);

        showBorder(&sdl);
        showScoreBanner(&sdl);
        showHeroBanner(&sdl, &gameStatus);

        SDL_RenderPresent(sdl.gRenderer);*/
    }
    



    closeGameFonts(gameFonts);
    closeHero(&hero);
    allTexturesFree(&textsColl);
    sdlClose(&sdl);
    return 0;
}
