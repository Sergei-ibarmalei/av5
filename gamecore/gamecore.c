#include "gamecore.h"

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

noaction_t* noaction;

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


    /*Резервируем память под scoreBanner*/
    noaction->scoreBanner = malloc(sizeof(score_t));
    if (!noaction->scoreBanner)
    {
        printf("Internal error by managing memory of score.\n");
        closeNoAction();
        return false;
    }
    noaction->scoreBanner->scoreTexture =
        malloc(sizeof(simple_type)* SCORE_BANNER_LEN);
    if (!noaction->scoreBanner->scoreTexture)
    {
        printf("Internal error by managing memory of score banner.\n");
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
    free(noaction);
    noaction = NULL;
}

void playerAction(sdl_type* sdl,
                  ship_t* hero,
                  tc* textureCollection)
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
