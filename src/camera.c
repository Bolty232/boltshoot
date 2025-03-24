#include "../include/camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

void camera_init(Camera* camera) {
    camera->position = glm::vec3(0.0f, 1.8f, 10.0f);
    camera->front = glm::vec3(0.0f, 0.0f, -1.0f);     
    camera->up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    camera->speed = 0.1f;
    camera->sensitivity = 0.1f;
    camera->yaw = -90.0f;
    camera->pitch = 0.0f;                            
    camera->height = 1.8f;                           
    camera->isJumping = false;
    camera->jumpForce = 0.1f;
    camera->gravity = 0.002f;
    
    camera_update_vectors(camera);
}

void camera_update_vectors(Camera* camera) {
    glm::vec3 front;
    front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    front.y = sin(glm::radians(camera->pitch));
    front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    camera->front = glm::normalize(front);
}

void camera_process_mouse(Camera* camera, double xoffset, double yoffset) {
    xoffset *= camera->sensitivity;
    yoffset *= camera->sensitivity;

    camera->yaw += xoffset;
    camera->pitch += yoffset;

    if (camera->pitch > 89.0f)
        camera->pitch = 89.0f;
    if (camera->pitch < -89.0f)
        camera->pitch = -89.0f;
        
    camera_update_vectors(camera);
}

glm::mat4 camera_get_view_matrix(Camera* camera) {
    return glm::lookAt(camera->position, camera->position + camera->front, camera->up);
}

float get_terrain_height(glm::vec3 position) {
    // TODO: implement after implementing levels. Will be used to determine if the player stands on solid ground.
    return 0.0f;
}

void camera_update_physics(Camera* camera, float deltaTime) {
    if (camera->isJumping || camera->position.y > camera->height + get_terrain_height(camera->position)) {
        camera->velocity.y -= camera->gravity;
        camera->position.y += camera->velocity.y;
        
        float terrainHeight = get_terrain_height(camera->position);
        if (camera->position.y < terrainHeight + camera->height) {
            camera->position.y = terrainHeight + camera->height;
            camera->velocity.y = 0.0f;
            camera->isJumping = false;
        }
    }
}

void camera_jump(Camera* camera) {
    if (!camera->isJumping) {
        camera->velocity.y = camera->jumpForce;
        camera->isJumping = true;
    }
}
