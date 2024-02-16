#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

int windowWidth = 640;
int windowHeight = 480;

const GLuint WIDTH = 800, HEIGHT = 600;
double lastTime;
int nbFrames;

void showFPS(GLFWwindow *pWindow)
{
    // Measure speed
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    nbFrames++;
    if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
        std::cout << 1000.0/double(nbFrames) << std::endl;
        double fps = double(nbFrames) / delta;
        const char* ss = std::to_string((int)fps).c_str();
        glfwSetWindowTitle(pWindow, ss);
        nbFrames = 0;
        lastTime = currentTime;
    }
}

void glWindowSizeCallback(GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, windowWidth, windowHeight);
}

void glKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main()
{
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "PTP", NULL, NULL);
    if (!window) {
        std::cout << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glWindowSizeCallback);
    glfwSetKeyCallback(window, glKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "LOAD GLAD FAILED" << std::endl;
        return -1;
    }
    std::cout << "Renderer " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        showFPS(window);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}