#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

typedef struct {
    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;
} ShaderProgram;

ShaderProgram shader_create(const char* vertexSource, const char* fragmentSource);
void shader_use(ShaderProgram shader);
void shader_set_mat4(ShaderProgram shader, const char* name, glm::mat4 value);
void shader_destroy(ShaderProgram shader);

#endif