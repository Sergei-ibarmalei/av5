#include "inits.h"
#include "../types/fontproperties.h"
#include "../types/rects.h"
#include <stdio.h>

void setFontsProperties(font_type* ft);
void initHeroIntersectRects(SDL_Rect* intersectRects, plot* startPos);
bool initHeroLaserPosition(tc* collection, ship_t* ship);
bool initHeroVelocitites(ship_t* ship);


void initGameStatus(status_t* status)
{
    status->mainMenu = true;
    status->pause    = false;
    status->partOne  = false;
    status->partTwo  = false;
}

font_type* initGameFonts()
{

    int count;
    font_type* gameFonts = malloc(sizeof(font_type)*allfonts);
    if (!gameFonts)
    {
        printf("Internal error by creating gameFonts referencing.\n");
        return NULL;
    }
    const char* globalFontName = FONT_GAME;

    setFontsProperties(gameFonts);

    for (count = 0; count < allfonts; ++count)
    {
        gameFonts[count].font = NULL;
        gameFonts[count].font =
            TTF_OpenFont(globalFontName, gameFonts[count].fp.fontSize);
        if (!gameFonts[count].font)
        {
            printf("Failed to load font. %s\n", TTF_GetError());
            return NULL;
        }
    }
    return gameFonts;
    

}

/*Устанавливаем размер, цвет шрифта*/
void setFontsProperties(font_type* ft)
{
    ft[menufont].fp.fontSize = MENU_FONT_SIZE;
    ft[menufont].fp.fontColor = DARK_RED;
    ft[menufont].fp.isAlpha = true;

    ft[menufontshadow].fp.fontSize = MENU_FONT_SIZE;
    ft[menufontshadow].fp.fontColor = LIGHTPINK;
    ft[menufontshadow].fp.isAlpha = true;

    ft[pausefont].fp.fontSize = PAUSE_FONT_SIZE;
    ft[pausefont].fp.fontColor = DARK_ORANGE;
    ft[pausefont].fp.isAlpha = true;

    ft[guifont].fp.fontSize = GUI_FONT_SIZE;
    ft[guifont].fp.fontColor = YELLOW_GREEN;
    ft[guifont].fp.isAlpha = false;

    ft[scorefont].fp.fontSize = SCORE_FONT_SIZE;
    ft[scorefont].fp.fontColor = CRIMSON;
    ft[scorefont].fp.isAlpha = false;

    
}

/*Инициализация всех текстур - картинок и текстур текста*/
bool initTextsCollection(sdl_type* sdl, tc* collection, font_type* gameFonts)
{

    int object;
    const char* complexFileName[] = {"Hero_1.png",
                                     "alien_one.png"};
    const char* simpleFileName[] = {"laserBlue01.png",
                                    "laserRed01.png",
                                    "one_star.png"};
    const char* simpleTextNames[] = {"0", "1", "2", "3", "4", "5", "6",
                                     "7", "8", "9",
                                     "PAUSE", "NEW GAME", "RULES", "EXIT",
                                     "NEW GAME", "RULES", "EXIT",
                                     "PRESS ESC TO EXIT, Q TO CONTINUE"};

    collection->complexObj = malloc(sizeof(complex_type)*allComplexObjects);
    if (!collection->complexObj)
    {
        printf("Internal error by complex textures init.\n"); return false;
    }
    collection->simpleObj = malloc(sizeof(simple_type)*allSimpleObjects);
    if (!collection->simpleObj)
    {
        printf("Internal error by simple textures init.\n"); return false;
    }
    collection->gameText = malloc(sizeof(simple_type)*allSimpleTextObjects);
    if (!collection->gameText)
    {
        printf("Internal error by simple text textures init.\n"); return false;
    }

    for (object = 0; object < allComplexObjects; ++object)
    {
        collection->complexObj[object].objTexture = NULL;
        /*Резерв памяти для прямоугольников пересечений*/
        collection->complexObj[object].objRectsArr = 
            malloc(sizeof(SDL_Rect)* allRects);
        if (loadFromFile(sdl,
                         /*отправляем текстуру*/
                         &collection->complexObj[object].objTexture,
                         /*отправляем главный прямоугольник пересечения*/
                         &collection->complexObj[object].objRectsArr[mainRect],
                         /*отправляем путь до файла*/
                         complexFileName[object]) == false)
            {
                printf("Cannot create complex object texture, abort.\n");
                return false;
            }
    }

    for (object = 0; object < allSimpleObjects; ++object)
    {
        collection->simpleObj[object].objTexture = NULL;
        collection->simpleObj[object].objRect = 
            malloc(sizeof(SDL_Rect));
        if (loadFromFile(sdl,
                         &collection->simpleObj[object].objTexture,
                         collection->simpleObj[object].objRect,
                         simpleFileName[object]) == false)
            {
                printf("Cannot create simple object texture, abort.\n");
                return false;
            }
    }


    /*Создание текстур для score от 0-9*/
    for (object = 0; object < pause; ++object)
    {
        collection -> gameText[object].objTexture = NULL;
        collection -> gameText[object].objRect =
            malloc(sizeof(SDL_Rect));
        if (loadFromText(sdl, 
                         simpleTextNames[object],
                         &gameFonts[scorefont],
                         &collection->gameText[object].objTexture,
                         collection->gameText[object].objRect) == false)
            {
                printf("Cannot create texture for 0-9, abort.\n");
                return false;
            }
    }

    /*Создание текстур для PAUSE*/
    object = pause;
    collection->gameText[object].objTexture = NULL;
    collection->gameText[object].objRect = malloc(sizeof(SDL_Rect));
    if (loadFromText(sdl,
                     simpleTextNames[object],
                     &gameFonts[pausefont],
                     &collection->gameText[object].objTexture,
                     collection->gameText[object].objRect) == false)
        {
            printf("Cannot create texture fo PAUSE, abort.\n");
            return false;
        }
    
    /*Создание текстур для главного меню*/
    for (object = new_game; object < new_game_Chosen; ++object)
    {
        collection->gameText[object].objTexture = NULL;
        collection->gameText[object].objRect = malloc(sizeof(SDL_Rect));
        if (loadFromText(sdl,
                         simpleTextNames[object],
                         &gameFonts[menufont],
                         &collection->gameText[object].objTexture,
                         collection->gameText[object].objRect) == false)
            {
                printf("Cannot create texture fo main menu, abort.\n");
                return false;
            }
    }

    /*Создание текстур для главного меню с ТЕНЬЮ*/
    for (object = new_game_Chosen; object < press_esc; ++object)
    {
        collection->gameText[object].objTexture = NULL;
        collection->gameText[object].objRect = malloc(sizeof(SDL_Rect));
        if (loadFromText(sdl,
                        /*Берем тот же текст что у простого главного меню*/
                        /*Поэтому в массиве их номер меньше на 3*/
                         simpleTextNames[object],
                         &gameFonts[menufontshadow],
                         &collection->gameText[object].objTexture,
                         collection->gameText[object].objRect) == false)
            {
                printf("Cannot create texture for main menu shadow, abort.\n");
                return false;
            }
    }

    /*Создание текстур для надписи "Press esc to.."*/
    object = press_esc;
    collection->gameText[object].objTexture = NULL;
    collection->gameText[object].objRect = malloc(sizeof(SDL_Rect));

    if (loadFromText(sdl,
                     simpleTextNames[object],
                     &gameFonts[guifont],
                     &collection->gameText[object].objTexture,
                     collection->gameText[object].objRect) == false)
        {
            printf("Cannot create texture for Press esc.., abort.\n");
            return false;
        }
    
    return true;
}

bool initHero(tc* collection, ship_t* ship, plot* startPos)
{
    if (collection->complexObj[hero].objTexture == NULL)
    {
        printf("Texture hero is absent.\n"); 
        return false;
    }
    ship->shipObject = &collection->complexObj[hero];

    ship->isDead = false;
    ship->laserStartPos = NULL;
    ship->laserOffSets = NULL;
    ship->velocities = NULL;
    ship->shipCenter.x = startPos->x;
    ship->shipCenter.y = startPos->y;

    initHeroIntersectRects(ship->shipObject->objRectsArr, startPos);
    if (!(initHeroLaserPosition(collection, ship))) return false;
    if (!(initHeroVelocitites(ship))) return false;
    return true;
}

void closeHero(ship_t* hero)
{
   hero->shipObject = NULL;
   free(hero->laserStartPos);
   hero->laserStartPos = NULL;
   free(hero->laserOffSets);
   hero->laserOffSets = NULL;
   free(hero->velocities);
   hero->velocities = NULL; 
}

bool initHeroVelocitites(ship_t* ship)
{
    ship->velocities = malloc(sizeof(plot));
    if (!ship->velocities)
    {
        printf("Internal error by managing memory of hero velocity.\n");
        return false;
    }
    ship->velocities->x = 0;
    ship->velocities->y = 0;
    return true;
}

void initHeroIntersectRects(SDL_Rect* intersectRects, plot* startPos)
{
    intersectRects[mainRect].x = startPos->x - intersectRects[mainRect].w/2;
    intersectRects[mainRect].y = startPos->y - intersectRects[mainRect].h/2;
    intersectRects[firstRect].x = intersectRects[mainRect].x + HERO_FX;
    intersectRects[firstRect].y = intersectRects[mainRect].y + HERO_FY;
    intersectRects[firstRect].w = HERO_FW;
    intersectRects[firstRect].h = HERO_FH;
    intersectRects[secondRect].x = intersectRects[mainRect].x + HERO_SX;
    intersectRects[secondRect].y = intersectRects[mainRect].y + HERO_SY;
    intersectRects[secondRect].w = HERO_SW;
    intersectRects[secondRect].h = HERO_SH;

}

bool initHeroLaserPosition(tc* collection, ship_t* ship)
{
    #define HERO_LASER_OFFSET 4
    ship->laserStartPos = malloc(sizeof(plot));
    if (!ship->laserStartPos)
    {
        printf("Internal error by managing memory of hero laser start pos.\n");
        return false;
    }
    ship->laserOffSets = malloc(sizeof(plot));
    if (!ship->laserOffSets)
    {
        printf("Internal error by managing memory of hero laser off sets.\n");
        return false;
    }

    ship->laserOffSets->x =
        ship->shipObject->objRectsArr[mainRect].w/2;
    ship->laserOffSets->y =
        collection->simpleObj[(int)heroLaser].objRect->h + HERO_LASER_OFFSET;

    ship->laserStartPos->x =
        ship->shipObject->objRectsArr[mainRect].x + 
        ship->laserOffSets->x;
    ship->laserStartPos->y =
        ship->shipObject->objRectsArr[mainRect].y -
        ship->laserOffSets->y;
    #undef HERO_LASER_OFFSET
    return true;
}

