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
#include <whileaction.h>
#include <fileutils.h>

extern int InputTextCallback(ImGuiInputTextCallbackData* data);
extern bool LoadFileToBuffer(const char* path, std::vector<char>& buffer);
extern bool SaveBufferToFile(const char* path, const std::vector<char>& buffer);


void whileAction (GLFWwindow* window, int& display_w, int& display_h, 
                 std::vector<char>& textBuffer, 
                 std::string& currentFilePath, 
                 bool& modified) {

    while(!glfwWindowShouldClose(window))
    {
        // background color
        glClearColor(0.180f, 0.164f, 0.278f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // rajzolás OpenGL-lel
        //glUseProgram(shaderProgram);
        //Shaperenderer::drawShape(3);
        // --- ImGui frame indítása ---
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- UI ---
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New")) {}
                if (ImGui::MenuItem("Open...", "Ctrl+O")) {
                    const char* filters[] = { "*.txt", "*.*" };
                    const char* file = tinyfd_openFileDialog("Open File", "", 2, filters, NULL, 0);
                    if (file) {
                        if (LoadFileToBuffer(file, textBuffer)) {
                            currentFilePath = file;
                            modified = false;
                        } else {
                            tinyfd_messageBox("Error", "Cannot open file", "ok", "error", 1);
                        }
                    }
                }
                if (ImGui::MenuItem("Save", "Ctrls+S")) {
                    if (currentFilePath.empty())
                    {
                        const char* save = tinyfd_saveFileDialog("Save File", "untitled.txt", 0, nullptr, nullptr);
                        if (save) currentFilePath = save;
                    }
                    if (!currentFilePath.empty())
                    {
                        if (SaveBufferToFile(currentFilePath.c_str(), textBuffer)) modified = false;
                        else tinyfd_messageBox("Error", "Cannot save file", "ok", "error", 1);
                    }
                }
                
                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                {
                    const char* save = tinyfd_saveFileDialog("Save File As", "untitled.txt", 0, nullptr, nullptr);
                    if (save) {
                        currentFilePath = save;
                        if (SaveBufferToFile(currentFilePath.c_str(), textBuffer)) modified = false;
                        else tinyfd_messageBox("Error", "Cannot save file", "ok", "error", 1);
                    }
                }

                if (ImGui::MenuItem("Exit")) {
                    glfwSetWindowShouldClose(window, true);
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo")) {}
                if (ImGui::MenuItem("Redo")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Cut")) {}
                if (ImGui::MenuItem("Copy")) {}
                if (ImGui::MenuItem("Paste")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Run"))
            {
                if (ImGui::MenuItem("Build")) {}
                if (ImGui::MenuItem("Stop")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About")) {}
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGuiIO& IO = ImGui::GetIO();
        bool ctrl = IO.KeyCtrl;
        bool shift = IO.KeyShift;
        if (ctrl && ImGui::IsKeyPressed(ImGuiKey_O)) { // Ctrl+O open (optional)
            const char* file = tinyfd_openFileDialog("Open File", "", 0, nullptr, NULL, 0);
            if (file) { if (LoadFileToBuffer(file, textBuffer)) { currentFilePath = file; modified = false; } }
        }
        if (ctrl && ImGui::IsKeyPressed(ImGuiKey_S))
        {
            if (shift) {
                // Save As
                const char* save = tinyfd_saveFileDialog("Save File As", "untitled.txt", 0, nullptr, nullptr);
                if (save) { currentFilePath = save; if (SaveBufferToFile(currentFilePath.c_str(), textBuffer)) modified = false; }
            } else {
                // Save
                if (currentFilePath.empty()) {
                    const char* save = tinyfd_saveFileDialog("Save File", "untitled.txt", 0, nullptr, nullptr);
                    if (save) currentFilePath = save;
                }
                if (!currentFilePath.empty()) { if (SaveBufferToFile(currentFilePath.c_str(), textBuffer)) modified = false; }
            }
        }
        
        glfwGetFramebufferSize(window, &display_w, &display_h);

        // Számítsd ki a kívánt százalékot
        float width = display_w * 0.8f;   // 80% szélesség
        float height = (display_h - 20) * 0.8f; // 80% magasság, figyelembe véve a menüsor magasságát

        ImGui::SetNextWindowPos(ImVec2(0, 20));
        ImGui::SetNextWindowSize(ImVec2(display_w, display_h - 20)); // az ablak maga kitölti a teljes méretet
        ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoCollapse);

        // InputTextMultiline kitöltése 80%-kal
        ImGui::InputTextMultiline("##source", textBuffer.data(), textBuffer.size(),
        ImVec2(width, height),
        ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_AllowTabInput,
        InputTextCallback, &textBuffer);
                   

        // top info
        ImGui::Text("File: %s %s", currentFilePath.empty() ? "[untitled]" : currentFilePath.c_str(), modified ? "(modified)" : "");
        ImGui::Separator();

        

        ImGui::End();


        // --- Renderelés ---
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}