#include "raylib.h"
#include <math.h>
#include <time.h>

#define PLAYER_BASE_SIZE 20.0f
#define PLAYER_SPEED 3.0f
#define NUM_METEORS 8
#define METEOR_SPEED 1
#define MAX_BULLETS 10

typedef float f32;
typedef int i32;

struct Ship
{
    Vector2 position;
    Vector2 speed;
    f32 rotation;
    f32 acceleration;
    Vector3 collider;
};

struct Meteor
{
    Vector2 position;
    Vector2 speed;
    i32 active;
    f32 radius;
};

struct Blaster
{
    Vector2 position;
    Vector2 speed;
    i32 active;
    i32 duration;
    f32 rotation;
    f32 acceleration;
    f32 radius;
};

static const i32 screenWidth = 640;
static const i32 screenHeight = 480;
static f32 shipHeight = (PLAYER_BASE_SIZE/2)/tanf(20*DEG2RAD);

static Ship ship = {0};
static Blaster shot[MAX_BULLETS] = {0};
static Meteor meteor[NUM_METEORS] = {0};
static int gameOver = 0;

void InitGame()
{
    gameOver = 0;
    Vector2 position = {screenWidth/2, screenHeight/2 - shipHeight/2};
    ship.position = position;
    ship.rotation = 0.0f;
    Vector3 collider = {
        ship.position.x + sinf(ship.rotation*DEG2RAD)*(shipHeight/2.5f),
        ship.position.y - cosf(ship.rotation*DEG2RAD)*(shipHeight/2.5f),
        12
    };
    ship.collider = collider;

    for(i32 i=0; i < NUM_METEORS; i++)
    {
        if(!meteor[i].active)
        {
            i32 RightRange = 0;
            f32 posx = GetRandomValue(0, screenWidth);
            while (!RightRange)
            {
                if (posx > (screenWidth / 2 - 200) && posx < (screenWidth / 2 + 200))
                {
                    posx = GetRandomValue(0, screenWidth);
                }
                else
                {
                    RightRange = 1;
                }
            }

            RightRange = 0;
            f32 posy = GetRandomValue(0, screenHeight);
            while (!RightRange)
            {
                if (posy > (screenHeight / 2 - 200) && posy < (screenHeight / 2 + 200))
                {
                    posy = GetRandomValue(0, screenHeight);
                }
                else
                {
                    RightRange = 1;
                }
            }

            Vector2 position = {posx, posy};
            meteor[i].position = position;
            Vector2 speed = {(f32)GetRandomValue(-METEOR_SPEED, METEOR_SPEED), (f32)GetRandomValue(-METEOR_SPEED, METEOR_SPEED)};
            if (speed.x == 0 && speed.y == 0)
            {
                speed.x = (f32)GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
                speed.y = (f32)GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
            }
            meteor[i].speed = speed;
            meteor[i].radius = 40.0f;
            meteor[i].active = 1;
        }
    }
}

