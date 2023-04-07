#include <stdio.h>
#include "physicsContext.h"
#include "glad.h"
#include "vector2.h"
#include "gl_particle_adapter.h"
#include "particle.h"
#include "simulation/simulation.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

#define HEIGHT 1200
#define WIDTH 1200


char fps;
float offset = 0.1f;
double start_, step_; // start and step are in seconds.

PhysicsContext context = (PhysicsContext) {0};

Vector2 currentXlr8 = (Vector2) {0.0f, 0.0f};

Vector2 xlr8 = (Vector2) {0.1f, 0.0f};
Vector2 friction = (Vector2) {-0.1f, 0.0f};

double reset = 0;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
//    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_RIGHT) {
            reset = step_;
            currentXlr8.x = xlr8.x;
            currentXlr8.y = xlr8.y;
        } else if (key == GLFW_KEY_LEFT) {
            reset = step_;
            currentXlr8.x = friction.x;
            currentXlr8.y = friction.y;
        } else if (key == GLFW_KEY_DOWN) {
            reset = step_;
            currentXlr8.x = 0;
            currentXlr8.y = 0;
        }
    }
}


GLFWwindow *setup();

GLuint genShaderProgram01();

void doSimulate(Particle *p);


Vector2 target = (Vector2) {700, 100};
Ant swarmedAnts[100];
int swarmedAntsLength = 0;

void randomizeTarget();

int main() {
    srand(1);
    GLFWwindow *window = setup();
    gladLoadGL();
    glViewport(0, 0, HEIGHT, WIDTH);
    glClearColor(0.07f, 0.13f, 0.17f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    step_ = start_ = glfwGetTime();

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

//    Vector2 position = CreateVector(200, 400);
//    Vector2 velocity = CreateVector(0, 0);
//    particle = (Particle) {position, velocity, 1};


    InitializeSimulation(0, HEIGHT);
    // Ant 01
    swarmedAnts[swarmedAntsLength] = CreateAnt(300, 400);
    swarmedAntsLength++;

    GLuint shaderProgram01 = genShaderProgram01();

    double currentTime, seconds, ite;
    currentTime = seconds = ite = 0;
    while (!glfwWindowShouldClose(window)) {
        fps++;

        step_ = glfwGetTime();
        currentTime = step_ - reset;
        context.t = currentTime;

        seconds = (double) (step_ - start_);

        if (seconds >= 1) {
            printf("FPS: %d | ", fps);
            printf("Context Time: %.2f\n", context.t);
            start_ = glfwGetTime();
            fps = 0;

            ite++;
        }

        if (ite >= 2) {
            randomizeTarget();
            ite = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(0);

        glUseProgram(shaderProgram01);

        Ant *ptr = GetSimulationArray();
        for (int i = 0; i < GetSimulationLength(); ++i) {
            Ant *ant = ptr + i;

            ant->bodyCenter.context.t = currentTime;
            doSimulate(&ant->bodyCenter);

            TriangleVector2 tv2 = CreateTriangle(&ant->bodyCenter.position, HEIGHT, WIDTH);
            GenerateFloatArray(&tv2, vectorVertex);

            // Draw Target
            glDrawArrays(GL_TRIANGLES, 0, 3);
            // Update buffer data.
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vectorVertex), vectorVertex);
        }

        for (int i = 0; i < swarmedAntsLength; ++i) {
            Ant *ant = &swarmedAnts[i];
            ant->bodyCenter.context.t = currentTime;

            SimulateAnt(ant, ptr, GetSimulationLength());

            TriangleVector2 tv2 = CreateTriangle(&ant->bodyCenter.position, HEIGHT, WIDTH);
            GenerateFloatArray(&tv2, vectorVertex);

            // Draw Target
            glDrawArrays(GL_TRIANGLES, 0, 3);
            // Update buffer data.
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vectorVertex), vectorVertex);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
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

void doSimulate(Particle *p) {
//    Vector2 accToTarget = GetAccelerationToTarget(p, &target);
//    CalculateNewPositionAndVelocity(p, &accToTarget);

//    if (p->position.x > WIDTH + 50) {
//        p->position.x = 0;
//        p->context.reset = p->context.t - 1;
//    }

    if (p->position.y > HEIGHT + 50) {
        p->position.y = 0;
        p->context.reset = p->context.t - 1;
    }

    CalculateNewPosition(p);

}

void randomizeTarget() {
    unsigned int x = (unsigned int) random();
    unsigned int y = (unsigned int) random();
    x = x % (WIDTH - 200);
    y = y % (HEIGHT - 200);

    target = (Vector2) {(float) x, (float) y};
}