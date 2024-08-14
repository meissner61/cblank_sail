
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
void DoKeyDown(SDL_KeyboardEvent* l_event);
void DoKeyUp(SDL_KeyboardEvent* l_event);
void Blit(SDL_Texture* texture, int x, int y);


App app;
Entity player;
Entity bullet;


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    memset(&bullet, 0, sizeof(Entity));

    InitSDL();

    player.texture = LoadTexture("../data/player.png");


    SDL_Rect rect = {100,100,100,100};
    // bullet.shape = {100,100,100,100}; //cannot use initializer list like this in C...
    //bullet.shape{bullet.x, bullet.y, 20,2};
    bullet.shape = (SDL_Rect){bullet.x,bullet.y,16,3};

    player.x = 100;
    player.y = 100;

    atexit(CleanUp);

    while(1)
    {
        PrepareScene();

        DoInput();

        if (app.up)
        {
            player.y -= 4;
        }

        if (app.down)
        {
            player.y += 4;
        }

        if (app.left)
        {
            player.x -= 4;
        }

        if (app.right)
        {
            player.x += 4;
        }

        if(app.fire && bullet.health == 0)
        {
            bullet.shape.x = player.x;
            bullet.shape.y = player.y;
            bullet.dx = 16;
            bullet.dy = 0;
            bullet.health = 1;
        }

        bullet.shape.x += bullet.dx;
        bullet.shape.y += bullet.dy;

        if(bullet.shape.x > SCREEN_WIDTH)
        {
            bullet.health = 0;
        }

        Blit(player.texture, player.x, player.y);

        SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(app.renderer, &bullet.shape);


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
    if(l_event->repeat == 0)
    {
        if(l_event->keysym.scancode == SDL_SCANCODE_W)
        {
            app.up = 1;
        }
        if(l_event->keysym.scancode == SDL_SCANCODE_S)
        {
            app.down = 1;
        }
        if(l_event->keysym.scancode == SDL_SCANCODE_D)
        {
            app.right = 1;
        }
        if(l_event->keysym.scancode == SDL_SCANCODE_A)
        {
            app.left = 1;
        }
        if(l_event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            app.fire = 1;
        }
    }
}

void DoKeyUp(SDL_KeyboardEvent *l_event)
{
    if(l_event->repeat == 0)
    {
        if(l_event->keysym.scancode == SDL_SCANCODE_W)
        {
            app.up = 0;
        }
        if(l_event->keysym.scancode == SDL_SCANCODE_S)
        {
            app.down = 0;
        }
        if(l_event->keysym.scancode == SDL_SCANCODE_D)
        {
            app.right = 0;
        }
        if(l_event->keysym.scancode == SDL_SCANCODE_A)
        {
            app.left = 0;
        }
        if(l_event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            app.fire = 0;
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
