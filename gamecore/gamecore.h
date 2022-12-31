#ifndef GAMECORE_H
#define GAMECORE_H


#include "../inits/inits.h"
#include "../consts/gameconsts.h"
#include "../random/rand.h"

bool makeNoAction(tc* collection);
void closeNoAction();
void playerAction(sdl_type* sdl,
                  ship_t* hero,
                  madeShots_t* madeShots,
                  status_t* status);
void moveHero(ship_t* hero);
void showBorder(sdl_type* sdl);
void showScoreBanner(sdl_type* sdl);
void showSky(sdl_type* sdl);
void moveSky();
void pauseIsPressed(sdl_type* sdl, ship_t* hero, 
                    madeShots_t* madeShots, status_t* status);
void showHeroBanner(sdl_type* sdl, status_t* status);
bool makeShotHero(ship_t* hero, madeShots_t* madeshots);
void showShots(sdl_type* sdl, madeShots_t* madeShots);
void moveShots(madeShots_t* madeShots);


#endif
