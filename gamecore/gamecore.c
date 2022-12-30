#include "gamecore.h"
#define PAUSE_STRINGS_LEN 2
#define HEROLIVESBANNERTEXT_LEN 3

bool makeBorder(border_t* border);
void makeScoreBanner(score_t* scoreBanner, simple_type* gameText);
void heroUp(ship_t* hero);
void heroDown(ship_t* hero);
void heroLeft(ship_t* hero);
void heroRight(ship_t* hero);
void stopHero(ship_t* hero);
bool isGonnaCrossUP(ship_t* hero);
bool isGonnaCrossDown(ship_t* hero);
bool isGonnaCrossRight(ship_t* hero);
bool isGonnaCrossLeft(ship_t* hero);
void recomputeHeroLaserPos(ship_t* hero);
void recomputeHeroRects(ship_t* hero);
void recomputeHeroCenter(ship_t* hero);
bool makeMainMenu(tc* collection);
bool makePause(tc* collection);
bool makeHeroLivesBanner(tc* collection);
void showPause(sdl_type* sdl);

enum noaction_pause {na_pause, na_press_esc};
static noaction_t* noaction;



bool makeNoAction(tc* collection)
{
    noaction = NULL;
    noaction = malloc(sizeof(noaction_t));
    if (!noaction)
    {
        printf("Internal error by managing memory of noaction.\n");
        noaction = NULL;
        return false;
    }
    noaction->border = NULL;
    noaction->scoreBanner = NULL;
    noaction->sky = NULL;
    noaction->pause = NULL;
    noaction->heroLivesBan = NULL;

    noaction->heroLivesBan = malloc(sizeof(heroLives_t));
    {
        if (!noaction->heroLivesBan)
        {
            printf("Internal error by managing memory of hero lives banner.\n");
            closeNoAction();
            return false;
        }
    }

    noaction->heroLivesBan->heroLivesTextures = 
        malloc(sizeof(simple_type*));
    if (!noaction->heroLivesBan->heroLivesTextures)
    {
        printf("Internal error by managing memory of hero lives textures.\n");
        closeNoAction();
        return false;
    }
    noaction->heroLivesBan->heroLivesTextures->objTexture = NULL;
    noaction->heroLivesBan->heroLivesTextures->objRect = 
        malloc(sizeof(SDL_Rect));
    if (!noaction->heroLivesBan->heroLivesTextures->objRect)
    {
        printf("Internal error by managing memory of hero ban rect.\n");
        closeNoAction();
        return false;
    }
    noaction->heroLivesBan->heroLivesText = 
        malloc(sizeof(simple_type) * HEROLIVESBANNERTEXT_LEN);
    if (!noaction->heroLivesBan->heroLivesText)
    {
        printf("Internal error by managing memory of hero banner text.\n");
        closeNoAction();
        return false;
    }

    noaction->border = malloc(sizeof(border_t));
    if (!noaction->border)
    {
        printf("Internal error by managing memory of border.\n");
        closeNoAction();
        return false;
    }
    noaction->border->border = NULL;

    noaction->scoreBanner = malloc(sizeof(score_t));
    if (!noaction->scoreBanner)
    {
        printf("Internal error by managing memory of score.\n");
        closeNoAction();
        return false;
    }
    noaction->scoreBanner->scoreTexture = NULL;
    noaction->scoreBanner->scoreTexture = 
        malloc(sizeof(simple_type)*SCORE_BANNER_LEN);
    if  (!noaction->scoreBanner->scoreTexture)
    {
        printf("Internal error by mananging memory of score textures.\n");
        closeNoAction();
        return false;
    }


    noaction->sky = malloc(sizeof(sky_t));
    if (!noaction->sky)
    {
        printf("Internal error by managing memory of sky.\n");
        closeNoAction();
        return false;
    }
    noaction->sky->fast = NULL;
    noaction->sky->slow = NULL;
    noaction->sky->starTexture = NULL;
    noaction->sky->fast = malloc(sizeof(SDL_Rect) * fastStarMax);
    if (noaction->sky->fast == NULL)
    {
        printf("Internal error by managing memory of fast stars.\n");
        closeNoAction();
        return false;
    }
    noaction->sky->slow = malloc(sizeof(SDL_Rect) * slowStarMax);
    if (noaction->sky->slow == NULL)
    {
        printf("Internal error by managing memory of slow stars.\n");
        closeNoAction();
        return false;
    }
    noaction->sky->starTexture = &collection->simpleObj[oneStar];
    if (!noaction->sky->starTexture)
    {
        printf("Cannot create sky, texture is absent.\n");
        closeNoAction();
        return false;
    } 

    /*Pause состоит из Pause и Press esc..*/
    noaction->pause = malloc(sizeof(simple_type) * PAUSE_STRINGS_LEN);
    if (!noaction->pause)
    {
        printf("Internal error by managing memory of pause.\n");
        closeNoAction();
        return false;
    }


    if (!(makeBorder(noaction->border)))
    {
        closeNoAction();
        return false;
    }
    setStarCoord(noaction); 
    makeScoreBanner(noaction->scoreBanner, collection->gameText);
    if (!makeMainMenu(collection))
    {
        closeNoAction();
        return false;
    }
    if (!makePause(collection))
    {
        closeNoAction();
        return false;
    }

    if (!makeHeroLivesBanner(collection))
    {
        closeNoAction();
        return false;
    }
    return true;
}


