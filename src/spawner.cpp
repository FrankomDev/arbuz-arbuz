//
// Created by frankom on 23.08.25.
//

#include "fruit.h"
#include <raylib.h>
#include "spawner.h"
#include <list>
#include <vector>
#include <box2d/box2d.h>

Texture2D spawner_texture;
float spawner_radius;
int type;
Vector2 mouse;
std::list<Fruit> fruits;
bool clicked = false;
int click_frames = 0;
struct pending {
    b2Vec2 pos;
    float radius;
    Texture2D texture;
};
std::vector<pending> pfruits;

void random_fruit() {
    const int num = GetRandomValue(1,4);
    if (num == type) {
        random_fruit();
    }else {
        type = num;
        switch (num) {
            case 1:
                spawner_texture = Orange::texture;
                spawner_radius = Orange::radius;
                break;
            case 2:
                spawner_texture = Peach::texture;
                spawner_radius = Peach::radius;
                break;
            case 3:
                spawner_texture = Apple::texture;
                spawner_radius = Apple::radius;
                break;
            case 4:
                spawner_texture = Blackberry::texture;
                spawner_radius = Blackberry::radius;
                break;
        }
    }
}

void spawner_draw() {
    if (!clicked) {
        mouse = GetMousePosition();
        if (mouse.x < 60) mouse.x = 60;
        if (mouse.x > 540) mouse.x = 540;

        Rectangle src = {0,0,(float)spawner_texture.width,(float)spawner_texture.height};
        Rectangle dst = {mouse.x, 28.0f, spawner_radius*2, spawner_radius*2};
        DrawTexturePro(spawner_texture, src, dst, {spawner_radius,spawner_radius}, 0.0f, WHITE);
    }
}

void spawn(b2WorldId world_id) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !clicked) {
        //Fruit fruit = Fruit(world_id, (b2Vec2){mouse.x, 5.0f}, spawner_radius, spawner_texture);
        //fruits.push_back(fruit);
        fruits.emplace_back(world_id, (b2Vec2){mouse.x, 5.0f}, spawner_radius, spawner_texture);
        //pfruits.push_back({(b2Vec2){mouse.x, 5.0f}, spawner_radius, spawner_texture});
        clicked = true;
        random_fruit();
    }else if (clicked) {
        click_frames++;
        if (click_frames >= 40) {
            click_frames = 0;
            clicked = false;
        }
    }

}

void change_fruit(float radius, b2Vec2 pos) {
    switch ((int) radius) {
        case 24:
            //change to peach
            //pfruits.emplace_back(world_id, pos, Peach::radius, Peach::texture);
            pfruits.push_back({pos, Peach::radius, Peach::texture});
            break;
        case 30:
            //change to apple
            //pfruits.emplace_back(world_id, pos, Apple::radius, Apple::texture);
            pfruits.push_back({pos, Apple::radius, Apple::texture});
            break;
        case 36:
            //change to blackberry
            //pfruits.emplace_back(world_id, pos, Blackberry::radius, Blackberry::texture);
            pfruits.push_back({pos, Blackberry::radius, Blackberry::texture});
            break;
        case 42:
            //change to lime
            //pfruits.emplace_back(world_id, pos, Lime::radius, Lime::texture);
            pfruits.push_back({pos, Lime::radius, Lime::texture});
            break;
        case 48:
            //change to lemon
            //pfruits.emplace_back(world_id, pos, Lemon::radius, Lemon::texture);
            pfruits.push_back({pos, Lemon::radius, Lemon::texture});
            break;
        case 54:
            //change to plum
            //pfruits.emplace_back(world_id, pos, Plum::radius, Plum::texture);
            pfruits.push_back({pos, Plum::radius, Plum::texture});
            break;
        case 60:
            //change to strawberry
            //pfruits.emplace_back(world_id, pos, Strawberry::radius, Strawberry::texture);
            pfruits.push_back({pos, Strawberry::radius, Strawberry::texture});
            break;
        case 66:
            //change to coconut
            //pfruits.emplace_back(world_id, pos, Coconut::radius, Coconut::texture);
            pfruits.push_back({pos, Coconut::radius, Coconut::texture});
            break;
        case 72:
            //change to starfruit
            //pfruits.emplace_back(world_id, pos, Starfruit::radius, Starfruit::texture);
            pfruits.push_back({pos, Starfruit::radius, Starfruit::texture});
            break;
        case 78:
            //change to watermelon
            //pfruits.emplace_back(world_id, pos, Watermelon::radius, Watermelon::texture);
            pfruits.push_back({pos, Watermelon::radius, Watermelon::texture});
            break;
    }
}

