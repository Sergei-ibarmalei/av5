#ifndef SDLCORE_H
#define SDLCORE_H

#include "../types/graphicstypes.h"
#include "../consts/graphicsconsts.h"
#include "../types/fonttypes.h"
#include "../types/fontproperties.h"
#include "../types/gametypes.h"

bool sdlInit(sdl_type* sdl, int s_w, int s_h, char* appName);
void sdlClose(sdl_type* sdl);
void closeGameFonts(font_type* gameFonts);
void textureFree(SDL_Texture* texture);
bool loadFromFile(sdl_type* sdl,
                  SDL_Texture** texture,
                  SDL_Rect* mainRect,
                  const char* path);
bool loadFromText(sdl_type* sdl,
                  const char* textToTexture,
                  font_type* ft,
                  SDL_Texture** texture,
                  SDL_Rect* mainRect);
void allTexturesFree(tc* collection);
void renderComplexObject(sdl_type* sdl, complex_type* obj);
void renderBorder(sdl_type* sdl, SDL_Rect* sides);
void renderScoreBanner(sdl_type* sdl, score_t* scoreBanner, int segments);
void renderSky(sdl_type* sdl, sky_t* sky);
void textureRender(sdl_type* sdl, SDL_Texture* t, SDL_Rect* r);
                  
#endif
