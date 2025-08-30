#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <vector>
#include <string>
#include <imgui.h>

// callback
int InputTextCallback(ImGuiInputTextCallbackData* data);

// fájl beolvasás bufferbe
bool LoadFileToBuffer(const char* path, std::vector<char>& buffer);

// buffer mentése fájlba
bool SaveBufferToFile(const char* path, const std::vector<char>& buffer);

#endif