#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "../include/game.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialise SDL. Exiting...\n");
        return 1;
    }

    if (!glfwInit()) {
        printf("Could not initialise GLFW. Exiting...\n");
        SDL_Quit();
        return 1;
    }

    Game game;
    if (!game_init(&game)) {
        glfwTerminate();
        SDL_Quit();
        return 1;
    }

    game_run(&game);
    game_destroy(&game);

    glfwTerminate();
    SDL_Quit();

    return 0;
}
