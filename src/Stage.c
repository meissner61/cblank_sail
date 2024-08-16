#include "Stage.h"

#include "draw.h"
#include "structs.h"



extern App app;
extern Stage stage;

static void logic();
static void draw();
static void InitPlayer();
static void FireBullet();
static void DoPlayer();
static void DoBullets();
static void DrawPlayer();
static void DrawBullets();


static Entity *player;
static SDL_Texture *bulletTexture;

void InitStage()
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;

    InitPlayer();

    bulletTexture = LoadTexture("../data/laser_beam.png");

}

static void InitPlayer()
{
    player = malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    stage.fighterTail->next = player;
    stage.fighterTail = player;

    player->x = 100;
    player->y = 100;
    player->texture = LoadTexture("../data/player.png");
    SDL_QueryTexture(player->texture, NULL, NULL, &player->width, &player->height);
}

static void logic(void)
{
    DoPlayer();
    DoBullets();
}

static void DoPlayer()
{
    player->dx = player->dy = 0;
    if(player->reload > 0)
    {
        player->reload--;
    }

    if(app.keyboard[SDL_SCANCODE_W])
    {
        player->dy = -PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_S])
    {
        player->dy = PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_A])
    {
        player->dx = -PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_D])
    {
        player->dx = PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_SPACE] && player->reload == 0)
    {
        FireBullet();
    }

    player->x += player->dx;
    player->y += player->dy;
}

static void FireBullet()
{
    Entity *bullet;

    bullet = malloc(sizeof(Entity));
    memset(bullet, 0 , sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->x = player->x;
    bullet->y = player->y;
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->width, &bullet->height);

    bullet->y += (player->height / 2) - (bullet->height / 2);

    player->reload = 8;
}

static void DoBullets()
{
    Entity *b, *prev;

    prev = &stage.bulletHead;
    for(b = stage.bulletHead.next; b!= NULL; b=b->next)
    {
        b->x += b->dx;
        b->y += b->dy;

        if(b->x > SCREEN_WIDTH)
        {
            if(b == stage.bulletTail)
            {
                stage.bulletTail = prev;
            }
            prev->next = b->next;
            free(b);
            b = prev;
        }
        prev = b;
    }
}

static void draw()
{
    DrawPlayer();
    DrawBullets();
}

static void DrawPlayer()
{
    Blit(player->texture, player->x, player->y);
}

static void DrawBullets()
{
    Entity *b;

    for(b = stage.bulletHead.next; b != NULL; b = b->next)
    {
        Blit(b->texture, b->x, b->y);
    }
}