#include "mainmenu.h"




void showMainMenu(sdl_type* sdl, tc* collection, status_t* status)
{
    int chosen_texture = new_game_Chosen;
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
                    }
                }
            }
        }

        SDL_RenderClear(sdl->gRenderer);
        if (chosen_texture == new_game_Chosen)
        {
            textureRender(sdl, collection->gameText[new_game_Chosen].objTexture,
                            collection->gameText[new_game_Chosen].objRect);
        }
        else textureRender(sdl, collection->gameText[new_game].objTexture,
                            collection->gameText[new_game].objRect);
        if (chosen_texture == rules_Chosen)
        {
            textureRender(sdl, collection->gameText[rules_Chosen].objTexture,
                            collection->gameText[rules_Chosen].objRect);
        }
        else textureRender(sdl, collection->gameText[rules].objTexture,
                            collection->gameText[rules].objRect);
        if (chosen_texture == game_exit_Chosen)
        {
            textureRender(sdl, collection->gameText[game_exit_Chosen].objTexture,
                            collection->gameText[game_exit_Chosen].objRect);
        }
        else textureRender(sdl, collection->gameText[game_exit].objTexture,
                            collection->gameText[game_exit].objRect);
        SDL_RenderPresent(sdl->gRenderer);
    }
}

