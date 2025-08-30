#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stb_image.h>
#include <shaperenderer.h>
#include <string>
#include <vector>
#include <memory>
#include <tinyfiledialogs.h>
#include <cstring> 
#include <fstream>
#include <window.h>
#include <whileaction.h>

using namespace std; 

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string/buffer
        vector<char>* buf = (std::vector<char>*)data->UserData;
        buf->resize(data->BufSize); // BufSize includes terminating null
        data->Buf = buf->data();
    }
    return 0;
}

static bool LoadFileToBuffer(const char* path, vector<char>& buffer)
{
    ifstream ifs(path, ios::binary);
    if (!ifs) return false;
    string content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    buffer.assign(content.begin(), content.end());
    buffer.push_back('\0');
    return true;
}

static bool SaveBufferToFile(const char* path, const vector<char>& buffer)
{
    ofstream ofs(path, ios::binary);
    if (!ofs) return false;
    // buffer contains terminating null; write only up to it
    ofs.write(buffer.data(), strlen(buffer.data()));
    return ofs.good();
}

const char* vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;    // x,y,z
layout (location = 1) in vec3 aColor;  // r,g,b
out vec3 ourColor;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
})";

const char* fragmentShaderSource = R"(#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(ourColor, 1.0);
})";



GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3,  0.0f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f * float(sqrt(3)) / 3,  0.0f,   1.0f, 0.0f, 0.0f,
     0.0f,  0.5f * float(sqrt(3)) * 2/3,0.0f,   1.0f, 0.0f, 0.0f
};




int main()
{
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    
    int display_w = 800;
    int display_h = 600;
    
    GLFWwindow* window = makeWindow(display_w, display_h, "Radon Modelling Software");
    if (!window) return -1; 


    // Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    //stb_image.h implementation  
    GLFWimage images[1];
    int width, height, channels;
    unsigned char *pixels = stbi_load("../resources/icon.png", &width, &height, &channels, 4);
    if (pixels)
    {
    images[0].width = width;
    images[0].height = height;
    images[0].pixels = pixels;
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(pixels);
    }   else    {
    std::cout << "Failed to load icon.png" << std::endl;
    };

    // shapes
    //Shaperenderer::initShape(vertices, 3);
    
    vector<char> textBuffer;
    textBuffer.push_back('\0'); // initially empty string
    string currentFilePath;
    bool modified = false;

    whileAction(window, display_w, display_h, textBuffer, currentFilePath, modified);
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
};