/*Создание баннера с изображениями жизней героя*/
bool makeHeroLivesBanner(tc* collection)
{
    if (!collection || !collection->complexObj[hero].objTexture)
    {
        printf("Cannot create hero lives banner, textures are absent.\n");
        return false;
    }

    int object;

    /*Берем текстуру героя из коллекции*/
    noaction->heroLivesBan->heroLivesTextures->objTexture =
        collection->complexObj[hero].objTexture;
    noaction->heroLivesBan->heroLivesTextures->objRect->w =
        collection->complexObj[hero].objRectsArr[mainRect].w;
    noaction->heroLivesBan->heroLivesTextures->objRect->h =
        collection->complexObj[hero].objRectsArr[mainRect].h;
    
     

    /*Берем три текстуры х1 х2 х3*/ 
    for (object = 0; object < HEROLIVESBANNERTEXT_LEN; ++object)
    {
        noaction->heroLivesBan->heroLivesText[object] =
            collection->heroBanner[object];
    }
    return true;
}





void makeScoreBanner(score_t* scoreBanner, simple_type* gameText)
{
    int count;
    int scoreBannerX; /*left up corner x*/
    int scoreBannerY; /*left up corner y*/

    /*Ширина цифры*/
    #define SPACE 4
    #define WIDTH gameText[0].objRect->w
    #define BORDER_UP_Y noaction->border->border[borderUp].y
    #define HEIGHT gameText[0].objRect->h

    scoreBannerX = S_W -(SCORE_BANNER_LEN * WIDTH) - (5 * SPACE);
    scoreBannerY = BORDER_UP_Y - SPACE - HEIGHT;

    for (count = 0; count < SCORE_BANNER_LEN; ++count)
    {
        /*Ставим текстуру цифры 0 в каждый сегмент*/
        scoreBanner->scoreTexture[count].objTexture = 
            gameText[0].objTexture;
        /*Определяем mainRect текстур сегментов*/
        scoreBanner->scoreTexture[count].objRect = 
            gameText[count].objRect;
        scoreBanner->scoreTexture[count].objRect->x = 
            scoreBannerX + (WIDTH + SPACE) * count;
        scoreBanner->scoreTexture[count].objRect->y = 
            scoreBannerY;
    }
    printf("\n");

    /*Обнуление счета Score*/
    scoreBanner->score = 0;

    #undef SPACE
    #undef WIDTH
    #undef BORDER_UP_Y
    #undef HEIGHT
}

bool makeBorder(border_t* border)
{
    border->border = malloc(sizeof(SDL_Rect) * allBorderSides);
    if (!border->border)
    {
        printf("Internal error by managing memory of border.\n");
        border->border = NULL;
        return false;
    }
    border->border[borderUp].x = UP_BORDER_X;
    border->border[borderUp].y = UP_BORDER_Y;
    border->border[borderUp].w = UP_BORDER_W;
    border->border[borderUp].h = UP_BORDER_H;

    border->border[borderDown].x = DOWN_BORDER_X;
    border->border[borderDown].y = DOWN_BORDER_Y;
    border->border[borderDown].w = DOWN_BORDER_W;
    border->border[borderDown].h = DOWN_BORDER_H;

    border->border[borderLeft].x = LEFT_BORDER_X;
    border->border[borderLeft].y = LEFT_BORDER_Y;
    border->border[borderLeft].w = LEFT_BORDER_W;
    border->border[borderLeft].h = LEFT_BORDER_H;

    border->border[borderRight].x = RIGHT_BORDER_X;
    border->border[borderRight].y = RIGHT_BORDER_Y;
    border->border[borderRight].w = RIGHT_BORDER_W;
    border->border[borderRight].h = RIGHT_BORDER_H;

    border->border[blackBanner].x = 0;
    border->border[blackBanner].y = 0;
    border->border[blackBanner].w = border->border[borderUp].w;
    border->border[blackBanner].h = border->border[borderUp].y;

    return true;
}

