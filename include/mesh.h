#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "shader.h"

typedef struct {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int indexCount;
} Mesh;

Mesh mesh_create(GLfloat* vertices, GLuint* indices, int vertexCount, int indexCount);
void mesh_draw(Mesh mesh, ShaderProgram shader, glm::mat4 mvp);
void mesh_draw_edges(Mesh mesh, ShaderProgram shader, glm::mat4 mvp);
void mesh_destroy(Mesh mesh);

Mesh mesh_create_plane();
Mesh mesh_create_plane_edges();

#endif
