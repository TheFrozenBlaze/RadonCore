#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

GLFWwindow* makeWindow(int display_w, int display_h, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

#endif