void UpdateGame()
{
    if(IsKeyDown(KEY_LEFT))
        ship.rotation -= 2.0f;
    if(IsKeyDown(KEY_RIGHT))
        ship.rotation += 2.0f;
    if(IsKeyDown(KEY_UP))
    {
        if(ship.acceleration < 1.0f)
            ship.acceleration += 0.04f;
        else if(ship.acceleration > 0)
            ship.acceleration -= 0.02f;
        else if(ship.acceleration < 0)
            ship.acceleration = 0;
    }
    if(IsKeyDown(KEY_DOWN))
    {
        if(ship.acceleration > 0)
            ship.acceleration -= 0.02f;
        else if(ship.acceleration < 0)
            ship.acceleration = 0;
    }

    ship.speed.x = sinf(ship.rotation * DEG2RAD) * PLAYER_SPEED;
    ship.speed.y = cosf(ship.rotation * DEG2RAD) * PLAYER_SPEED;
    ship.position.x += (ship.speed.x * ship.acceleration);
    ship.position.y -= (ship.speed.y * ship.acceleration);

    if(ship.position.x > screenWidth)
        ship.position.x = 0.0f;
    else if(ship.position.x < 0)
        ship.position.x = 640.0f;
    if(ship.position.y > screenHeight)
        ship.position.y = 0.0f;
    else if(ship.position.y < 0)
        ship.position.y = 480.0f;
    Vector3 collider = {
        ship.position.x + sinf(ship.rotation*DEG2RAD)*(shipHeight/2.5f),
        ship.position.y - cosf(ship.rotation*DEG2RAD)*(shipHeight/2.5f),
        12
    };
    ship.collider = collider;

    if (IsKeyDown(KEY_SPACE))
    {
        for (i32 i = 0; i < MAX_BULLETS; i++)
        {
            if (!shot[i].active)
            {
                shot[i].rotation = ship.rotation;
                Vector2 position = {
                    ship.position.x + sinf(ship.rotation * DEG2RAD) * (shipHeight),
                    ship.position.y - cosf(ship.rotation * DEG2RAD) * (shipHeight)
                };
                shot[i].position = position;
                Vector2 ShotSpeed = {
                    1.5f * sinf(shot[i].rotation * DEG2RAD) * PLAYER_SPEED,
                    1.5f * cosf(shot[i].rotation * DEG2RAD) * PLAYER_SPEED
                };
                shot[i].speed = ShotSpeed;
                shot[i].active = 1;
                shot[i].duration = 0;
                shot[i].radius = 2.0f;
                break;
            }
        }
    }

    for (i32 i = 0; i < MAX_BULLETS; i++)
    {
        if (shot[i].active)
            shot[i].duration++;
    }

    for (i32 i = 0; i < MAX_BULLETS; i++)
    {
        if (shot[i].active)
        {
            shot[i].position.x += shot[i].speed.x;
            shot[i].position.y -= shot[i].speed.y;
            if (shot[i].duration >= 60)
                shot[i].active = 0;
            if (shot[i].position.x > screenWidth + shot[i].radius)
                shot[i].active = 0;
            else if (shot[i].position.x < -shot[i].radius)
                shot[i].active = 0;
            if (shot[i].position.y > screenHeight + shot[i].radius)
                shot[i].active = 0;
            else if (shot[i].position.y < -shot[i].radius)
                shot[i].active = 0;
        }
    }

    for (i32 i = 0; i < NUM_METEORS; i++)
    {
        if(meteor[i].active)
        {
            meteor[i].position.x += meteor[i].speed.x;
            meteor[i].position.y += meteor[i].speed.y;

            if (meteor[i].position.x > screenWidth + meteor[i].radius)
                meteor[i].position.x = -meteor[i].radius;
            else if (meteor[i].position.x < -meteor[i].radius)
                meteor[i].position.x = screenWidth + meteor[i].radius;
            if (meteor[i].position.y > screenHeight + meteor[i].radius)
                meteor[i].position.y = -meteor[i].radius;
            else if (meteor[i].position.y < -meteor[i].radius)
                meteor[i].position.y = screenHeight + meteor[i].radius;
        }
    }

    for(i32 i = 0; i < NUM_METEORS; i++)
    {
        Vector2 ColliderCenter = {ship.collider.x, ship.collider.y};
        f32 ColliderRadius = ship.collider.z;
        if(meteor[i].active && CheckCollisionCircles(ColliderCenter, ColliderRadius, meteor[i].position, meteor[i].radius))
        {
            gameOver = 1;
        }
    }

    for(i32 i = 0; i < MAX_BULLETS; i++)
    {
        if(shot[i].active)
        {
            for (i32 j = 0; j < NUM_METEORS; j++)
            {
                if(meteor[j].active && CheckCollisionCircles(meteor[j].position, meteor[j].radius, shot[i].position, shot[i].radius))
                {
                    shot[i].active = 0;
                    shot[i].duration = 0;
                    meteor[j].active = 0;
                }
            }
        }
    }
}

void DrawGame()
{
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        if(!gameOver)
        {

            Vector2 v1 =
            {
                ship.position.x + sinf(ship.rotation * DEG2RAD) * (shipHeight),
                ship.position.y - cosf(ship.rotation * DEG2RAD) * (shipHeight)
            };
            Vector2 v2 =
            {
                ship.position.x - cosf(ship.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2),
                ship.position.y - sinf(ship.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2)
            };
            Vector2 v3 =
            {
                ship.position.x + cosf(ship.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2),
                ship.position.y + sinf(ship.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2)
            };

            DrawTriangle(v1, v2, v3, MAROON);

            for (i32 i = 0; i < NUM_METEORS; i++)
            {
                if (meteor[i].active)
                    DrawCircle(meteor[i].position.x, meteor[i].position.y, meteor[i].radius, BLACK);
            }

            for (i32 i = 0; i < MAX_BULLETS; i++)
            {
                if (shot[i].active)
                    DrawCircle(shot[i].position.x, shot[i].position.y, shot[i].radius, DARKBLUE);
            }
        }
        else
        {
            DrawText("You Lost!", 190, 200, 20, LIGHTGRAY);
            if(IsKeyDown(KEY_ENTER))
            {
                gameOver = 0;
                InitGame();
            }
        }
        EndDrawing();
    }
}

i32 main()
{
    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitGame();
    
    while (!WindowShouldClose())
    {
        UpdateGame();
        DrawGame();
    }
    
    CloseWindow();
    
    return 0;
}