void closeNoAction()
{
    int count;

    if (!noaction) return;
    if (noaction->border)
    {
        if (noaction->border->border)
        {
            free(noaction->border->border);
            noaction->border->border = NULL;
        }

        free(noaction->border);

    }
    noaction->border = NULL;
    if (noaction->sky)
    {
        if (noaction->sky->starTexture)
        {
            if (noaction->sky->starTexture->objTexture)
            {
                noaction->sky->starTexture->objTexture = NULL;
            }
        }
        if (noaction->sky->fast)
        {
            free(noaction->sky->fast);
            noaction->sky->fast = NULL;
        }
        if (noaction->sky->slow)
        {
            free(noaction->sky->slow);
            noaction->sky->slow = NULL;
        }
        free(noaction->sky);
    }
    noaction->sky = NULL;
    if (noaction->scoreBanner)
    {
        if (noaction->scoreBanner->scoreTexture)
        {
            for (count = 0; count < SCORE_BANNER_LEN; ++count)
            {
                noaction->scoreBanner->scoreTexture[count].objTexture = NULL;
            }
            free(noaction->scoreBanner->scoreTexture);
            noaction->scoreBanner->scoreTexture = NULL;
        }
        free(noaction->scoreBanner);
    }
    noaction->scoreBanner = NULL;

    if (noaction->pause)
    {
        if (noaction->pause->objTexture)
        {
            noaction->pause->objTexture = NULL;
        }
        free(noaction->pause);
    }
    noaction->pause = NULL;

    if (noaction->heroLivesBan)
    {
        if (noaction->heroLivesBan->heroLivesTextures)
        {
            noaction->heroLivesBan->heroLivesTextures->objTexture = NULL;
            free(noaction->heroLivesBan->heroLivesTextures->objRect);
            noaction->heroLivesBan->heroLivesTextures->objRect = NULL;
            free(noaction->heroLivesBan->heroLivesTextures);
            noaction->heroLivesBan->heroLivesTextures = NULL;
        }
        if (noaction->heroLivesBan->heroLivesText)
        {
            for (count = 0; count < HEROLIVESBANNERTEXT_LEN; ++count)
            {
                noaction->heroLivesBan->heroLivesText->objTexture = NULL;
            }
            free(noaction->heroLivesBan->heroLivesText);
            noaction->heroLivesBan->heroLivesText = NULL;
        }
        free(noaction->heroLivesBan);
        noaction->heroLivesBan = NULL;
    }
    free(noaction);
    noaction = NULL;
}

void playerAction(sdl_type* sdl,
                  ship_t* hero,
                  tc* textureCollection,
                  status_t* status)
{
    while (SDL_PollEvent(&sdl->e) != 0)
    {
        if (sdl->e.type == SDL_QUIT) sdl->gameQuit = true;
        else if (sdl->e.type == SDL_KEYDOWN && sdl->e.key.repeat == 0)
        {
            switch (sdl->e.key.keysym.sym)
            {
                case SDLK_UP:
                {
                    heroUp(hero); break;
                }
                case SDLK_DOWN:
                {
                    heroDown(hero); break;
                }
                case SDLK_LEFT:
                {
                    heroLeft(hero); break;
                }
                case SDLK_RIGHT:
                {
                    heroRight(hero); break;
                }
                case SDLK_ESCAPE:
                {
                    status->pause = !status->pause;
                    break;
                }
                default: {}
            }
        }
        else if (sdl->e.type == SDL_KEYUP) stopHero(hero);
    }
}

void heroUp(ship_t* hero)
{
    hero->velocities->y -= HERO_VELOCITY;
    moveHero(hero);
}

void heroDown(ship_t* hero)
{
    hero->velocities->y += HERO_VELOCITY;
    moveHero(hero);
}

void heroLeft(ship_t* hero)
{
    hero->velocities->x -= HERO_VELOCITY;
    moveHero(hero);
}

void heroRight(ship_t* hero)
{
    hero->velocities->x += HERO_VELOCITY;
    moveHero(hero);
}

void stopHero(ship_t* hero)
{
    hero->velocities->x = hero->velocities->y = 0;
}

