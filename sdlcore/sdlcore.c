#include "sdlcore.h"
#include <stdio.h>




bool sdlInit(sdl_type* sdl, int s_w, int s_h, char* appName)
{
    int imgFlags;

    if (appName == NULL)
    {
        printf("SDL init stop, need app name\n");
        return false;
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not initialize video mode.\n");
        return false;
    }

    /*Set texture filtering linear*/
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("SDL linear texture error\n");
        return false;
    }

    /*Create window*/
    sdl->gWindow = SDL_CreateWindow(appName,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    s_w,
                                    s_h,
                                    SDL_WINDOW_SHOWN);
    if (!sdl->gWindow)
    {
        printf("Cannot create window, error.\n");
        return false;
    }

    sdl->gRenderer = SDL_CreateRenderer(sdl->gWindow,
                                        -1,
                                        SDL_RENDERER_ACCELERATED);
    if (!sdl->gRenderer)
    {
        printf("Renderer could not be created.\n");
        return false;
    }

    imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("Could not initialize png image.\n");
        return false;
    }

    if (TTF_Init() == 1)
    {
        printf("SDL_ttf could not initialize. %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void sdlClose(sdl_type* sdl)
{
    SDL_DestroyRenderer(sdl->gRenderer);
    SDL_DestroyWindow(sdl->gWindow);
    sdl->gRenderer = NULL;
    sdl->gWindow = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void closeGameFonts(font_type* gameFonts)
{
    if (!gameFonts) return;
    int count;
    for (count = 0; count < allfonts; ++count)
    {
        TTF_CloseFont(gameFonts[count].font);
        gameFonts[count].font = NULL;
    }
    free(gameFonts);
    gameFonts = NULL;
}

void textureFree(SDL_Texture* texture)
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

/*Загрузка текстуры для картинки*/
bool loadFromFile(sdl_type* sdl,
                  SDL_Texture** texture,
                  SDL_Rect* mainRect,
                  const char* path)
{
    if (path == NULL)
    {
        printf("Need path to load image.\n"); return false;
    }
    textureFree(*texture);
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface)
    {
        printf("Unable to load image %s.\n", path); return false;
    }
    SDL_SetColorKey(loadedSurface,
                    SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0, 0, 0));
    newTexture = SDL_CreateTextureFromSurface(sdl->gRenderer, loadedSurface);
    if (!newTexture)
    {
        printf("Unable to create texture from %s.\n", path);
        return false;
    }
    mainRect->w = loadedSurface->w;
    mainRect->h = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    *texture = newTexture;
    return true;
}

bool loadFromText(sdl_type* sdl,
                  const char* textToTexture,
                  font_type* ft,
                  SDL_Texture** texture,
                  SDL_Rect* mainRect)
{
    if (!textToTexture)
    {
        printf("Need text to make texture.\n"); return false;
    }
    SDL_Texture* newTexture = NULL;
    SDL_Surface* txtSurface =
        TTF_RenderText_Solid(ft->font,
                             textToTexture,
                             ft->fp.fontColor);
    if (!txtSurface)
    {
        printf("Unable to render text surface. %s\n", TTF_GetError());
        return false;
    }
    newTexture = SDL_CreateTextureFromSurface(sdl->gRenderer, txtSurface);
    if (!newTexture)
    {
        printf("Unable to create texture from rendered text. %s\n",
            SDL_GetError());
        return false;
    }

    /*Для букв устанавливаем разную ширину и высоту*/
    if (ft->fp.isAlpha)
    {
        mainRect->w = txtSurface->w;
        mainRect->h = txtSurface->h;
    }
    else
    /*Для цифр устанавливаем одинаковую ширину и высоту*/
    {
        mainRect->w = FONT_DIGIT_WIDTH;
        mainRect->h = txtSurface->h;
    }
    SDL_FreeSurface(txtSurface);
    *texture = newTexture;
    return true;
}

void allTexturesFree(tc* collection)
{
    int texture;
    if (collection->complexObj)
    {
        for (texture = 0; texture < allComplexObjects; ++texture)
        {
            textureFree(collection->complexObj[texture].objTexture);
            free(collection->complexObj[texture].objRectsArr);
        }
        free(collection->complexObj);
        collection->complexObj = NULL;
    }

    if (collection->simpleObj)
    {
        for (texture = 0; texture < allSimpleObjects; ++texture)
        {
            textureFree(collection->simpleObj[texture].objTexture);
            free(collection->simpleObj[texture].objRect);
        }
        free(collection->simpleObj);
        collection->simpleObj = NULL;
    }

    if (collection->gameText)
    {
        for (texture = 0; texture < allSimpleTextObjects; ++texture)
        {
            textureFree(collection->gameText[texture].objTexture);
            free(collection->gameText[texture].objRect);
        }
        free(collection->gameText);
        collection->gameText = NULL;
    }
}

/*Рисуем одну текстуру*/
void textureRender(sdl_type* sdl, SDL_Texture* t, SDL_Rect* r)
{
    SDL_RenderCopy(sdl->gRenderer, t, NULL, r);
}

void renderComplexObject(sdl_type* sdl, complex_type* obj)
{
    textureRender(sdl, obj->objTexture, &obj->objRectsArr[mainRect]);
}

void renderBorder(sdl_type* sdl, SDL_Rect* sides)
{
    SDL_SetRenderDrawColor(sdl->gRenderer, 0xFF, 0, 0, 0xFF);
    SDL_RenderFillRect(sdl->gRenderer, &sides[borderUp]);
    SDL_RenderFillRect(sdl->gRenderer, &sides[borderDown]);
    SDL_RenderFillRect(sdl->gRenderer, &sides[borderLeft]);
    SDL_RenderFillRect(sdl->gRenderer, &sides[borderRight]);
    SDL_SetRenderDrawColor(sdl->gRenderer, 0, 0, 0, 0);
    SDL_RenderFillRect(sdl->gRenderer, &sides[blackBanner]);
}

void renderScoreBanner(sdl_type* sdl, score_t* scoreBanner, int segments)
{
    int segment;
    for (segment = 0; segment < segments; ++segment)
    {
        textureRender(sdl, scoreBanner->scoreTexture[segment].objTexture,
        scoreBanner->scoreTexture[segment].objRect);
    }
}

void renderSky(sdl_type* sdl, sky_t* sky)
{
    int count;
    for (count = 0; count < fastStarMax; ++count)
    {
        textureRender(sdl, sky->starTexture->objTexture, &sky->fast[count]);
    }

    for (count = 0; count < slowStarMax; ++count)
    {
        textureRender(sdl, sky->starTexture->objTexture, &sky->slow[count]);
    }
}
