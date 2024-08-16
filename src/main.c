
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "defs.h"
#include "init.h"
#include "draw.h"
#include "Stage.h"

#include "SDL.h"

void PrepareScene(void);
void PresentScene(void);
void DoInput(void);
void DoKeyDown(SDL_KeyboardEvent* l_event);
void DoKeyUp(SDL_KeyboardEvent* l_event);
// void Blit(SDL_Texture* texture, int x, int y);


App app;
Stage stage;


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    memset(&app, 0, sizeof(App));

    InitSDL();

    atexit(CleanUp);

    InitStage();


    while(1)
    {
        PrepareScene();

        DoInput();

        app.delegate.logic();
        app.delegate.draw();

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
            {
                exit(0);
                break;
            }
            case SDL_KEYDOWN:
            {
                DoKeyDown(&event.key);
                break;
            }
            case SDL_KEYUP:
            {
                DoKeyUp(&event.key);
                break;
            }

            default:
                break;
        }
    }
}

void DoKeyDown(SDL_KeyboardEvent *l_event)
{
    if(l_event->repeat == 0 && l_event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        app.keyboard[l_event->keysym.scancode] = 1;
        //print this out
    }
}

void DoKeyUp(SDL_KeyboardEvent *l_event)
{
    if(l_event->repeat == 0 && l_event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        app.keyboard[l_event->keysym.scancode] = 0;
    }
}

// void Blit(SDL_Texture *texture, int x, int y)
// {
//     SDL_Rect dest;

//     dest.x = x;
//     dest.y = y;

//     SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

//     SDL_RenderCopy(app.renderer, texture, NULL, &dest);


// }
