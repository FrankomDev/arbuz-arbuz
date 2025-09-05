//
// Created by frankom on 23.08.25.
//

#ifndef SPAWNER_H
#define SPAWNER_H
#include <box2d/box2d.h>
#include <list>
#include "../include/fruit.h"

//extern Texture2D spawner_texture;
//extern float spawner_radius;
extern std::list<Fruit> fruits;

void random_fruit();
void spawner_draw();
void spawn(b2WorldId world_id);
void collision_detection(b2WorldId world_id);

#endif //SPAWNER_H
