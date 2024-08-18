
#include "ctype.h"
#include "defs.h"
#include "math.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "structs.h"

#include "draw.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


extern App app;

//App app; //why does this work without the extern keyword? - it does not on linux

SDL_Texture* LoadTexture(char *filename)
{
    SDL_Texture *texture = NULL;
    unsigned char* imageData = NULL;
    int width, height, numChannels = 0;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    imageData = stbi_load(filename, &width, &height, &numChannels, 4);
    if(imageData == NULL)
    {
        SDL_Log("stbi_load() Failed: %s\n", stbi_failure_reason());
        return NULL;
    }

    texture = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, width, height);
    if(texture == NULL)
    {
        SDL_Log("Error with SDL_CreateTexture(): %s", SDL_GetError());
        return NULL;
    }

    if(SDL_UpdateTexture(texture, NULL, imageData, width*sizeof(unsigned char)*4) != 0)
    {
        SDL_Log("Error with SDL_UpdateTexture(): %s", SDL_GetError());
        return NULL;
    }

    //allows PNG transparency
    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);

    //delete the stbi image data 
    stbi_image_free(imageData);

    return texture;
}


void Blit(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);


}
