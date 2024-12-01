#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "glad/glad.h"
#include <glfw3.h>
#include <glfw3native.h>

int make_shader(char* shader_path, int type, int program) {
    FILE* file = fopen(shader_path, "r");
    char* buf = malloc(4096);
    fread(buf, 1, 4096, file);
    
    int shader = glCreateShader(type); 
    glShaderSource(shader, 1, (char const**) &buf, 0);
    glCompileShader(shader);
    glAttachShader(program, shader);

    return shader;
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL Example", 0, 0);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    float verts[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    }; 

    int vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
        
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    int program = glCreateProgram();
    int vert_shader = make_shader("vert.glsl", GL_VERTEX_SHADER, program);
    int frag_shader = make_shader("frag.glsl", GL_FRAGMENT_SHADER, program);
    glLinkProgram(program);
    glUseProgram(program);

    glClearColor(0, 0, 0, 0);
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}













