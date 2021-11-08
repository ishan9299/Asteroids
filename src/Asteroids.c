/* #include "raylib.h" */
/* #include <math.h> */
/* #include <time.h> */
/*  */
/* #define PLAYER_BASE_SIZE 20.0f */
/* #define PLAYER_SPEED 3.0f */
/* #define NUM_METEORS 8 */
/* #define METEOR_SPEED 1 */
/* #define MAX_BULLETS 1 */
/*  */
/* typedef float f32; */
/* typedef int i32; */
/*  */
/* struct Ship */
/* { */
/*     Vector2 position; */
/*     Vector2 speed; */
/*     f32 rotation; */
/*     f32 acceleration; */
/*     Vector3 collider; */
/* }; */
/*  */
/* struct Meteor */
/* { */
/*     Vector2 position; */
/*     Vector2 speed; */
/*     i32 active; */
/*     f32 radius; */
/* }; */
/*  */
/* struct Blaster */
/* { */
/*     Vector2 position; */
/*     Vector2 speed; */
/*     i32 active; */
/*     i32 life; */
/*     f32 rotation; */
/*     f32 acceleration; */
/*     f32 radius; */
/* }; */
/*  */
/* static const i32 screenWidth = 640; */
/* static const i32 screenHeight = 480; */
/* static f32 shipHeight = (PLAYER_BASE_SIZE/2)/tanf(20*DEG2RAD); */
/*  */
/* static Ship ship = {0}; */
/* static Blaster blaster[MAX_BULLETS] = {0}; */
/* static Meteor meteor[NUM_METEORS] = {0}; */
/* static int gameOver = 0; */
/*  */
/* void InitGame() */
/* { */
/*     gameOver = 0; */
/*     Vector2 position = {screenWidth/2, screenHeight/2 - shipHeight/2}; */
/*     ship.position = position; */
/*     ship.rotation = 0.0f; */
/*     Vector3 collider = { */
/*         ship.position.x + sinf(ship.rotation*DEG2RAD)*(shipHeight/2.5f), */
/*         ship.position.y - cosf(ship.rotation*DEG2RAD)*(shipHeight/2.5f), */
/*         12 */
/*     }; */
/*     ship.collider = collider; */
/*  */
/*     for(i32 i=0; i < NUM_METEORS; i++) */
/*     { */
/*         if(!meteor[i].active) */
/*         { */
/*             i32 RightRange = 0; */
/*             f32 posx = GetRandomValue(0, screenWidth); */
/*             while (!RightRange) */
/*             { */
/*                 if (posx > (screenWidth / 2 - 200) && posx < (screenWidth / 2 + 200)) */
/*                 { */
/*                     posx = GetRandomValue(0, screenWidth); */
/*                 } */
/*                 else */
/*                 { */
/*                     RightRange = 1; */
/*                 } */
/*             } */
/*  */
/*             RightRange = 0; */
/*             f32 posy = GetRandomValue(0, screenHeight); */
/*             while (!RightRange) */
/*             { */
/*                 if (posy > (screenHeight / 2 - 200) && posy < (screenHeight / 2 + 200)) */
/*                 { */
/*                     posy = GetRandomValue(0, screenHeight); */
/*                 } */
/*                 else */
/*                 { */
/*                     RightRange = 1; */
/*                 } */
/*             } */
/*  */
/*             Vector2 position = {posx, posy}; */
/*             meteor[i].position = position; */
/*             Vector2 speed = {(f32)GetRandomValue(-METEOR_SPEED, METEOR_SPEED), (f32)GetRandomValue(-METEOR_SPEED, METEOR_SPEED)}; */
/*             if (speed.x == 0 && speed.y == 0) */
/*             { */
/*                 speed.x = (f32)GetRandomValue(-METEOR_SPEED, METEOR_SPEED); */
/*                 speed.y = (f32)GetRandomValue(-METEOR_SPEED, METEOR_SPEED); */
/*             } */
/*             meteor[i].speed = speed; */
/*             meteor[i].radius = 40.0f; */
/*             meteor[i].active = 1; */
/*         } */
/*     } */
/* } */
/*  */
/* void UpdateGame() */
/* { */
/*     if (IsKeyDown(KEY_LEFT)) */
/*         ship.rotation -= 2.0f; */
/*     if (IsKeyDown(KEY_RIGHT)) */
/*         ship.rotation += 2.0f; */
/*     if (IsKeyDown(KEY_UP)) */
/*         if (ship.acceleration < 1.0f) */
/*             ship.acceleration += 0.04f; */
/*         else if (ship.acceleration > 0) */
/*             ship.acceleration -= 0.02f; */
/*         else if (ship.acceleration < 0) */
/*             ship.acceleration = 0; */
/*     if (IsKeyDown(KEY_DOWN)) */
/*         if (ship.acceleration > 0) */
/*             ship.acceleration -= 0.02f; */
/*         else if (ship.acceleration < 0) */
/*             ship.acceleration = 0; */
/*  */
/*     ship.speed.x = sinf(ship.rotation * DEG2RAD) * PLAYER_SPEED; */
/*     ship.speed.y = cosf(ship.rotation * DEG2RAD) * PLAYER_SPEED; */
/*     ship.position.x += (ship.speed.x * ship.acceleration); */
/*     ship.position.y -= (ship.speed.y * ship.acceleration); */
/*  */
/*     if (ship.position.x > screenWidth) */
/*         ship.position.x = 0.0f; */
/*     else if (ship.position.x < 0) */
/*         ship.position.x = 640.0f; */
/*     if (ship.position.y > screenHeight) */
/*         ship.position.y = 0.0f; */
/*     else if (ship.position.y < 0) */
/*         ship.position.y = 480.0f; */
/*  */
/*     if (IsKeyDown(KEY_SPACE)) */
/*     { */
/*         for (i32 i = 0; i < MAX_BULLETS; i++) */
/*         { */
/*             if (!blaster[i].active) */
/*             { */
/*                 blaster[i].rotation = ship.rotation; */
/*                 blaster[i].position = { */
/*                     ship.position.x + sinf(ship.rotation * DEG2RAD) * (shipHeight), */
/*                     ship.position.y - cosf(ship.rotation * DEG2RAD) * (shipHeight) */
/*                 }; */
/*                 Vector2 BlasterSpeed = { */
/*                     1.5f * sinf(blaster[i].rotation * DEG2RAD) * PLAYER_SPEED, */
/*                     1.5f * cosf(blaster[i].rotation * DEG2RAD) * PLAYER_SPEED */
/*                 }; */
/*                 blaster[i].speed = BlasterSpeed; */
/*                 blaster[i].active = 1; */
/*                 blaster[i].life = 0; */
/*                 blaster[i].radius = 2.0f; */
/*                 break; */
/*             } */
/*         } */
/*     } */
/*  */
/*     for (i32 i = 0; i < MAX_BULLETS; i++) */
/*     { */
/*         if (blaster[i].active) */
/*             blaster[i].life++; */
/*     } */
/*  */
/*     for (i32 i = 0; i < MAX_BULLETS; i++) */
/*     { */
/*         if (blaster[i].active) */
/*         { */
/*             blaster[i].position.x += blaster[i].speed.x; */
/*             blaster[i].position.y -= blaster[i].speed.y; */
/*             if (blaster[i].life >= 60) */
/*                 blaster[i].active = 0; */
/*             if (blaster[i].position.x > screenWidth + blaster[i].radius) */
/*                 blaster[i].active = 0; */
/*             else if (blaster[i].position.y < -blaster[i].radius) */
/*                 blaster[i].active = 0; */
/*             if (blaster[i].position.y > screenHeight + blaster[i].radius) */
/*                 blaster[i].active = 0; */
/*             else if (blaster[i].position.y < -blaster[i].radius) */
/*                 blaster[i].active = 0; */
/*         } */
/*     } */
/*  */
/*     for (i32 i = 0; i < NUM_METEORS; i++) */
/*     { */
/*         if(meteor[i].active) */
/*         { */
/*             Vector2 c1 = {meteor[i].position.x, */
/*                           meteor[i].position.y}; */
/*  */
/*             meteor[i].position.x += meteor[i].speed.x; */
/*             meteor[i].position.y += meteor[i].speed.y; */
/*  */
/*             if (meteor[i].position.x > screenWidth + meteor[i].radius) */
/*                 meteor[i].position.x = -meteor[i].radius; */
/*             else if (meteor[i].position.x < -meteor[i].radius) */
/*                 meteor[i].position.x = screenWidth + meteor[i].radius; */
/*             if (meteor[i].position.y > screenHeight + meteor[i].radius) */
/*                 meteor[i].position.y = -meteor[i].radius; */
/*             else if (meteor[i].position.y < -meteor[i].radius) */
/*                 meteor[i].position.y = screenHeight + meteor[i].radius; */
/*         } */
/*     } */
/*  */
/*     for(i32 i = 0; i < NUM_METEORS; i++) */
/*     { */
/*         Vector2 ColliderCenter = {ship.collider.x, ship.collider.y}; */
/*         f32 ColliderRadius = ship.collider.z; */
/*         if(meteor[i].active && CheckCollisionCircles(ColliderCenter, ColliderRadius, meteor[i].position, meteor[i].radius)) */
/*         { */
/*             gameOver = 1; */
/*         } */
/*     } */
/*  */
/*     for(i32 i = 0; i < MAX_BULLETS; i++) */
/*     { */
/*         if(blaster[i].active) */
/*         { */
/*             for (i32 j = 0; j < NUM_METEORS; j++) */
/*             { */
/*                 if(meteor[i].active && CheckCollisionCircles(meteor[i].position, meteor[i].radius, blaster[i].position, blaster[i].radius)) */
/*                 { */
/*                     blaster[i].active = 0; */
/*                     blaster[i].life = 0; */
/*                     meteor[i].active = 0; */
/*                 } */
/*             } */
/*         } */
/*     } */
/* } */
/*  */
/* void DrawGame() */
/* { */
/*     BeginDrawing(); */
/*     { */
/*         ClearBackground(RAYWHITE); */
/*         if(!gameOver) */
/*         { */
/*  */
/*             Vector2 v1 = */
/*             { */
/*                 ship.position.x + sinf(ship.rotation * DEG2RAD) * (shipHeight), */
/*                 ship.position.y - cosf(ship.rotation * DEG2RAD) * (shipHeight) */
/*             }; */
/*             Vector2 v2 = */
/*             { */
/*                 ship.position.x - cosf(ship.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), */
/*                 ship.position.y - sinf(ship.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2) */
/*             }; */
/*             Vector2 v3 = */
/*             { */
/*                 ship.position.x + cosf(ship.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), */
/*                 ship.position.y + sinf(ship.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2) */
/*             }; */
/*  */
/*             DrawTriangle(v1, v2, v3, MAROON); */
/*  */
/*             for (i32 i = 0; i < NUM_METEORS; i++) */
/*             { */
/*                 if (meteor[i].active) */
/*                     DrawCircleLines(meteor[i].position.x, meteor[i].position.y, meteor[i].radius, BLACK); */
/*             } */
/*  */
/*             for (i32 i = 0; i < MAX_BULLETS; i++) */
/*             { */
/*                 if (blaster[i].active) */
/*                     DrawCircleLines(blaster[i].position.x, blaster[i].position.y, blaster[i].radius, DARKBLUE); */
/*             } */
/*         } */
/*         else */
/*         { */
/*             DrawText("You Lost!", 190, 200, 20, LIGHTGRAY); */
/*         } */
/*         EndDrawing(); */
/*     } */
/* } */
/*  */
/* i32 main() */
/* { */
/*     SetTargetFPS(60); */
/*     InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window"); */
/*     InitGame(); */
/*      */
/*     while (!WindowShouldClose()) */
/*     { */
/*         UpdateGame(); */
/*         DrawGame(); */
/*     } */
/*      */
/*     CloseWindow(); */
/*      */
/*     return 0; */
/* } */











































