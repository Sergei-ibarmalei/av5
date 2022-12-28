#include "mainmenu.h"

void showNewGameString(sdl_type* sdl, tc* collect, int chosen_texture);
void showRulesString(sdl_type* sdl, tc* collect, int chosen_texture);
void showExitString(sdl_type* sdl, tc* collect, int chosen_texture);

void showMainMenu(sdl_type* sdl, tc* collect, status_t* status)
{
    int chosen_texture = new_game_Chosen;
    status->partOne = false;
    status->partTwo = false;
    status->pause = false;

    while (!sdl->gameQuit)
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
                        chosen_texture -= 1;
                        if (chosen_texture < new_game_Chosen)
                            chosen_texture = game_exit_Chosen;
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        chosen_texture += 1;
                        if (chosen_texture > game_exit_Chosen)
                            chosen_texture = new_game_Chosen;
                        break;
                    }
                    case SDLK_RETURN:
                    {
                        if (chosen_texture == new_game_Chosen)
                        {
                            status->mainMenu = false;
                            status->partOne = true;
                            status->partTwo = false;
                            status->pause = false;
                            return;
                        }
                        if (chosen_texture == rules_Chosen)
                        {

                        }
                        if (chosen_texture == game_exit_Chosen)
                        {
                            status->mainMenu = false;
                            status->partOne = false;
                            status->partTwo = false;
                            status->pause = false;
                            sdl->gameQuit = true;
                        }
                    }

                }
            }
        }

        SDL_RenderClear(sdl->gRenderer);
        showNewGameString(sdl, collect, chosen_texture);
        showRulesString(sdl, collect, chosen_texture);
        showExitString(sdl, collect, chosen_texture);

        SDL_RenderPresent(sdl->gRenderer);
    }
}

/*В главном меню рисуем NEW GAME*/
void showNewGameString(sdl_type* sdl, tc* collect, int chosen_texture)
{
    if (chosen_texture == new_game_Chosen)
    {
        textureRender(sdl, collect->gameText[new_game_Chosen].objTexture,
                        collect->gameText[new_game_Chosen].objRect);
    }
    else textureRender(sdl, collect->gameText[new_game].objTexture,
                        collect->gameText[new_game].objRect);
}

/*В главном меню рисуем RULES*/
void showRulesString(sdl_type* sdl, tc* collect, int chosen_texture)
{
    if (chosen_texture == rules_Chosen)
    {
        textureRender(sdl, collect->gameText[rules_Chosen].objTexture,
                        collect->gameText[rules_Chosen].objRect);
    }
    else textureRender(sdl, collect->gameText[rules].objTexture,
                        collect->gameText[rules].objRect);
}

/*В главном меню рисуем EXIT*/
void showExitString(sdl_type* sdl, tc* collect, int chosen_texture)
{
    if (chosen_texture == game_exit_Chosen)
    {
        textureRender(sdl, collect->gameText[game_exit_Chosen].objTexture,
                        collect->gameText[game_exit_Chosen].objRect);
    }
    else textureRender(sdl, collect->gameText[game_exit].objTexture,
                        collect->gameText[game_exit].objRect);
}

