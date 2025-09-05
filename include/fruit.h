//
// Created by frankom on 22.08.25.
//

#ifndef FRUIT_H
#define FRUIT_H
#include <box2d/box2d.h>
#include <raylib.h>

class Fruit {
public:
    b2BodyDef body_def;
    Texture2D texture;
    b2BodyId body_id;
    b2Circle circle;
    b2ShapeDef shape_def;
    b2ShapeId shape_id;
    float radius;
    void draw() {
        Rectangle src = {0,0,(float)texture.width,(float)texture.height};
        Rectangle dst = {get_position().x, get_position().y, radius*2, radius*2};
        DrawTexturePro(texture, src, dst, {radius,radius}, get_angle(), WHITE);
    }
    b2Vec2 get_position() {
        if (b2Body_IsValid(body_id)) return b2Body_GetPosition(body_id);
        return {0,0};
    }
    float get_angle() {
        if (b2Body_IsValid(body_id)) return RAD2DEG * b2Rot_GetAngle(b2Body_GetRotation(body_id));
        return 0.0f;        
    }
    Fruit(b2WorldId world_id, b2Vec2 position, float radius, Texture2D texture);
};

struct Orange {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Peach {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Apple {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Blackberry {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Lime {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Lemon {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Plum {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Strawberry {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Coconut {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Starfruit {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

struct Watermelon {
    static Texture2D texture;
    static float radius;
    static void load_texture();
    static void unload_texture();
};

#endif //FRUIT_H
