#pragma once

#include <box2d/id.h>
#include <raylib.h>
#include <unordered_map>
#include <vector>

#define START_X 20
#define END_X 600 - START_X
extern b2WorldId world_id;

inline bool end = false;

typedef enum { Apple, Blueberry, Lemon, Grape, Orange, GreenApple, Peach, Coconut, DragonFruit, Pineapple, Watermelon } FruitType;

struct Fruit {
    FruitType type;
    b2BodyId body_id;

    void draw();
};
extern std::vector<Fruit> fruits;


struct FruitTemplate {
    int radius;
    Color color;
    FruitType next;
};
extern std::unordered_map<FruitType, FruitTemplate> fruit_db;
void init_fruits();


FruitType select_random_fruit();
void spawn_fruit(Vector2 position, FruitType type);

void handle_collisions();


void detect_fruits_on_endline();
void restart_game();
