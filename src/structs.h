
#include "SDL.h"

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int left;
    int right;
    int fire;
} App;

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int health;
    SDL_Rect shape;
    SDL_Texture* texture;
} Entity;