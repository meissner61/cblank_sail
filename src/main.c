
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "defs.h"
#include "init.h"
#include "draw.h"

#include "SDL.h"

void PrepareScene(void);
void PresentScene(void);
void DoInput(void);
void Blit(SDL_Texture* texture, int x, int y);


App app;
Entity player;

//SDL_Texture* tex; //= LoadTexture("arena_input.png");

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));


    
    

    InitSDL();

    player.texture = LoadTexture("../data/player.png");

    player.x = 100;
    player.y = 100;

    atexit(CleanUp);

    while(1)
    {
        PrepareScene();

        DoInput();

        Blit(player.texture, player.x, player.y);

        PresentScene();

        //SDL_Delay(16);
    }

    return 0;
}

void PrepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void PresentScene(void)
{

    //SDL_RenderCopy(app.renderer, player.texture, NULL, NULL);

    SDL_RenderPresent(app.renderer);
}

void DoInput(void)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            default:
                break;
        }
    }
}

void Blit(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);


}
