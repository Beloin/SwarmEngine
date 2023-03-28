#include <stdio.h>
#include "physicsContext.h"
#include "glad.h"
#include "vector2.h"
#include "gl_particle_adapter.h"
#include "particle.h"
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdlib.h>

#define HEIGHT 800
#define WIDTH 800

char fps;
float offset = 0.1f;
struct timespec start, end;
clock_t start_, step_; // start and step are in seconds.

PhysicsContext context = (PhysicsContext) {0, S};

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
}


GLFWwindow *setup();

GLuint genShaderProgram01();

void doSimulate();

void checkSimulation(double seconds);

Particle particle;


int main() {
    GLFWwindow *window = setup();
    gladLoadGL();
    glViewport(0, 0, HEIGHT, WIDTH);
    glClearColor(0.07f, 0.13f, 0.17f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    step_ = start_ = clock();
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    float vectorVertex[9];

    // Reference containers for the Vertex Array and the Vertex Buffer
    // VAO = Vertex Array Object
    // VBO = Vertex Buffer Object
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind and configure buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vectorVertex), vectorVertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);

    Vector2 position = CreateVector(200, 400);
    Vector2 velocity = CreateVector(0, 0);
    particle = (Particle) {position, velocity, 1};

    GLuint shaderProgram01 = genShaderProgram01();
    while (!glfwWindowShouldClose(window)) {
        fps++;

        step_ = clock();
        double currentTime = (double) step_ / CLOCKS_PER_SEC;

        context.dt = currentTime;

        double seconds = (double) (step_ - start_) / CLOCKS_PER_SEC;

        if (seconds >= 1) {
            printf("FPS: %d\n", fps);
            start_ = clock();
            fps = 0;
        }

        checkSimulation(seconds);

        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(0);

        glUseProgram(shaderProgram01);

        TriangleVector2 tv2 = CreateTriangle(&particle.position, HEIGHT, WIDTH);
        GenerateFloatArray(&tv2, vectorVertex);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Update buffer data.
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vectorVertex), vectorVertex);

        glfwSwapBuffers(window);
        glfwPollEvents();

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    }

    return 0;
}

void checkSimulation(double seconds) {
    if (context.resolution == S) {
        if (seconds + offset >= 1) {
            doSimulate();
        }
    } else if (context.resolution == MS_500) {
        if (seconds >= 0.5) {
            doSimulate();
        }
    } else if (context.resolution == MS_100) {
        if (seconds >= 0.1) {
            doSimulate();
        }
    }
}

GLFWwindow *setup() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    GLFWwindow *window = glfwCreateWindow(HEIGHT, WIDTH, "OpenGL", NULL, NULL);
    if (window == NULL) {
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    return window;
}

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
//Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                   "}\n\0";

GLuint genShaderProgram01() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void doSimulate() {
    Vector2 acceleration = ComputeGravityForce(&particle);
    CalculateNewPositionAndVelocity(&particle, &acceleration, &context);
}