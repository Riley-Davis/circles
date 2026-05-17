#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Circle {
    Vector2 pos;
    float radius;
    Vector2 vel;
    Color color;
} Circle;

bool circles_colliding(Circle circle1, Circle circle2){
    double dist_x = circle1.pos.x - circle2.pos.x;
    double dist_y = circle1.pos.y - circle2.pos.y;

    float dist = sqrt(pow(dist_x, 2) + pow(dist_y, 2));
    if (dist < circle1.radius + circle2.radius){
        return true;
    } 

    return false;
}

Color random_pretty_color(){
    return ColorFromHSV(GetRandomValue(0, 360), 1, 1);
}

void thrust_to(Circle *circle, Vector2 coords, float speed){
    float dx = coords.x - circle->pos.x;
    float dy= coords.y - circle->pos.y;
    //Normalize vector
    float magnitude = sqrt(pow(dx, 2) + pow(dy, 2));
    if (magnitude == 0) return;
    circle->vel.x = (dx / magnitude) * speed;
    circle->vel.y = (dy / magnitude) * speed;
}

int main(){
    const int screenWidth = 16 * 90;
    const int screenHeight = 9 * 90;

    InitWindow(screenWidth, screenHeight, "Circles");

    SetTargetFPS(60);
 

    Circle circle1;
    circle1.pos = (Vector2) {100.0f, 100.0f};
    circle1.radius = 100;
    circle1.vel = (Vector2) {10.5, 10.5};
    circle1.color = random_pretty_color();

    Circle circle2;
    circle2.pos = (Vector2) {(float) screenWidth - 100, (float) screenHeight - 100};
    circle2.radius = 100;
    circle2.vel = (Vector2) {-10.5, -10.5};
    circle2.color = random_pretty_color();

    Circle follower1;
    follower1.pos = (Vector2) {100.0f, 100.0f};
    follower1.radius = 10;
    follower1.vel = (Vector2) {0, 0};
    follower1.color = RED;


    Circle follower2;
    follower2.pos = (Vector2) {(float) screenWidth - 100, (float) screenHeight - 100};
    follower2.radius = 10;
    follower2.vel = (Vector2) {0, 0};
    follower2.color = BLUE;
    
    char* text1;
    char* text2;

    
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            circle1.pos.x += circle1.vel.x;
            circle1.pos.y += circle1.vel.y;

            circle2.pos.x += circle2.vel.x;
            circle2.pos.y += circle2.vel.y;
            
            follower1.pos.x += follower1.vel.x;
            follower1.pos.y += follower1.vel.y;

            follower2.pos.x += follower2.vel.x;
            follower2.pos.y += follower2.vel.y;

            thrust_to(&follower1, circle1.pos, 7.5);
            thrust_to(&follower2, circle2.pos, 7.5);

            if (circle1.pos.x >= screenWidth - 100 || circle1.pos.x <= 0 + 100){
                circle1.vel.x *= -1;

                circle1.color = random_pretty_color();
            }
            if (circle1.pos.y >= screenHeight - 100 || circle1.pos.y <= 0 + 100){
                circle1.vel.y *= -1;
                circle1.color = random_pretty_color();
            }

            if (circle2.pos.x >= screenWidth - 100 || circle2.pos.x <= 0 + 100){
                circle2.vel.x *= -1;
                circle2.color = random_pretty_color();
            }
            if (circle2.pos.y >= screenHeight - 100 || circle2.pos.y <= 0 + 100){
                circle2.vel.y *= -1;
                circle2.color = random_pretty_color();
            }

            if (circles_colliding(circle1, circle2)){
                circle1.vel.x *= -1;
                circle1.vel.y *= -1;
                circle2.vel.x *= -1;
                circle2.vel.y *= -1;

                circle1.color = random_pretty_color();
                circle2.color = random_pretty_color();
            }

            DrawCircle(follower1.pos.x, follower1.pos.y, follower1.radius, follower1.color);
            DrawCircle(follower2.pos.x, follower2.pos.y, follower2.radius, follower2.color);
            // float scale = 1;
            // DrawLine(follower1.pos.x, follower1.pos.y, follower1.pos.x + follower1.vel.x * scale, follower1.pos.y + follower1.vel.y * scale, RED);
            // DrawLine(follower2.pos.x, follower2.pos.y, follower2.pos.x + follower2.vel.x * scale, follower2.pos.y + follower2.vel.y * scale, BLUE);
            DrawCircle(circle1.pos.x, circle1.pos.y, circle1.radius, circle1.color);
            DrawCircle(circle2.pos.x, circle2.pos.y, circle2.radius, circle2.color);
            
            
            asprintf(&text1, "Circle1 x: %f, y: %f", circle1.pos.x, circle1.pos.y);
            asprintf(&text2, "Circle2 x: %f, y: %f", circle2.pos.x, circle2.pos.y);
            DrawText(text1, 0, 0, 20, RED);
            DrawText(text2, 0, 20, 20, BLUE);
            DrawText(TextFormat("follower1 velx: %03f, follower1 vely: %03f", follower1.vel.x, follower1.vel.y), 0, 40, 20, GREEN);
            free(text1);
            free(text2);
        EndDrawing();
    }

    
    CloseWindow();
    return 0;
}