/*******************************************************************************************
*
*   raylib - classic game: asteroids
*
*   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <math.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define PLAYER_BASE_SIZE    20.0f
#define PLAYER_SPEED        6.0f
#define PLAYER_MAX_SHOOTS   10

#define METEORS_SPEED       2
#define MAX_BIG_METEORS     4
#define MAX_MEDIUM_METEORS  8
#define MAX_SMALL_METEORS   16

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Player {
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    Vector3 collider;
    Color color;
} Player;

typedef struct Shoot {
    Vector2 position;
    Vector2 speed;
    float radius;
    float rotation;
    int lifeSpawn;
    bool active;
    Color color;
} Shoot;

typedef struct Meteor {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
    Color color;
} Meteor;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;
static bool victory = false;

// NOTE: Defined triangle is isosceles with common angles of 70 degrees.
static float shipHeight = 0.0f;

static Player player = { 0 };
static Shoot shoot[PLAYER_MAX_SHOOTS] = { 0 };
static Meteor bigMeteor[MAX_BIG_METEORS] = { 0 };
static Meteor mediumMeteor[MAX_MEDIUM_METEORS] = { 0 };
static Meteor smallMeteor[MAX_SMALL_METEORS] = { 0 };

static int midMeteorsCount = 0;
static int smallMeteorsCount = 0;
static int destroyedMeteorsCount = 0;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "classic game: asteroids");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
    int posx, posy;
    int velx, vely;
    bool correctRange = false;
    victory = false;
    pause = false;

    shipHeight = (PLAYER_BASE_SIZE/2)/tanf(20*DEG2RAD);

    // Initialization player
    player.position = (Vector2){screenWidth/2, screenHeight/2 - shipHeight/2};
    player.speed = (Vector2){0, 0};
    player.acceleration = 0;
    player.rotation = 0;
    player.collider = (Vector3){player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight/2.5f), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight/2.5f), 12};
    player.color = LIGHTGRAY;

    destroyedMeteorsCount = 0;

    // Initialization shoot
    for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
    {
        shoot[i].position = (Vector2){0, 0};
        shoot[i].speed = (Vector2){0, 0};
        shoot[i].radius = 2;
        shoot[i].active = false;
        shoot[i].lifeSpawn = 0;
        shoot[i].color = WHITE;
    }

    for (int i = 0; i < MAX_BIG_METEORS; i++)
    {
        posx = GetRandomValue(0, screenWidth);

        while (!correctRange)
        {
            if (posx > screenWidth/2 - 150 && posx < screenWidth/2 + 150) posx = GetRandomValue(0, screenWidth);
            else correctRange = true;
        }

        correctRange = false;

        posy = GetRandomValue(0, screenHeight);

        while (!correctRange)
        {
            if (posy > screenHeight/2 - 150 && posy < screenHeight/2 + 150)  posy = GetRandomValue(0, screenHeight);
            else correctRange = true;
        }

        bigMeteor[i].position = (Vector2){posx, posy};

        correctRange = false;
        velx = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
        vely = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);

        while (!correctRange)
        {
            if (velx == 0 && vely == 0)
            {
                velx = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
                vely = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
            }
            else correctRange = true;
        }

        bigMeteor[i].speed = (Vector2){velx, vely};
        bigMeteor[i].radius = 40;
        bigMeteor[i].active = true;
        bigMeteor[i].color = BLUE;
    }

    for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
    {
        mediumMeteor[i].position = (Vector2){-100, -100};
        mediumMeteor[i].speed = (Vector2){0,0};
        mediumMeteor[i].radius = 20;
        mediumMeteor[i].active = false;
        mediumMeteor[i].color = BLUE;
    }

    for (int i = 0; i < MAX_SMALL_METEORS; i++)
    {
        smallMeteor[i].position = (Vector2){-100, -100};
        smallMeteor[i].speed = (Vector2){0,0};
        smallMeteor[i].radius = 10;
        smallMeteor[i].active = false;
        smallMeteor[i].color = BLUE;
    }

    midMeteorsCount = 0;
    smallMeteorsCount = 0;
}

// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            // Player logic: rotation
            if (IsKeyDown(KEY_LEFT)) player.rotation -= 5;
            if (IsKeyDown(KEY_RIGHT)) player.rotation += 5;

            // Player logic: speed
            player.speed.x = sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
            player.speed.y = cos(player.rotation*DEG2RAD)*PLAYER_SPEED;

            // Player logic: acceleration
            if (IsKeyDown(KEY_UP))
            {
                if (player.acceleration < 1) player.acceleration += 0.04f;
            }
            else
            {
                if (player.acceleration > 0) player.acceleration -= 0.02f;
                else if (player.acceleration < 0) player.acceleration = 0;
            }
            if (IsKeyDown(KEY_DOWN))
            {
                if (player.acceleration > 0) player.acceleration -= 0.04f;
                else if (player.acceleration < 0) player.acceleration = 0;
            }

            // Player logic: movement
            player.position.x += (player.speed.x*player.acceleration);
            player.position.y -= (player.speed.y*player.acceleration);

            // Collision logic: player vs walls
            if (player.position.x > screenWidth + shipHeight) player.position.x = -(shipHeight);
            else if (player.position.x < -(shipHeight)) player.position.x = screenWidth + shipHeight;
            if (player.position.y > (screenHeight + shipHeight)) player.position.y = -(shipHeight);
            else if (player.position.y < -(shipHeight)) player.position.y = screenHeight + shipHeight;

            // Player shoot logic
            if (IsKeyPressed(KEY_SPACE))
            {
                for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
                {
                    if (!shoot[i].active)
                    {
                        shoot[i].position = (Vector2){ player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight) };
                        shoot[i].active = true;
                        shoot[i].speed.x = 1.5*sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
                        shoot[i].speed.y = 1.5*cos(player.rotation*DEG2RAD)*PLAYER_SPEED;
                        shoot[i].rotation = player.rotation;
                        break;
                    }
                }
            }

            // Shoot life timer
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
            {
                if (shoot[i].active) shoot[i].lifeSpawn++;
            }

            // Shot logic
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
            {
                if (shoot[i].active)
                {
                    // Movement
                    shoot[i].position.x += shoot[i].speed.x;
                    shoot[i].position.y -= shoot[i].speed.y;

                    // Collision logic: shoot vs walls
                    if  (shoot[i].position.x > screenWidth + shoot[i].radius)
                    {
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    else if (shoot[i].position.x < 0 - shoot[i].radius)
                    {
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    if (shoot[i].position.y > screenHeight + shoot[i].radius)
                    {
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    else if (shoot[i].position.y < 0 - shoot[i].radius)
                    {
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }

                    // Life of shoot
                    if (shoot[i].lifeSpawn >= 60)
                    {
                        shoot[i].position = (Vector2){0, 0};
                        shoot[i].speed = (Vector2){0, 0};
                        shoot[i].lifeSpawn = 0;
                        shoot[i].active = false;
                    }
                }
            }

            // Collision logic: player vs meteors
            player.collider = (Vector3){player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight/2.5f), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight/2.5f), 12};

            for (int a = 0; a < MAX_BIG_METEORS; a++)
            {
                if (CheckCollisionCircles((Vector2){player.collider.x, player.collider.y}, player.collider.z, bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active) gameOver = true;
            }

            for (int a = 0; a < MAX_MEDIUM_METEORS; a++)
            {
                if (CheckCollisionCircles((Vector2){player.collider.x, player.collider.y}, player.collider.z, mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active) gameOver = true;
            }

            for (int a = 0; a < MAX_SMALL_METEORS; a++)
            {
                if (CheckCollisionCircles((Vector2){player.collider.x, player.collider.y}, player.collider.z, smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active) gameOver = true;
            }

            // Meteors logic: big meteors
            for (int i = 0; i < MAX_BIG_METEORS; i++)
            {
                if (bigMeteor[i].active)
                {
                    // Movement
                    bigMeteor[i].position.x += bigMeteor[i].speed.x;
                    bigMeteor[i].position.y += bigMeteor[i].speed.y;

                    // Collision logic: meteor vs wall
                    if  (bigMeteor[i].position.x > screenWidth + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
                    else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = screenWidth + bigMeteor[i].radius;
                    if (bigMeteor[i].position.y > screenHeight + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
                    else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = screenHeight + bigMeteor[i].radius;
                }
            }

            // Meteors logic: medium meteors
            for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
            {
                if (mediumMeteor[i].active)
                {
                    // Movement
                    mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
                    mediumMeteor[i].position.y += mediumMeteor[i].speed.y;

                    // Collision logic: meteor vs wall
                    if  (mediumMeteor[i].position.x > screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
                    else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
                    if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
                    else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
                }
            }

            // Meteors logic: small meteors
            for (int i = 0; i < MAX_SMALL_METEORS; i++)
            {
                if (smallMeteor[i].active)
                {
                    // Movement
                    smallMeteor[i].position.x += smallMeteor[i].speed.x;
                    smallMeteor[i].position.y += smallMeteor[i].speed.y;

                    // Collision logic: meteor vs wall
                    if  (smallMeteor[i].position.x > screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
                    else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
                    if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
                    else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
                }
            }

            // Collision logic: player-shoots vs meteors
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
            {
                if ((shoot[i].active))
                {
                    for (int a = 0; a < MAX_BIG_METEORS; a++)
                    {
                        if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius))
                        {
                            shoot[i].active = false;
                            shoot[i].lifeSpawn = 0;
                            bigMeteor[a].active = false;
                            destroyedMeteorsCount++;

                            for (int j = 0; j < 2; j ++)
                            {
                                if (midMeteorsCount%2 == 0)
                                {
                                    mediumMeteor[midMeteorsCount].position = (Vector2){bigMeteor[a].position.x, bigMeteor[a].position.y};
                                    mediumMeteor[midMeteorsCount].speed = (Vector2){cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1, sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1};
                                }
                                else
                                {
                                    mediumMeteor[midMeteorsCount].position = (Vector2){bigMeteor[a].position.x, bigMeteor[a].position.y};
                                    mediumMeteor[midMeteorsCount].speed = (Vector2){cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED, sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED};
                                }

                                mediumMeteor[midMeteorsCount].active = true;
                                midMeteorsCount ++;
                            }
                            //bigMeteor[a].position = (Vector2){-100, -100};
                            bigMeteor[a].color = RED;
                            a = MAX_BIG_METEORS;
                        }
                    }

                    for (int b = 0; b < MAX_MEDIUM_METEORS; b++)
                    {
                        if (mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, mediumMeteor[b].position, mediumMeteor[b].radius))
                        {
                            shoot[i].active = false;
                            shoot[i].lifeSpawn = 0;
                            mediumMeteor[b].active = false;
                            destroyedMeteorsCount++;

                            for (int j = 0; j < 2; j ++)
                            {
                                 if (smallMeteorsCount%2 == 0)
                                {
                                    smallMeteor[smallMeteorsCount].position = (Vector2){mediumMeteor[b].position.x, mediumMeteor[b].position.y};
                                    smallMeteor[smallMeteorsCount].speed = (Vector2){cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1, sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1};
                                }
                                else
                                {
                                    smallMeteor[smallMeteorsCount].position = (Vector2){mediumMeteor[b].position.x, mediumMeteor[b].position.y};
                                    smallMeteor[smallMeteorsCount].speed = (Vector2){cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED, sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED};
                                }

                                smallMeteor[smallMeteorsCount].active = true;
                                smallMeteorsCount ++;
                            }
                            //mediumMeteor[b].position = (Vector2){-100, -100};
                            mediumMeteor[b].color = GREEN;
                            b = MAX_MEDIUM_METEORS;
                        }
                    }

                    for (int c = 0; c < MAX_SMALL_METEORS; c++)
                    {
                        if (smallMeteor[c].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, smallMeteor[c].position, smallMeteor[c].radius))
                        {
                            shoot[i].active = false;
                            shoot[i].lifeSpawn = 0;
                            smallMeteor[c].active = false;
                            destroyedMeteorsCount++;
                            smallMeteor[c].color = YELLOW;
                           // smallMeteor[c].position = (Vector2){-100, -100};
                            c = MAX_SMALL_METEORS;
                        }
                    }
                }
            }
        }

        if (destroyedMeteorsCount == MAX_BIG_METEORS + MAX_MEDIUM_METEORS + MAX_SMALL_METEORS) victory = true;
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

        ClearBackground(RAYWHITE);

        if (!gameOver)
        {
            // Draw spaceship
            Vector2 v1 = { player.position.x + sinf(player.rotation*DEG2RAD)*(shipHeight), player.position.y - cosf(player.rotation*DEG2RAD)*(shipHeight) };
            Vector2 v2 = { player.position.x - cosf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE/2), player.position.y - sinf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE/2) };
            Vector2 v3 = { player.position.x + cosf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE/2), player.position.y + sinf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE/2) };
            DrawTriangle(v1, v2, v3, MAROON);

            // Draw meteors
            for (int i = 0; i < MAX_BIG_METEORS; i++)
            {
                if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
                else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
            }

            for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
            {
                if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, GRAY);
                else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
            }

            for (int i = 0; i < MAX_SMALL_METEORS; i++)
            {
                if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, GRAY);
                else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
            }

            // Draw shoot
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
            {
                if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, BLACK);
            }

            if (victory) DrawText("VICTORY", screenWidth/2 - MeasureText("VICTORY", 20)/2, screenHeight/2, 20, LIGHTGRAY);

            if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
        else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);

    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}



