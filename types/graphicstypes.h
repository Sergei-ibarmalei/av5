#ifndef GRAPHICSTYPES_H
#define GRAPHICSTYPES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>


/*Основной графический тип для изображений */
typedef struct
{
    SDL_Renderer*  gRenderer;
    SDL_Window*    gWindow;
    SDL_Event      e;
    bool           gameQuit;
} sdl_type;

typedef struct
{
    int x;
    int y;
} plot;



#endif
