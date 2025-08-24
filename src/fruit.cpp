//
// Created by frankom on 22.08.25.
//

#include "fruit.h"
#include <box2d/box2d.h>

Fruit::Fruit(b2WorldId world_id, b2Vec2 position, float radius, Texture2D texture):
body_def(b2DefaultBodyDef()),
texture(),
body_id(),
circle({{0, 0}, radius}),
shape_def(b2DefaultShapeDef()),
shape_id()
{
    this->texture = texture;
    this->radius = radius;
    //body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.position = position;
    body_id = b2CreateBody(world_id, &body_def);
    //circle = {{0,0}, radius};
    //shape_def = b2DefaultShapeDef();
    shape_id = b2CreateCircleShape(body_id, &shape_def, &circle);
    shape_def.enableContactEvents = true;
    shape_def.enableHitEvents = true;
    b2Shape_EnableContactEvents(shape_id, true);
    b2Shape_EnableHitEvents(shape_id, true);

}

Texture2D Orange::texture;
float Orange::radius = 24.0f;
void Orange::load_texture() {
    texture = LoadTexture("../assets/orange.png");
}
void Orange::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Peach::texture;
float Peach::radius = 30.0f;
void Peach::load_texture() {
    texture = LoadTexture("../assets/peach.png");
}
void Peach::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Apple::texture;
float Apple::radius = 36.0f;
void Apple::load_texture() {
    texture = LoadTexture("../assets/red-apple.png");
}
void Apple::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Blackberry::texture;
float Blackberry::radius = 42.0f;
void Blackberry::load_texture() {
    texture = LoadTexture("../assets/black-berry-dark.png");
}
void Blackberry::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Lime::texture;
float Lime::radius = 48.0f;
void Lime::load_texture() {
    texture = LoadTexture("../assets/lime.png");
}
void Lime::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Lemon::texture;
float Lemon::radius = 54.0f;
void Lemon::load_texture() {
    texture = LoadTexture("../assets/lemon.png");
}
void Lemon::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Plum::texture;
float Plum::radius = 60.0f;
void Plum::load_texture() {
    texture = LoadTexture("../assets/plum.png");
}
void Plum::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Strawberry::texture;
float Strawberry::radius = 66.0f;
void Strawberry::load_texture() {
    texture = LoadTexture("../assets/strawberry.png");
}
void Strawberry::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Coconut::texture;
float Coconut::radius = 72.0f;
void Coconut::load_texture() {
    texture = LoadTexture("../assets/coconut.png");
}
void Coconut::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Starfruit::texture;
float Starfruit::radius = 78.0f;
void Starfruit::load_texture() {
    texture = LoadTexture("../assets/star-fruit.png");
}
void Starfruit::unload_texture() {
    UnloadTexture(texture);
}

Texture2D Watermelon::texture;
float Watermelon::radius = 84.0f;
void Watermelon::load_texture() {
    texture = LoadTexture("../assets/watermelon.png");
}
void Watermelon::unload_texture() {
    UnloadTexture(texture);
}
