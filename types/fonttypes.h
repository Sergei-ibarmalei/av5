#ifndef FONTTYPES_H
#define FONTTYPES_H

#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

/*menufont - шрифт в главном меню*/
/*menufontshadow - шрифт в главном меню ТЕНЬ*/
/*pausefont - шрифт ПАУЗА*/
/*guifont - шрифт Grahpic user interface*/
/*в него входит надпись "Press esc to..." , а также */
/*цифры счета при попадании в алиена*/
/*scorefont - цифры счета*/
enum fontenum {menufont, menufontshadow,
               pausefont, guifont, scorefont, allfonts};

typedef struct
{
    int       fontSize;
    SDL_Color fontColor;
    bool      isAlpha;
} font_property;

typedef struct
{
    TTF_Font*     font;
    font_property fp;
} font_type;



#endif
