
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

void logAppStateToFile(const App* app);

App app;
Stage stage;




int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    memset(&app, 0, sizeof(App));

    logAppStateToFile(&app);

    //printf("WTF is going on:\n");
    //printf("App:\n app.renderer: %p\n", (void*)app.renderer);
    //printf("app.renderer: %p\n", (void*)app.window);
    //printf("app.delegate.draw %p\n", app.delegate.draw);
    //printf("app.delegate.logic %p\n", app.delegate.logic);

    //printf("Keyboard array contents:\n");
    //for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
    //{
    //    // Print the index and the value at that index
    //    printf("Key[%d] = %d\n", i, app.keyboard[i]);
    //}


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

    logAppStateToFile(&app);
}

void DoKeyUp(SDL_KeyboardEvent *l_event)
{
    if(l_event->repeat == 0 && l_event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        app.keyboard[l_event->keysym.scancode] = 0;
    }
}

void logAppStateToFile(const App* app)
{
    // Open the file for writing
    //a for append mode, means that it will not over write what is in there 
    FILE* file = fopen("app_log.txt", "a"); // "a" for append mode
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // Write the output to the file instead of the console
    fprintf(file, "app state logging:\n");
    fprintf(file, "App:\napp.renderer: %p\n", (void*)app->renderer);
    fprintf(file, "app.window: %p\n", (void*)app->window);
    fprintf(file, "app.delegate.draw: %p\n", (void*)app->delegate.draw);
    fprintf(file, "app.delegate.logic: %p\n", (void*)app->delegate.logic);

    fprintf(file, "Keyboard array contents:\n");
    for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
    {
        if (app->keyboard[i] > 0)
        {
            // Print the index and the value at that index
            fprintf(file, "Key[%d] = %d\n", i, app->keyboard[i]);
        }
        else
        {
            fprintf(file, "All contents of app.keyboard[] are 0\n");
        }

    }

    fprintf(file, "-------------------------------------------\n\n\n");

    // Close the file
    fclose(file);
}

// void Blit(SDL_Texture *texture, int x, int y)
// {
//     SDL_Rect dest;

//     dest.x = x;
//     dest.y = y;

//     SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

//     SDL_RenderCopy(app.renderer, texture, NULL, &dest);


// }