void moveHero(ship_t* hero)
{
    if (isGonnaCrossRight(hero)) return;
    if (isGonnaCrossLeft(hero))  return;
    if (isGonnaCrossDown(hero))  return;
    if (isGonnaCrossUP(hero))    return;
    recomputeHeroLaserPos(hero);
    recomputeHeroRects(hero);
    recomputeHeroCenter(hero);
}

bool isGonnaCrossUP(ship_t* hero)
{
    return hero->shipObject->objRectsArr[mainRect].y + hero->velocities->y <
            noaction->border->border[borderUp].y +\
            noaction->border->border[borderUp].h;
}

bool isGonnaCrossDown(ship_t* hero)
{
    return hero->shipObject->objRectsArr[mainRect].y +\
           hero->shipObject->objRectsArr[mainRect].h + hero->velocities->y >
           noaction->border->border[borderDown].y;
}

bool isGonnaCrossLeft(ship_t* hero)
{
    return hero->shipObject->objRectsArr[mainRect].x +
           hero->velocities->x < noaction->border->border[borderLeft].x;
}

bool isGonnaCrossRight(ship_t* hero)
{
    return hero->shipObject->objRectsArr[mainRect].x +
           hero->shipObject->objRectsArr[mainRect].w +
           hero->velocities->x > noaction->border->border[borderRight].x;
}

void recomputeHeroCenter(ship_t* hero)
{
    hero->shipCenter.x += hero->velocities->x;
    hero->shipCenter.y += hero->velocities->y;
}

void recomputeHeroLaserPos(ship_t* hero)
{
    hero->laserStartPos->x = 
        hero->shipObject->objRectsArr[mainRect].x +
        hero->laserOffSets->x;
    hero->laserStartPos->y =
        hero->shipObject->objRectsArr[mainRect].y -
        hero->laserOffSets->y;
}


void recomputeHeroRects(ship_t* hero)
{
    int rect;
    for (rect = 0; rect < allRects; ++rect)
    {
        hero->shipObject->objRectsArr[rect].x += hero->velocities->x;
        hero->shipObject->objRectsArr[rect].y += hero->velocities->y;
    }
}


void showBorder(sdl_type* sdl)
{
    renderBorder(sdl, noaction->border->border);
}


void showScoreBanner(sdl_type* sdl)
{
    renderScoreBanner(sdl, noaction->scoreBanner, SCORE_BANNER_LEN);
}

void showSky(sdl_type* sdl)
{
    renderSky(sdl, noaction->sky);
}

void showPause(sdl_type* sdl)
{
    textureRender(sdl, noaction->pause[na_pause].objTexture,
                    noaction->pause[na_pause].objRect);
    textureRender(sdl, noaction->pause[na_press_esc].objTexture,
                    noaction->pause[na_press_esc].objRect);
}

void pauseIsPressed(sdl_type* sdl, ship_t* hero, status_t* status)
{
    while (!sdl->gameQuit || !status->pause)
    {
        SDL_RenderClear(sdl->gRenderer);
        showSky(sdl);
        moveSky();
        renderComplexObject(sdl, hero->shipObject);
        showBorder(sdl);
        showScoreBanner(sdl);
        showHeroBanner(sdl, status);
        showPause(sdl);
        while (SDL_PollEvent(&sdl->e) != 0)
        {
            if (sdl->e.type == SDL_QUIT)
            {
                sdl->gameQuit = true; 
                status->pause = false;
                return;
            }
            else if (sdl->e.type == SDL_KEYDOWN && sdl->e.key.repeat == 0)
            {
                switch (sdl->e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        status->pause = false;
                        return;
                    }
                    case SDLK_q:
                    {
                        status->mainMenu = true;
                        return;
                    }
                    default : {}
                }
            }
        }
        SDL_RenderPresent(sdl->gRenderer);
    }

}

