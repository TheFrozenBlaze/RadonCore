#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <window.h>

GLFWwindow* makeWindow(int display_w, int display_h, const char* title, GLFWmonitor* monitor, GLFWwindow* share) { 
    GLFWwindow* window = glfwCreateWindow(display_w, display_h, title, monitor, share);
    if (window == nullptr) {
        std::cout << "Failed to open GLFW window" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}