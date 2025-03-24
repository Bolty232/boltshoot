#include "../include/mesh.h"
#include <stdlib.h>

Mesh mesh_create(GLfloat* vertices, GLuint* indices, int vertexCount, int indexCount) {
    Mesh mesh;
    mesh.indexCount = indexCount / sizeof(GLuint);
    
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    
    return mesh;
}

void mesh_draw(Mesh mesh, ShaderProgram shader, glm::mat4 mvp) {
    shader_use(shader);
    shader_set_mat4(shader, "mpv", mvp);
    
    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void mesh_draw_edges(Mesh mesh, ShaderProgram shader, glm::mat4 mvp) {
    glLineWidth(2.0f);
    glDisable(GL_DEPTH_TEST);
    
    shader_use(shader);
    shader_set_mat4(shader, "mpv", mvp);
    
    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_LINES, mesh.indexCount, GL_UNSIGNED_INT, 0);
    
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(0);
}

void mesh_destroy(Mesh mesh) {
    glDeleteVertexArrays(1, &mesh.VAO);
    glDeleteBuffers(1, &mesh.VBO);
    glDeleteBuffers(1, &mesh.EBO);
}

Mesh mesh_create_plane() {
    GLfloat vertices[] = {
        -5.0f, 0.0f, -5.0f,
         5.0f, 0.0f, -5.0f,
         5.0f, 0.0f,  5.0f,
        -5.0f, 0.0f,  5.0f,
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0 
    };
    
    return mesh_create(vertices, indices, sizeof(vertices), sizeof(indices));
}

Mesh mesh_create_plane_edges() {
    GLfloat vertices[] = {
        -5.0f, 0.0f, -5.0f,
         5.0f, 0.0f, -5.0f,
         5.0f, 0.0f,  5.0f,
        -5.0f, 0.0f,  5.0f,
    };

    GLuint edgeIndices[] = {
        0, 1,
        1, 2,
        2, 3,
        3, 0
    };
    
    return mesh_create(vertices, edgeIndices, sizeof(vertices), sizeof(edgeIndices));
}
