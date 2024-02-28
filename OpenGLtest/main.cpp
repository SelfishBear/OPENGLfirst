#include <iostream>
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>

const char * vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main(){\n"
        "gl_Position = vec4(position, 1.0);\n"
        "}\0";

const char * fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 fragColor\n"
        "void main(){\n"
        "fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0);\n"
        "}\0";

void input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void sizeCallBack(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "MRPENIS", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Error" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, sizeCallBack);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        return -2;
    }

    int successCode;
    char infoLog[512];
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr );
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successCode);

    if(!successCode)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1 , &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successCode);

    if(!successCode)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    }

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successCode);

    if(!successCode)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //==========================================================

    float verticis[] =
            {
                -1.0f, 1.0f, 0.0f,
                1.0f,  -1.0f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                -1.0f, -1.0f, 0.0f
            };

    unsigned int indices[] =
            {
                0, 1, 3,
                1, 2, 3
            };

    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticis), verticis, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    double previousTime = glfwGetTime();
    int fps = 0;

    while (!glfwWindowShouldClose(window)) {
        input(window);
        glClearColor(1, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        double currentTime = glfwGetTime();
        fps++;
        if(currentTime - previousTime >= 1.0)
        {
            std::string title = "MRPENIS FPS: " + std::to_string(fps);
            glfwSetWindowTitle(window, title.c_str());
            fps = 0;
            previousTime = currentTime;
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}
