#include "fruit.h"
#include <box2d/box2d.h>
#include <box2d/id.h>
#include <box2d/math_functions.h>
#include <cstdio>
#include <raylib.h>
#include <vector>

void detect_fruits_on_endline() {
    struct on_line {
        b2BodyId body_id;
        float radius;
        float time = 0;
    };
    static std::vector<on_line> fruits_on_line;
    static Rectangle line = {START_X, 120, END_X-START_X, 5};

    for (Fruit &f : fruits) {
        b2Vec2 position = b2Body_GetPosition(f.body_id);
        float radius = fruit_db[f.type].radius;
        if (CheckCollisionCircleRec({position.x, position.y}, radius, line)) {
            fruits_on_line.push_back({f.body_id, radius});
        }
    }

    std::vector<int> to_delete;

    for (on_line &f : fruits_on_line) {
        if (!b2Body_IsValid(f.body_id)) {
            to_delete.push_back(f.body_id.index1);
            continue;
        }

        f.time += GetFrameTime();
        b2Vec2 position = b2Body_GetPosition(f.body_id);
        if (!CheckCollisionCircleRec({position.x, position.y}, f.radius, line)) {
            to_delete.push_back(f.body_id.index1);
            continue;
        }

        if (f.time >= 5.5f) {
            printf("end\n");
        }
    }

    //printf("%d \n", (int)fruits_on_line.size());
    for (int &j : to_delete) {
        for (int i=0; i<fruits_on_line.size(); i++) {
            if (j == fruits_on_line[i].body_id.index1) {
                fruits_on_line.erase(fruits_on_line.begin()+i);
                break;
            }
        }
    }
}
