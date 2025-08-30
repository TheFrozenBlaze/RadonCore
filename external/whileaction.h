#ifndef WHILEACTION_H
#define WHILEACTION_H
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <shaperenderer.h>
#include <string>
#include <vector>
#include <memory>
#include <tinyfiledialogs.h>
#include <cstring> 
#include <fstream>

void whileAction(GLFWwindow* window, int& display_w, int& display_h, 
                 std::vector<char>& textBuffer, 
                 std::string& currentFilePath, 
                 bool& modified);

#endif