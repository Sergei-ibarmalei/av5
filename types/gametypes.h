#ifndef GAMETYPES_H
#define GAMETYPES_H

#include "graphicstypes.h"
#include <stdbool.h>



/*Сложный тип состоит из текстуры и массива прямоугольников */
typedef struct
{
    SDL_Texture* objTexture;
    SDL_Rect*    objRectsArr;
} complex_type;

/*Простой тип состоит из текстуры и прямоугольника */
typedef struct
{
    SDL_Texture* objTexture;
    SDL_Rect*    objRect;
} simple_type;

struct weaponNode
{
    SDL_Rect shotRect;
    struct weaponNode* next;
    struct weaponNode* prev;
};

typedef struct
{
    struct weaponNode* firstShot;
    struct weaponNode* lastShot;
} weaponStore_t;


enum velocity {velocityX, velocityY, allVelocity};


enum rects {mainRect, firstRect, secondRect, allRects};

/*Все возможные сложные (complex) объекты */
enum complexTexts {hero,
                   alienOne,
                   allComplexObjects};

/*Все возможные простые (simple) объекты */
enum simpleTexts  {heroLaser,
                   alienLaser,
                   oneStar,
                   allSimpleObjects};

enum simpleTextTextures {zero,
                         one,
                         two,
                         three,
                         four,
                         five,
                         six,
                         seven,
                         eight,
                         nine,
                         pause,
                         new_game,
                         rules,
                         game_exit,
                         new_game_Chosen,
                         rules_Chosen,
                         game_exit_Chosen,
                         press_esc,
                         allSimpleTextObjects};


enum heroBannerText {x1, x2, x3, allHeroBannerText};

enum starCount {fastStarMax = 5, slowStarMax = 4};

enum borderSides {borderUp,
                  borderDown,
                  borderRight,
                  borderLeft,
                  blackBanner,
                  allBorderSides};



/*Коллекция текстур*/
typedef struct
{
    complex_type* complexObj; /*Коллекция complex текстур*/
    simple_type*  simpleObj;  /*Коллекция simple текстур*/
    simple_type*  gameText;       /*Коллекция gameText текстур*/
    simple_type*  heroBanner; /*Отображение жизней героя*/
} tc;

/*Тип определяющий любой корабль*/
typedef struct
{
    complex_type* shipObject;
    plot          shipCenter;
    plot*         laserStartPos; /*массив - может быть две точки*/
    plot*         laserOffSets;  /*массив - смещение начальной позиции лазера*/
    plot*         velocities;    /*массив - ускорение по двум направлениям*/
    bool          isDead;
} ship_t;


typedef struct
{
    SDL_Rect*    fast;
    SDL_Rect*    slow;
    simple_type* starTexture;
} sky_t;

typedef struct
{
    SDL_Rect* border;
} border_t;

typedef struct
{
    simple_type* scoreTexture;
    int          score;
} score_t;

/*Баннер где отображаются жизни героя*/
typedef struct 
{
    simple_type* heroLivesTextures;
    simple_type* heroLivesText;
} heroLives_t;



/*No action stuff like score, border, sky*/
typedef struct
{
    border_t*    border;
    sky_t*       sky;
    score_t*     scoreBanner;
    simple_type* pause;

    //Баннер отображения жизней героя
    //Изображения жизней плюс текст
    heroLives_t* heroLivesBan; 
} noaction_t;


/*--------LASER STORE-----------*/
struct laserNode
{
    SDL_Rect laser;
    struct laserNode* next;
    struct laserNode* prev;
};

typedef struct 
{
    struct laserNode* firstLaser;
    struct laserNode* lastLaser;
} laserStore_t;
/*--------LASER STORE-----------*/

typedef struct 
{
    bool mainMenu;
    bool pause;
    bool partOne;
    bool partTwo;
    int  HeroLives;
} status_t;

#endif
