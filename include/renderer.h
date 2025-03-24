#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "mesh.h"
#include "shader.h"

typedef struct {
    GLFWwindow* window;
    int width;
    int height;
    ShaderProgram objectShader;
    ShaderProgram edgeShader;
} Renderer;

int renderer_init(Renderer* renderer, int width, int height, const char* title);
void renderer_clear();
void renderer_render(Renderer* renderer, Mesh cubeMesh, Mesh edgeMesh, Camera camera);
void renderer_destroy(Renderer* renderer);

#endif
