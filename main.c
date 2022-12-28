#include "gamecore/gamecore.h"
#include "mainmenu/mainmenu.h"

int main()
{
    sdl_type sdl;
    font_type* gameFonts;
    tc texturesColleciton;
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


    if (initTextsCollection(&sdl, &texturesColleciton, gameFonts) == false)
    {
        sdlClose(&sdl); return 1;
    }

    hero_start.x = S_W /2;
    hero_start.y = S_H/2;
    if (initHero(&texturesColleciton, &hero, &hero_start) == false)
    {
        printf("Failed to initialize hero.\n");
        sdlClose(&sdl);
        return 1;
    }

    if (!makeNoAction(&texturesColleciton))
    {
        closeNoAction();
        allTexturesFree(&texturesColleciton);
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
            showMainMenu(&sdl, &texturesColleciton, &gameStatus); 
        }
        playerAction(&sdl, &hero, &texturesColleciton); 
        moveHero(&hero);
        showSky(&sdl);
        moveSky();
        renderComplexObject(&sdl, hero.shipObject);

        showBorder(&sdl);
        showScoreBanner(&sdl);

        SDL_RenderPresent(sdl.gRenderer);
    }
    



    closeGameFonts(gameFonts);
    closeHero(&hero);
    allTexturesFree(&texturesColleciton);
    sdlClose(&sdl);
    return 0;
}
