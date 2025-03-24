#include "../include/input.h"
#include <glm/glm.hpp>
#include <stdio.h>      

static Camera* g_camera = NULL;
static bool firstMouse = true;
static double lastX = 400.0;
static double lastY = 300.0;

void input_init(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, width / 2, height / 2);
    
    lastX = width / 2;
    lastY = height / 2;
}

void input_process(GLFWwindow* window, Camera* camera, float deltaTime) {
    g_camera = camera;
    
    float velocity = camera->speed * deltaTime * 60.0f;
    glm::vec3 oldPosition = camera->position;
    glm::vec3 movement(0.0f);
    
    glm::vec3 forward = camera->front;
    forward.y = 0.0f;
    forward = glm::normalize(forward);
    
    glm::vec3 right = glm::normalize(glm::cross(forward, camera->up));
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movement += forward * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movement -= forward * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movement -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movement += right * velocity;
    
    camera->position.x += movement.x;
    camera->position.z += movement.z;
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera_jump(camera);
    
    camera_update_physics(camera, deltaTime);
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void input_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (g_camera == NULL) return;
    
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera_process_mouse(g_camera, xoffset, yoffset);
}
