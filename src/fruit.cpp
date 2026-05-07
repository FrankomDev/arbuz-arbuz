#include "fruit.h"
#include <box2d/box2d.h>
#include <box2d/id.h>
#include <box2d/math_functions.h>
#include <box2d/types.h>
#include <raylib.h>
#include <string>
#include <vector>

std::unordered_map<FruitType, FruitTemplate> fruit_db;
std::vector<Fruit> fruits;

void init_fruits() {
    fruit_db[Apple]       = {10, RED, Blueberry};
    fruit_db[Blueberry]   = {20, BLUE, Lemon};
    fruit_db[Lemon]       = {30, YELLOW, Grape};
    fruit_db[Grape]       = {40, PURPLE, Orange};
    fruit_db[Orange]      = {50, ORANGE, GreenApple};
    fruit_db[GreenApple]  = {60, GREEN, Peach};
    fruit_db[Peach]       = {70, PINK, Coconut};
    fruit_db[Coconut]     = {80, BROWN, DragonFruit};
    fruit_db[DragonFruit] = {90, GOLD, Pineapple};
    fruit_db[Pineapple]   = {100, YELLOW, Watermelon};
    fruit_db[Watermelon]  = {110, DARKGREEN, Watermelon};
}

void Fruit::draw() {
    b2Vec2 position = b2Body_GetPosition(this->body_id);
    FruitTemplate fruit_data = fruit_db[this->type];
    DrawCircle(position.x, position.y, fruit_data.radius, fruit_data.color);
    DrawText(std::to_string(this->type).c_str(), position.x, position.y, fruit_data.radius/2, BLACK);
}

FruitType select_random_fruit() {
    return (FruitType)GetRandomValue(0, 2);
}

void spawn_fruit(Vector2 position, FruitType type) {
    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.position = {position.x, position.y};
    b2BodyId body_id = b2CreateBody(world_id, &body_def);
    b2Circle circle = {{0, 0}, (float)fruit_db[type].radius};
    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.enableHitEvents = true;
    shape_def.enableContactEvents = true;
    b2CreateCircleShape(body_id, &shape_def, &circle);

    fruits.push_back({type, body_id});
}

void handle_collisions() {
    b2ContactEvents events = b2World_GetContactEvents(world_id);
    struct new_fruit {
        b2Vec2 position;
        FruitType old_type;
    };
    std::vector<new_fruit> to_create;
    std::vector<b2BodyId> to_destroy;

    for (int i=0; i<events.beginCount; i++) {
        //b2ContactHitEvent &hit = events.hitEvents[i];
        b2ContactBeginTouchEvent &hit = events.beginEvents[i];
        struct body {
            bool found = false;
            FruitType type;
        };
        body body_a;
        body body_b;

        for (Fruit &f : fruits) {
            if (!body_a.found)
                if (b2Shape_GetBody(hit.shapeIdA).index1 == f.body_id.index1) {
                    body_a.type = f.type;
                    body_a.found = true;
                }

            if (!body_b.found)
                if (b2Shape_GetBody(hit.shapeIdB).index1 == f.body_id.index1) {
                    body_b.type = f.type;
                    body_b.found = true;
                }

            if (body_a.found && body_b.found)
                break;
        }
        if (body_a.type == body_b.type && body_a.found && body_b.found) {
            to_destroy.push_back(b2Shape_GetBody(hit.shapeIdA));
            to_destroy.push_back(b2Shape_GetBody(hit.shapeIdB));
            if (body_a.type != Watermelon)
                to_create.push_back({b2Body_GetPosition(b2Shape_GetBody(hit.shapeIdB)), body_a.type});
        }
    }

    for (b2BodyId &b : to_destroy) {
        for (int i=0; i<fruits.size(); i++) {
            if (fruits[i].body_id.index1 == b.index1) {
                fruits.erase(fruits.begin()+i);
                b2DestroyBody(b);
                break;
            }
        }
    }
    to_destroy.clear();

    for (new_fruit &f : to_create) {
        FruitTemplate data = fruit_db[f.old_type];
        spawn_fruit({f.position.x, f.position.y-data.radius/2.0f}, data.next);
    }
    to_create.clear();
}
