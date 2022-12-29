#ifndef INITS_H
#define INITS_H


#include "../sdlcore/sdlcore.h"
#include "../consts/gameconsts.h"
//#include "../types/gametypes.h"

font_type* initGameFonts();
bool initTextsCollection(sdl_type* sdl, tc* collection, font_type* gameFonts);
bool initHero(tc* collection, ship_t* hero, plot* startPos);
void closeHero(ship_t* hero);
void initGameStatus(status_t* status);
#endif
