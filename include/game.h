#ifndef GAME_H
#define GAME_H

#include "renderer.h"
#include "camera.h"
#include "mesh.h"

typedef struct {
    Renderer renderer;
    Camera camera;
    Mesh cubeMesh;
    Mesh edgeMesh;
    float deltaTime;
    float lastFrame;
} Game;

int game_init(Game* game);
void game_run(Game* game);
void game_destroy(Game* game);

#endif
