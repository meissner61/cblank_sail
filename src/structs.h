
#include "defs.h"

#include "SDL.h"

typedef struct Entity Entity;

typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];

} App;

struct Entity 
{
    int x;
    int y;
    int width;
    int height;
    int dx;
    int dy;
    int health;
    int reload;
    SDL_Rect shape;
    SDL_Texture* texture;
    Entity *next;
};


typedef struct
{
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
} Stage;