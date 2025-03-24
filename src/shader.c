#include "../include/shader.h"
#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram shader_create(const char* vertexSource, const char* fragmentSource) {
    ShaderProgram shader;
    
    shader.vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader.vertexShader, 1, &vertexSource, NULL);
    glCompileShader(shader.vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(shader.vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader.vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }
    
    shader.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader.fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(shader.fragmentShader);
    
    glGetShaderiv(shader.fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader.fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }
    
    shader.program = glCreateProgram();
    glAttachShader(shader.program, shader.vertexShader);
    glAttachShader(shader.program, shader.fragmentShader);
    glLinkProgram(shader.program);
    
    glGetProgramiv(shader.program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader.program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    
    return shader;
}

void shader_use(ShaderProgram shader) {
    glUseProgram(shader.program);
}

void shader_set_mat4(ShaderProgram shader, const char* name, glm::mat4 value) {
    GLuint location = glGetUniformLocation(shader.program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void shader_destroy(ShaderProgram shader) {
    glDeleteShader(shader.vertexShader);
    glDeleteShader(shader.fragmentShader);
    glDeleteProgram(shader.program);
}
