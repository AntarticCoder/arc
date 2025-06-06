#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

#include <glad/gl.h>
#include <SDL.h>

#include "arc/math/arc_vector.h"

struct ExampleData
{
    SDL_Window* window;
    SDL_GLContext glContext;
};

struct Renderable
{
    arc::Vec3 position = arc::Vec3(0.0f);
    arc::Vec3 scale = arc::Vec3(1.0f);
    arc::Vec3 color = arc::Vec3(0.0f);

    Renderable(arc::Vec3 pos) : position(pos) {}
    Renderable(arc::Vec3 pos, arc::Vec3 scale) : position(pos), scale(scale) {}
};

struct GraphicsData
{
    unsigned VAO;
    unsigned VBO;
    unsigned shaderProgram;

    std::vector<Renderable> objects;
    std::vector<arc::Vec3> randomColors;
    std::vector<Renderable> triggers;
};

void Ortho(float* matrix, float left, float right, float bottom, float top, float near, float far)
{
    matrix[0] = 2.0f / (right - left);
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 2.0f / (top - bottom);
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = -2.0f / (far - near);
    matrix[11] = 0.0f;

    matrix[12] = -1 * (right + left) / (right - left);
    matrix[13] = -1 * (top + bottom) / (top - bottom);
    matrix[14] = -1 * (far + near) / (far - near);
    matrix[15] = 1.0f;

}

std::string ReadFile(std::string filePath)
{
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if(!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

ExampleData IntializeExample()
{
    ExampleData data{};

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("Hello SDL",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!window) {
        std::cerr << "Failed to create SDL Window " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if(!glContext) {
        std::cerr << "Failed to create SDL OpenGL context: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    data.window = window;
    data.glContext = glContext;

    int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    int w, h;
    SDL_GetWindowSize(data.window, &w, &h);
    glViewport(0, 0, w, h);

    return data;
}

GraphicsData CreateOpenGLResources()
{
    GraphicsData data = {};

    const float quadVertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    glGenVertexArrays(1, &data.VAO);
    glBindVertexArray(data.VAO);
    
    glGenBuffers(1, &data.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, data.VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, (quadVertices), GL_STATIC_DRAW);  

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    std::string vertexSourceStr = ReadFile("examples/opengl_2d/resources/vert.vert");
    const char* vertexSource = vertexSourceStr.c_str();
    std::string fragmentSourceStr = ReadFile("examples/opengl_2d/resources/frag.frag");
    const char* fragmentSource = fragmentSourceStr.c_str();

    unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex Shader compilation failed: " << infoLog << "\n";
    }

    unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment Shader compilation failed: " << infoLog << "\n";
    }

    data.shaderProgram = glCreateProgram();
    glAttachShader(data.shaderProgram, vertexShader);
    glAttachShader(data.shaderProgram, fragmentShader);
    glLinkProgram(data.shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    for(int i = 0; i < 16; i++) {
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<float> distribution(0.0, 1.0);
        data.randomColors.push_back(arc::Vec3(1.0f, distribution(rng), distribution(rng)));
    }

    return data;
}

void Render(GraphicsData* data)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int location = 0;
    float perspectiveMatrix[16];
    float aspect = 800.0f / 600.0f;
    float perspectiveScale = 10.0f;
    Ortho(perspectiveMatrix, 
        -1 * aspect * perspectiveScale, 
        aspect * perspectiveScale, 
        -1 * perspectiveScale, 
        perspectiveScale, 
        -1.0f, 
        1.0f
    );

    for(int i = 0; i < data->objects.size(); i++)
    {
        auto object = data->objects[i];

        glBindVertexArray(data->VAO);
        glUseProgram(data->shaderProgram);

        float color[3] = {(float)data->randomColors[i % 16].x, (float)data->randomColors[i % 16].y, (float)data->randomColors[i % 16].z};
        float position[2] = {(float)object.position.x, (float)object.position.y};
        float scale[2] = {(float)object.scale.x, (float)object.scale.y};
        
        location = glGetUniformLocation(data->shaderProgram, "color");
        glUniform3fv(location, 1, color);
        location = glGetUniformLocation(data->shaderProgram, "perspective");
        glUniformMatrix4fv(location, 1, GL_FALSE, perspectiveMatrix);
        location = glGetUniformLocation(data->shaderProgram, "position");
        glUniform2fv(location, 1, position);
        location = glGetUniformLocation(data->shaderProgram, "scale");
        glUniform2fv(location, 1, scale);
    
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    for(int i = 0; i < data->triggers.size(); i++)
    {
        auto trigger = data->triggers[i];

        glBindVertexArray(data->VAO);
        glUseProgram(data->shaderProgram);

        float color[3] = {(float)data->randomColors[i % 16].x, (float)data->randomColors[i % 16].y, (float)data->randomColors[i % 16].z};
        float position[2] = {(float)trigger.position.x, (float)trigger.position.y};
        float scale[2] = {(float)trigger.scale.x, (float)trigger.scale.y};
        
        location = glGetUniformLocation(data->shaderProgram, "color");
        glUniform3fv(location, 1, color);
        location = glGetUniformLocation(data->shaderProgram, "perspective");
        glUniformMatrix4fv(location, 1, GL_FALSE, perspectiveMatrix);
        location = glGetUniformLocation(data->shaderProgram, "position");
        glUniform2fv(location, 1, position);
        location = glGetUniformLocation(data->shaderProgram, "scale");
        glUniform2fv(location, 1, scale);
        
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}