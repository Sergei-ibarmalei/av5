#ifndef GAMECORE_H
#define GAMECORE_H


#include "../inits/inits.h"
#include "../consts/gameconsts.h"
#include "../random/rand.h"

bool makeNoAction(tc* collection);
void closeNoAction();
void playerAction(sdl_type* sdl,
                  ship_t* hero,
                  tc* textureCollection);

void moveHero(ship_t* hero);
void showBorder(sdl_type* sdl);
void showScoreBanner(sdl_type* sdl);
void showSky(sdl_type* sdl);
void moveSky();
void showPause(sdl_type* sdl);

#endif