/*void check_if_equal(std::vector<Fruit*> fruits_l, b2WorldId world_id) {
    if (fruits_l[0]->radius == fruits_l[1]->radius) {
        float get_radius = fruits_l[1]->radius;
        b2Vec2 get_pos = fruits_l[1]->get_position();
        // [0] ten co spada [1] ten na dole wiec go zmieniac
        auto i = fruits.begin();
        for (Fruit &fruit : fruits) {
            if (fruit.body_id.index1 == fruits_l[1]->body_id.index1) {
                if (b2Body_IsValid(fruits_l[1]->body_id)) {
                    b2DestroyBody(fruits_l[1]->body_id);
                    fruits.erase(i);
                }
                ++i;
            }else if (fruit.body_id.index1 == fruits_l[0]->body_id.index1) {
                if (b2Body_IsValid(fruits_l[0]->body_id)) {
                    b2DestroyBody(fruits_l[0]->body_id);
                    fruits.erase(i);
                }
                ++i;
            }else ++i;
        }
       change_fruit(get_radius, get_pos, world_id);
    }
}*/


void collision_detection(b2WorldId world_id) {
    b2ContactEvents contacts = b2World_GetContactEvents(world_id);
    //std::cout << "hit: " << contacts.hitCount << " begin: " << contacts.beginCount << " end: " << contacts.endCount << std::endl;
    if (!fruits.empty()) {
        std::vector<Fruit*> fruits_vec;
        for (int i =0; i < contacts.hitCount; i++ ) {
            b2ContactHitEvent &events = contacts.hitEvents[i];
            b2BodyId bodyA = b2Shape_GetBody(events.shapeIdA);
            b2BodyId bodyB = b2Shape_GetBody(events.shapeIdB);
            if (b2Body_IsValid(bodyA) && b2Body_IsValid(bodyB) &&
                b2Shape_IsValid(events.shapeIdA) && b2Shape_IsValid(events.shapeIdB) &&
                b2Body_GetType(bodyA) == b2_dynamicBody && b2Body_GetType(bodyB) == b2_dynamicBody) {
                for (Fruit& fruit : fruits) {
                    //if (fruit.body_id.index1 == bodyA.index1||fruit.body_id.index1 == bodyB.index1) {
                    if (b2Body_IsValid(fruit.body_id) && b2Shape_IsValid(fruit.shape_id)){
                        if (fruit.shape_id.index1 == events.shapeIdA.index1||fruit.shape_id.index1 == events.shapeIdB.index1) {
                            fruits_vec.push_back(&fruit);
                            if (fruits_vec.size()==2) {
                                //check_if_equal(fruits_vec, world_id);
                                if (fruits_vec[1]->radius == fruits_vec[0]->radius) {
                                    b2Vec2 get_pos = fruits_vec[1]->get_position();
                                    float get_radius = fruits_vec[1]->radius;
                                    b2DestroyBody(fruits_vec[1]->body_id);
                                    b2DestroyBody(fruits_vec[0]->body_id);
                                    fruits.remove_if([&](const Fruit& f) {
                                        return &f == fruits_vec[1];
                                    });
                                    fruits.remove_if([&](const Fruit& f) {
                                        return &f == fruits_vec[0];
                                    });
                                    change_fruit(get_radius, get_pos);
                                }
                                fruits_vec.clear();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if (!pfruits.empty()) {
        for (auto& fruit : pfruits) {
            fruits.emplace_back(world_id, fruit.pos, fruit.radius, fruit.texture);
        }
        pfruits.clear();
    }
}