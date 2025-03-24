#include "../include/renderer.h"
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>

int renderer_init(Renderer* renderer, int width, int height, const char* title) {
    renderer->width = width;
    renderer->height = height;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    renderer->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!renderer->window) {
        printf("Could not initialisere GLFW.\n");
        return 0;
    }

    glfwMakeContextCurrent(renderer->window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("Could not initialise GLEW: %s\n", glewGetErrorString(err));
        return 0;
    }
    
    const char* vertexSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 mpv;
        void main()
        {
            gl_Position = mpv * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )glsl";

    const char* fragmentSource = R"glsl(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.55f, 0.27f, 0.07f, 1.0f); // Braun
        }
    )glsl";

    const char* fragmentEdgeSource = R"glsl(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f); // Schwarz
        }
    )glsl";

    renderer->objectShader = shader_create(vertexSource, fragmentSource);
    renderer->edgeShader = shader_create(vertexSource, fragmentEdgeSource);
    
    glEnable(GL_DEPTH_TEST);
    
    return 1;
}

void renderer_clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_render(Renderer* renderer, Mesh cubeMesh, Mesh edgeMesh, Camera camera) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera_get_view_matrix(&camera);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                          (float)renderer->width / (float)renderer->height, 
                                          0.1f, 100.0f);

    glm::mat4 mvp = projection * view * model;

    //TODO: implement levels. Flat plane for testing right now
    mesh_draw(cubeMesh, renderer->objectShader, mvp);

    mesh_draw_edges(edgeMesh, renderer->edgeShader, mvp);
}

void renderer_destroy(Renderer* renderer) {
    shader_destroy(renderer->objectShader);
    shader_destroy(renderer->edgeShader);
    glfwDestroyWindow(renderer->window);
}
