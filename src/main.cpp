#include <algorithm>
#include <box2d/math_functions.h>
#include <raylib.h>
#include <box2d/box2d.h>
#include <vector>
#include <iostream>
#include "../include/fruit.h"
#include "../include/spawner.h"


int main() {
    InitWindow(600, 800, "arbuz-arbuz");
    Orange::load_texture();
    Peach::load_texture();
    Apple::load_texture();
    Blackberry::load_texture();
    Lime::load_texture();
    Lemon::load_texture();
    Plum::load_texture();
    Strawberry::load_texture();
    Coconut::load_texture();
    Starfruit::load_texture();
    Watermelon::load_texture();

    bool end = false;
    struct fruit_on_line{
        Fruit fruit;
        int frames;  
    };
    std::vector<fruit_on_line> dead_fruits;

    // world
    b2WorldDef world_def = b2DefaultWorldDef();
    float lenght_unit_per_meter = 128.0f;
    world_def.gravity = (b2Vec2){ 0.0f, 9.81f*lenght_unit_per_meter };
    b2WorldId world_id = b2CreateWorld(&world_def);
    b2SetLengthUnitsPerMeter(lenght_unit_per_meter);
    // ground
    b2BodyDef ground_body_def = b2DefaultBodyDef();
    ground_body_def.position = (b2Vec2){ 300.0f, 700.0f };
    b2BodyId ground_id  = b2CreateBody(world_id, &ground_body_def);
    b2Polygon ground_box = b2MakeBox(290.0f, 5.0f);
    b2ShapeDef ground_shape_def = b2DefaultShapeDef();
    b2CreatePolygonShape(ground_id, &ground_shape_def, &ground_box);
    // wall 1
    b2BodyDef wall1_body_def = b2DefaultBodyDef();
    wall1_body_def.position = (b2Vec2){ 12.0f, 350.0f };
    b2BodyId wall1_body_id = b2CreateBody(world_id, &wall1_body_def);
    b2Polygon wall1_box = b2MakeBox(2.0f, 350.0f);
    b2ShapeDef wall1_shape_def = b2DefaultShapeDef();
    b2CreatePolygonShape(wall1_body_id, &wall1_shape_def, &wall1_box);
    // wall 2
    b2BodyDef wall2_body_def = b2DefaultBodyDef();
    wall2_body_def.position = (b2Vec2){ 600.0f-12.0f, 350.0f };
    b2BodyId wall2_body_id = b2CreateBody(world_id, &wall2_body_def);
    b2Polygon wall2_box = b2MakeBox(2.0f, 350.0f);
    b2ShapeDef wall2_shape_def = b2DefaultShapeDef();
    b2CreatePolygonShape(wall2_body_id, &wall2_shape_def, &wall2_box);

    random_fruit();
    SetTargetFPS(60);

    Rectangle end_line = {10, 150, 576, 5};
    while (!WindowShouldClose()) {
        b2World_Step(world_id, 1.0f/60.0f, 4);
        spawn(world_id);
        collision_detection(world_id);

        if (!dead_fruits.empty()){
            std::vector<fruit_on_line> to_destroy;
            for (auto &i : dead_fruits){
                if (i.frames <= 180 ) i.frames++;
                else{
                    if (b2Body_IsValid(i.fruit.body_id)){
                        Rectangle rec = {i.fruit.get_position().x-i.fruit.radius, i.fruit.get_position().y-i.fruit.radius, i.fruit.radius*2, i.fruit.radius*2};
                        if (CheckCollisionRecs(rec, end_line)){
                            i.frames=0;
                            end = true;
                        }else {
                            to_destroy.push_back(i);
                        }
                    }
                }                
            }
            if (!to_destroy.empty()){
                for (auto &it : to_destroy){
                    dead_fruits.erase(std::remove_if(dead_fruits.begin(), dead_fruits.end(), [&it](const fruit_on_line &f){
                        return f.fruit.body_id.index1 == it.fruit.body_id.index1;
                    }));
                }
            }
        }

        BeginDrawing();
            ClearBackground((Color){255,255,143,255});
            if (!end){
                DrawRectangleRec(end_line, RED);
                spawner_draw();
                if (!fruits.empty()) {
                    for (Fruit &fruit : fruits){
                        fruit.draw();
                        Rectangle rec = {fruit.get_position().x-fruit.radius, fruit.get_position().y-fruit.radius, fruit.radius*2, fruit.radius*2};
                        //DrawRectangleRec(rec, GREEN);
                        if (CheckCollisionRecs(rec, end_line)) dead_fruits.push_back({fruit, 0});    
                    }
                }
                DrawRectangle(12-2, 0, 4, 700, DARKGRAY); // wall 1
                DrawRectangle(600-12-2, 0, 4, 700, DARKGRAY); // wall 2
                DrawRectangle(300-290, 700-5, 580, 10, DARKGRAY); // ground
            } else {
                DrawText("Game Over", 150, 250, 50, RED);               
            }
        EndDrawing();
    }

    b2DestroyWorld(world_id);
    Orange::unload_texture();
    Peach::unload_texture();
    Apple::unload_texture();
    Blackberry::unload_texture();
    Lime::unload_texture();
    Lemon::unload_texture();
    Plum::unload_texture();
    Strawberry::unload_texture();
    Coconut::unload_texture();
    Starfruit::unload_texture();
    Watermelon::unload_texture();
    CloseWindow();
    return 0;
}
