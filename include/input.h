#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "camera.h"

void input_init(GLFWwindow* window);
void input_process(GLFWwindow* window, Camera* camera, float deltaTime);
void input_mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif
