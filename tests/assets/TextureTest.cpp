#include <gtest/gtest.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include "enginecore/core/assets/texture/GLTexture.h"
//#include "enginecore/core/EngineCoreApplication.h"
//
//
//GLuint compileShader(const char* source, GLenum type) {
//    GLuint shader = glCreateShader(type);
//    glShaderSource(shader, 1, &source, nullptr);
//    glCompileShader(shader);
//
//    GLint success;
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        char infoLog[512];
//        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
//        std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
//    }
//    return shader;
//}
//
//GLuint createShaderProgram(const char* vertSrc, const char* fragSrc) {
//    GLuint vertShader = compileShader(vertSrc, GL_VERTEX_SHADER);
//    GLuint fragShader = compileShader(fragSrc, GL_FRAGMENT_SHADER);
//
//    GLuint program = glCreateProgram();
//    glAttachShader(program, vertShader);
//    glAttachShader(program, fragShader);
//    glLinkProgram(program);
//
//    GLint success;
//    glGetProgramiv(program, GL_LINK_STATUS, &success);
//    if (!success) {
//        char infoLog[512];
//        glGetProgramInfoLog(program, 512, nullptr, infoLog);
//        std::cerr << "Shader program linking error:\n" << infoLog << std::endl;
//    }
//
//    glDeleteShader(vertShader);
//    glDeleteShader(fragShader);
//
//    return program;
//}
//
//void pollTest(std::shared_ptr<Texture> gl_texture)
//{
//    const char* vertSrc = R"(#version 330 core
//
//layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec2 aTexCoord;
//
//out vec2 TexCoord;
//
//void main() {
//    gl_Position = vec4(aPos, 1.0);
//    TexCoord = aTexCoord;
//})"; // vert.glsl
//    const char* fragSrc = R"(#version 330 core
//
//in vec2 TexCoord;
//out vec4 FragColor;
//
//uniform sampler2D texture1;
//
//void main() {
//    FragColor = texture(texture1, TexCoord);
//})"; // frag.glsl
//    GLuint shaderProgram = createShaderProgram(vertSrc, fragSrc);
//
//    glClearColor(0.5, .5, .5, 1);
//
//    float vertices[] = {
//        // (x, y, z)   UV (s, t)
//        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
//         0.5f, -0.5f, 0.0f,    1.0f, 0.0f,  
//         0.5f,  0.5f, 0.0f,    1.0f, 1.0f,  
//        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f  
//    };
//
//    unsigned int indices[] = {
//        0, 1, 2,
//        0, 2, 3  
//    };
//
//    GLuint VAO, VBO, EBO;
//
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
//    while (!GameWindow::shouldClose()) {
//        glClear(GL_COLOR_BUFFER_BIT);
//        gl_texture->bind();
//
//        glUseProgram(shaderProgram);
//        glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
//
//        glBindVertexArray(VAO); 
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        GLenum err = glGetError();
//        if (err != GL_NO_ERROR) {
//            std::cerr << "OpenGL error: " << err << std::endl;
//        }
//
//
//        GameWindow::update();
//    }
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    GameWindow::destructWindow();
//}

TEST(GLTexture, BaseTest)
{
    /*auto a = DisplaySettings();
    GameWindow::createWindow(&a);*/

	std::filesystem::path texture_path = "texture_test.png";

	cv::Mat image = cv::imread(texture_path.string(), cv::ImreadModes::IMREAD_UNCHANGED);

	std::shared_ptr<Texture> gl_texture = Texture::createFromFile<GLTexture>(texture_path);

	for (size_t i = 0; i < image.size().height; i++)
	{
		for (size_t j = 0; j < image.size().width; j++)
		{
			EXPECT_EQ(gl_texture->getBytesArray()[i * image.size().width + j], image.data[i * image.size().width + j]);
		}
	}

}