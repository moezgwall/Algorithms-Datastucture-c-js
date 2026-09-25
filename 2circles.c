#include "reOpengl.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>
#define CIRCLE_SEGMENTS 64
#define MAX_PLAYERS 22

typedef struct {
  Vec3f position;
  float radius;
  Vec3f color;
  int selected;
} Player;
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    printf("Escape key pressed — setting window should close\n");
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  } else {
    printf("Key pressed: %d\n", key);
  }
}

Player players[MAX_PLAYERS];
int selectedPlayer = -1;

const char *vertexShaderSrc = "#version 330 core\n"
                              "layout(location = 0) in vec3 aPos;\n"
                              "uniform mat4 uMVP;\n"
                              "void main() {\n"
                              "   gl_Position = uMVP * vec4(aPos, 1.0);\n"
                              "}\n";

const char *fragmentShaderSrc = "#version 330 core\n"
                                "out vec4 FragColor;\n"
                                "uniform vec3 uColor;\n"
                                "void main() {\n"
                                "   FragColor = vec4(uColor, 1.0);\n"
                                "}\n";

// Generate a 2D circle's vertices
static void generateCircleVertices(Vec3f *vertices, int segments,
                                   float radius) {
  vertices[0] = (Vec3f){0.0f, 0.0f, 0.0f}; // center
  for (int i = 0; i <= segments; ++i) {
    float angle = 2.0f * M_PI * i / segments;
    vertices[i + 1] = (Vec3f){cosf(angle) * radius, sinf(angle) * radius, 0.0f};
  }
}

void initPlayers() {
  printf("Initializing players...\n");
  for (int i = 0; i < MAX_PLAYERS; ++i) {
    players[i].position =
        (Vec3f){(i % 11 - 5) * 0.4f, (i < 11) ? -1.0f : 1.0f, 0.0f};
    players[i].radius = 0.15f;
    players[i].color =
        (i < 11) ? (Vec3f){1.0f, 0.0f, 0.0f} : (Vec3f){0.0f, 0.0f, 1.0f};
    players[i].selected = 0;
  }
  printf("Players initialized.\n");
}

Vec3f screenToWorld(GLFWwindow *window, double xpos, double ypos, Mat4f view,
                    Mat4f projection) {
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  float x = (2.0f * xpos) / width - 1.0f;
  float y = 1.0f - (2.0f * ypos) / height;

  Vec4f ray_clip = {x, y, 0.0f, 1.0f};

  Mat4f invVP = mat4f_inverse(mat4f_mul(projection, view));
  Vec4f world = mat4f_mul_vec4f(invVP, ray_clip);

  return (Vec3f){world.x, world.y, 0.0f};
}

Mat4f g_view;
Mat4f g_projection;
GLFWwindow *g_window;

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    Vec3f clickPos = screenToWorld(window, xpos, ypos, g_view, g_projection);

    printf("Mouse button event: button=%d action=%d at screen(%.1f, %.1f), "
           "world(%.2f, %.2f)\n",
           button, action, xpos, ypos, clickPos.x, clickPos.y);

    if (action == GLFW_PRESS) {
      for (int i = 0; i < MAX_PLAYERS; ++i) {
        float dx = players[i].position.x - clickPos.x;
        float dy = players[i].position.y - clickPos.y;
        if (dx * dx + dy * dy < players[i].radius * players[i].radius) {
          selectedPlayer = i;
          players[i].selected = 1;
          printf("Player %d selected at position (%.2f, %.2f)\n", i,
                 players[i].position.x, players[i].position.y);
          break;
        }
      }
    } else if (action == GLFW_RELEASE) {
      if (selectedPlayer >= 0) {
        printf("Player %d released\n", selectedPlayer);
        players[selectedPlayer].selected = 0;
      }
      selectedPlayer = -1;
    }
  }
}
void error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error [%d]: %s\n", error, description);
}
int main() {
  printf("Starting application...\n");
  glfwSetErrorCallback(error_callback);
  InitGLFW();

  int windowWidth = 1280, windowHeight = 720;
  g_window = CreateWindowContext(windowWidth, windowHeight,
                                 "Tactical Pitch - Drag Players");
  if (!g_window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    return -1;
  }
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version: %s\n", version);
  printf("Window created successfully\n");

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  RegisterFrameBufferSizeCallBack(g_window, FrameBufferSizeCallBack);
  SetViewport(0, 0, windowWidth, windowHeight);
  glfwSetKeyCallback(g_window, key_callback);
  glfwSetMouseButtonCallback(g_window, mouse_button_callback);

  Vec3f circleVertices[CIRCLE_SEGMENTS + 2];
  generateCircleVertices(circleVertices, CIRCLE_SEGMENTS,
                         1.0f); // unit radius, will scale later

  GLuint vao = CreateVertexArrayObject();
  GLuint vbo = CreateVertexBufferObject(circleVertices, sizeof(circleVertices));
  SetupVertexAttrib(0, 3, GL_FLOAT, sizeof(Vec3f), (void *)0);

  GLuint shader = CreateShader(vertexShaderSrc, fragmentShaderSrc);

  Vec3f camPos = {0, 0, 5};
  Vec3f camTarget = {0, 0, 0};
  Vec3f camUp = {0, 1, 0};

  g_projection = Ortho4f(-5.0f, 5.0f, -3.5f, 3.5f, 0.1f, 100.0f);

  initPlayers();

  printf("Entering main loop...\n");

  while (!glfwWindowShouldClose(g_window)) {
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(g_window);
    Sleep(100); // include windows.h for Sleep
  }

  printf("Exiting main loop\n");

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(shader);
  FreeWindow(g_window);

  printf("Application terminated cleanly.\n");
  return 0;
}
