#include <box2d/box2d.h>
#include <box2d/collision.h>
#include <box2d/id.h>
#include <box2d/math_functions.h>
#include <box2d/types.h>
#include <raylib.h>
#include "fruit.h"

b2WorldId world_id;

int main() {
    InitWindow(600, 800, "Arbuz-Arbuz");
    SetTargetFPS(60);
    init_fruits();

    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = {0, 9.81*128};
    world_def.hitEventThreshold = 0.0f;
    world_id = b2CreateWorld(&world_def);
    b2SetLengthUnitsPerMeter(128.0f);

    b2BodyDef ground_body_def = b2DefaultBodyDef();
    ground_body_def.position = {START_X, 755+START_X};
    b2BodyId ground_id = b2CreateBody(world_id, &ground_body_def);
    b2Polygon ground_box = b2MakeBox(END_X-START_X+5, 1.0f);
    b2ShapeDef ground_shape_def = b2DefaultShapeDef();
    b2CreatePolygonShape(ground_id, &ground_shape_def, &ground_box);

    b2BodyDef wall_body_def = b2DefaultBodyDef();
    wall_body_def.position = {START_X, 20};
    b2BodyId wall_id = b2CreateBody(world_id, &wall_body_def);
    b2Polygon wall_box = b2MakeBox(5.0f, 750.0f);
    b2ShapeDef wall_shape_def = b2DefaultShapeDef();
    b2CreatePolygonShape(wall_id, &wall_shape_def, &wall_box);

    b2BodyDef wall2_body_def = b2DefaultBodyDef();
    wall2_body_def.position = {END_X, 20};
    b2BodyId wall2_id = b2CreateBody(world_id, &wall2_body_def);
    b2Polygon wall2_box = b2MakeBox(5.0f, 750.0f);
    b2ShapeDef wall2_shape_def = b2DefaultShapeDef();
    b2CreatePolygonShape(wall2_id, &wall2_shape_def, &wall2_box);

    struct  {
        FruitType type = select_random_fruit();
        Vector2 position = {100, 20};
        bool disabled = false;
        float disabled_timer = 0;
    } RandomFruit;

    while (!WindowShouldClose()) {
        if (!end) {
            b2World_Step(world_id, GetFrameTime(), 4);
            Vector2 mouse = GetMousePosition();

            if (RandomFruit.disabled) {
                RandomFruit.disabled_timer += GetFrameTime();
                if (RandomFruit.disabled_timer >= 1.0f) {
                    RandomFruit.type = select_random_fruit();
                    RandomFruit.disabled_timer = 0;
                    RandomFruit.disabled = false;
                }
            }

            FruitTemplate random_fruit_data = fruit_db[RandomFruit.type];
            RandomFruit.position.x = mouse.x;

            float min = 20+random_fruit_data.radius+5;
            float max = END_X-5-random_fruit_data.radius;
            if (RandomFruit.position.x < min)
                RandomFruit.position.x = min;
            else if (RandomFruit.position.x > max)
                RandomFruit.position.x = max;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !RandomFruit.disabled) {
                spawn_fruit(RandomFruit.position, RandomFruit.type);
                RandomFruit.disabled = true;
            }

            handle_collisions();

            detect_fruits_on_endline();

            BeginDrawing();
            ClearBackground(GRAY);
            if (!RandomFruit.disabled)
                DrawCircleV(RandomFruit.position, random_fruit_data.radius, random_fruit_data.color);

            DrawRectangle(START_X, 120, END_X-START_X, 5, RED);             // end line
            DrawRectangle(START_X, 20, 5, 755, BLACK);                      // wall 1
            DrawRectangle(END_X-5, 20, 5, 755, BLACK);                      // wall 2
            DrawRectangle(START_X, 755+START_X, END_X-START_X, 5, BLACK);   // ground

            for (Fruit &f : fruits) {
                f.draw();
            }

            EndDrawing();
        } else {

            if (IsKeyPressed(KEY_ENTER))
                restart_game();
            BeginDrawing();
            ClearBackground(GRAY);
            const char* text = "Game Over!";
            int width = MeasureText(text, 50);
            DrawText(text, GetScreenWidth()/2-width/2, 250, 50, RED);

            text = "ENTER to restart";
            width = MeasureText(text, 40);
            DrawText("ENTER to restart", GetScreenWidth()/2-width/2, 500, 40, RED);
            EndDrawing();
        }
    }

    b2DestroyWorld(world_id);
    CloseWindow();
    return 0;
}
