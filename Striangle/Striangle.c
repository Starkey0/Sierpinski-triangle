

/*******************************************************************************************
*
*   raylib [shapes] example - Draw basic shapes 2d (rectangle, circle, line...)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

typedef struct Triangle
{
    Vector2 vu;
    Vector2 vl;
    Vector2 vr;
    Color color;
};
typedef struct Triangle Triangle;


Triangle* SubdivideTris(Triangle* ptri, int *size)
{
    int new_size = 3 * *size;
    int i = 0;
    Triangle* new_ptri = (Triangle *) malloc(new_size * sizeof(Triangle));
    Triangle tri,tri_up,tri_left,tri_right;
    Vector2 mdown, mleft, mright;

    for (i = 0; i < *size; i++)
    {
        tri = *(ptri + i);
        mdown = (Vector2) {tri.vu.x, tri.vl.y};
        mleft = (Vector2) {tri.vl.x + (mdown.x-tri.vl.x)/2, mdown.y + (tri.vu.y-mdown.y)/2};
        mright = (Vector2) {mdown.x + (tri.vr.x - mdown.x) / 2, mleft.y};

        tri_up.vu = tri.vu;
        tri_up.vl = mleft;
        tri_up.vr = mright;
        
        tri_left.vu = mleft;
        tri_left.vl = tri.vl;
        tri_left.vr = mdown;

        tri_right.vu = mright;
        tri_right.vl = mdown;
        tri_right.vr = tri.vr;

        *(new_ptri + (3 * i)) = tri_up;
        *(new_ptri + (3 * i) + 1) = tri_left;
        *(new_ptri + (3 * i) + 2) = tri_right;
    }

    free(ptri);
    *size = new_size;

    return new_ptri;
}



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1800;
    const int screenHeight = 1000;
    Triangle tri;
    Triangle* ptri;
    int size = 1;
    int i = 0;

    tri.vu = (Vector2){ screenWidth / 2, 0 };
    tri.vl = (Vector2){ 0, screenHeight };
    tri.vr = (Vector2){ screenWidth, screenHeight };

    ptri = (Triangle*)malloc(sizeof(Triangle));
    *ptri = tri;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");

    SetTargetFPS(1);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (i = 0; i < size; i++)
        {
            DrawTriangle((ptri+i)->vu, (ptri + i)->vl, (ptri + i)->vr, VIOLET);
        }

        ptri = SubdivideTris(ptri, &size);
        

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    free(ptri);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

