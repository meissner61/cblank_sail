
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "defs.h"
#include "init.h"

#include "SDL.h"

void PrepareScene(void);
void PresentScene(void);
void DoInput(void);


App app;

int main(int argc, char* argv[])
{
    memset(&app, 0, sizeof(App));
    InitSDL();

    atexit(CleanUp);

    while(1)
    {
        PrepareScene();

        DoInput();

        PresentScene();

        SDL_Delay(16);
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