void showHeroBanner(sdl_type* sdl, status_t* status)
{
    if (status->HeroLives < 0) return;
    
    #define BORD_LEFT noaction->border->border[borderLeft].x + BORDER_THICKNESS
    #define BORD_UP   noaction->border->border[borderUp].y
    #define HEROLIVE_W noaction->heroLivesBan->heroLivesTextures->objRect->w
    #define HEROLIVE_H noaction->heroLivesBan->heroLivesTextures->objRect->h
    #define CURRENT_TEXT status->HeroLives - 1
    #define HEROTEXTURE_W noaction->heroLivesBan->heroLivesTextures->objRect->x\
            + noaction->heroLivesBan->heroLivesTextures->objRect->w
    #define XTEXTURE_H noaction->heroLivesBan->heroLivesText[0].objRect->h

    /*Рисуем текстурку героя в баннере*/
    noaction->heroLivesBan->heroLivesTextures->objRect->x =
        BORD_LEFT + BORDER_THICKNESS;
    noaction->heroLivesBan->heroLivesTextures->objRect->y =
        BORD_UP - HEROLIVE_H;
    textureRender(sdl, noaction->heroLivesBan->heroLivesTextures->objTexture,
                    noaction->heroLivesBan->heroLivesTextures->objRect);

    noaction->heroLivesBan->heroLivesText[CURRENT_TEXT].objRect->x = 
        HEROTEXTURE_W + 2 * BORDER_THICKNESS;
    noaction->heroLivesBan->heroLivesText[CURRENT_TEXT].objRect->y =
        BORD_UP - XTEXTURE_H - BORDER_THICKNESS;
    textureRender(sdl, 
                noaction->heroLivesBan->heroLivesText[CURRENT_TEXT].objTexture,
                noaction->heroLivesBan->heroLivesText[CURRENT_TEXT].objRect);



    #undef XTEXTURE_H
    #undef HEROTEXTURE_W
    #undef BORD_LEFT
    #undef BORD_UP
    #undef HEROLIVE_W
    #undef HEROLIVE_H
    #undef CURRENT_TEXT

}

void moveSky()
{
    int count;
    #define BORDER_LEFT  noaction->border->border[borderLeft].w
    #define BORDER_RIGHT noaction->border->border[borderRight].x

    for (count = 0; count < fastStarMax; ++count)
    {
        noaction->sky->fast[count].y += FAST_STAR_VELOCITY;
        if (noaction->sky->fast[count].y > noaction->border->border[borderDown].y)
        {
            noaction->sky->fast[count].x =
                getRand(BORDER_LEFT, BORDER_RIGHT);
            noaction->sky->fast[count].y = getRand(-300, 0);
        }
    }
    for (count = 0; count < slowStarMax; ++count)
    {
        noaction->sky->slow[count].y += SLOW_STAR_VELOCITY;
        if (noaction->sky->slow[count].y > noaction->border->border[borderDown].y)
        {
            noaction->sky->slow[count].x =
                getRand(BORDER_LEFT, BORDER_RIGHT);
            noaction->sky->slow[count].y = getRand(-300, 0);
        }
    }

    #undef BORDER_LEFT
    #undef BORDER_RIGHT
}

/*Установка координат для PAUSE и Press esc..*/
bool makePause(tc* collection)
{
    if (!collection || !collection->gameText)
    {
        printf("Cannot make pause, textures are absent.\n");
        return false;
    }
    plot centerPause;
    plot centerPressEsc;

    centerPause.x = S_W / 2;
    centerPause.y = S_H / 2;
    centerPressEsc.x = S_W / 2;
    centerPressEsc.y = S_H - 100;

    noaction->pause[na_pause] = collection->gameText[pause];
    noaction->pause[na_press_esc] = collection->gameText[press_esc];

    noaction->pause[na_pause].objRect->x =
        centerPause.x - noaction->pause[na_pause].objRect->w / 2;
    noaction->pause[na_pause].objRect->y =
        centerPause.y - noaction->pause[na_pause].objRect->h / 2;
    noaction->pause[na_press_esc].objRect->x =
        centerPressEsc.x - noaction->pause[na_press_esc].objRect->w / 2;
    noaction->pause[na_press_esc].objRect->y =
        centerPressEsc.y - noaction->pause[na_press_esc].objRect->h / 2;

    return true;
}

/*Установка кооридинат для текстур главного меню */
bool makeMainMenu(tc* collection)
{
    if (!collection || !collection->gameText)
    {
        printf("Cannot make main menu, textures are absent.\n");
        return false;
    }
    
    plot center;
    int oneFourth;
    int count;
    int step;
    
    
    oneFourth = S_H / 4;

    step = 1;
    center.x = S_W / 2;
    for (count = new_game; count < new_game_Chosen; ++count)
    {
        center.y = step * oneFourth;
        collection->gameText[count].objRect->x =
            center.x - collection->gameText[count].objRect->w / 2;
        collection->gameText[count].objRect->y =
            center.y - collection->gameText[count].objRect->h / 2;
        step += 1;
    }

    step = 1;
    for (count = new_game_Chosen; count < press_esc; ++count)
    {
        center.y = step * oneFourth;
        collection->gameText[count].objRect->x = 
            center.x - collection->gameText[count].objRect-> w / 2;
        collection->gameText[count].objRect->y = 
            center.y - collection->gameText[count].objRect->h / 2;
        step += 1;
    }
    return true;
}
