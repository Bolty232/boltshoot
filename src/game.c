#include "../include/game.h"
#include "../include/input.h"
#include <stdio.h>

int game_init(Game* game) {
    if (!renderer_init(&game->renderer, 800, 600, "BoltShoot")) {
        printf("Renderer konnte nicht initialisiert werden.\n");
        return 0;
    }
    
    camera_init(&game->camera);
    
    input_init(game->renderer.window);
    
    glfwSetCursorPosCallback(game->renderer.window, input_mouse_callback);
    
    game->cubeMesh = mesh_create_plane();
    game->edgeMesh = mesh_create_plane_edges();
    
    game->deltaTime = 0.0f;
    game->lastFrame = 0.0f;
    
    return 1;
}

void game_run(Game* game) {
    while (!glfwWindowShouldClose(game->renderer.window)) {
        float currentFrame = glfwGetTime();
        game->deltaTime = currentFrame - game->lastFrame;
        game->lastFrame = currentFrame;

        input_process(game->renderer.window, &game->camera, game->deltaTime);
        
        camera_update_physics(&game->camera, game->deltaTime);

        renderer_clear();
        renderer_render(&game->renderer, game->cubeMesh, game->edgeMesh, game->camera);

        glfwSwapBuffers(game->renderer.window);

        glfwPollEvents();
    }
}

void game_destroy(Game* game) {
    mesh_destroy(game->cubeMesh);
    mesh_destroy(game->edgeMesh);
    renderer_destroy(&game->renderer);
}
