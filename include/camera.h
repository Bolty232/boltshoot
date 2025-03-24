#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

typedef struct {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 velocity;     // for jumping
    float speed;
    float sensitivity;
    float yaw;
    float pitch;
    float height;           // height above ground aka player-height
    bool isJumping;
    float jumpForce;
    float gravity;
} Camera;

void camera_init(Camera* camera);
void camera_update_vectors(Camera* camera);
void camera_process_mouse(Camera* camera, double xoffset, double yoffset);
glm::mat4 camera_get_view_matrix(Camera* camera);
void camera_update_physics(Camera* camera, float deltaTime);
void camera_jump(Camera* camera);
float get_terrain_height(glm::vec3 position);

#endif
