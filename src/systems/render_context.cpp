#pragma once
#include <cstdint>
#include <glad/glad.h> // Fixed path based on your dependencies folder structure
#include <stb_image.h> // Using your stb dependency
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct RenderContext
{
    uint32_t quad_vao;

    // Asset handles
    uint32_t default_shader;
    uint32_t outline_shader;
    uint32_t player_texture;

    void init()
    {
        // 1. Initialize the shared Quad VAO
        quad_vao = create_quad_vao();

        // 2. Compile shaders
        default_shader = compile_shader("shaders/default.vert", "shaders/default.frag");
        outline_shader = compile_shader("shaders/default.vert", "shaders/outline.frag");

        // 3. Load textures
        player_texture = load_texture("assets/player.png");
    }

private:
    uint32_t create_quad_vao()
    {
        // 1x1 Quad centered at (0,0): Positions (X, Y), Texture Coordinates (U, V)
        float vertices[] = {
            -0.5f, 0.5f, 0.0f, 1.0f,  // Top Left
            -0.5f, -0.5f, 0.0f, 0.0f, // Bottom Left
            0.5f, -0.5f, 1.0f, 0.0f,  // Bottom Right

            -0.5f, 0.5f, 0.0f, 1.0f, // Top Left
            0.5f, -0.5f, 1.0f, 0.0f, // Bottom Right
            0.5f, 0.5f, 1.0f, 1.0f   // Top Right
        };

        uint32_t vao, vbo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Position Attribute (Location = 0)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

        // UV Texture Coordinate Attribute (Location = 1)
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

        glBindVertexArray(0);
        // Note: We don't delete the VBO here because the VAO tracks it while bound,
        // but you can safely unbind the VBO right after if preferred.
        return vao;
    }

    uint32_t compile_shader(const char *vert_path, const char *frag_path)
    {
        std::string vert_code = read_file(vert_path);
        std::string frag_code = read_file(frag_path);

        const char *vert_src = vert_code.c_str();
        const char *frag_src = frag_code.c_str();

        int success;
        char info_log[512];

        // Vertex Shader
        uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vert_src, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, info_log);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << vert_path << "\n"
                      << info_log << std::endl;
        }

        // Fragment Shader
        uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &frag_src, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, info_log);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << frag_path << "\n"
                      << info_log << std::endl;
        }

        // Shader Program
        uint32_t program_id = glCreateProgram();
        glAttachShader(program_id, vertex);
        glAttachShader(program_id, fragment);
        glLinkProgram(program_id);
        glGetProgramiv(program_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program_id, 512, NULL, info_log);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << info_log << std::endl;
        }

        // Clean up raw shader stages
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program_id;
    }

    uint32_t load_texture(const char *path)
    {
        uint32_t texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        // Texture wrapping/filtering profiles
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Clear pixel art scaling

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true); // Flip texture coordinate system to match OpenGL's origin
        unsigned char *data = stbi_load(path, &width, &height, &channels, 0);

        if (data)
        {
            GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "ERROR::TEXTURE::FAILED_TO_LOAD\n"
                      << path << std::endl;
        }

        stbi_image_free(data);
        return texture_id;
    }

    // Helper function to read shader source code from text file
    std::string read_file(const char *path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cerr << "ERROR::FILE::COULD_NOT_OPEN\n"
                      << path << std::endl;
            return "";
        }
        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    }
};