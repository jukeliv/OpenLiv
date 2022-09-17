#include "OpenLiv\Core.h"

using namespace OpenLiv;

#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) while (glGetError());\
    x;\
    ASSERT(glCheckError(#x, __FILE__, __LINE__))

static bool glCheckError(const char* func, const char* file, int line)
{
    while (GLenum err = glGetError())
    {
        fprintf(stderr, "[OpenGL Error] ( %u ) %s || %s: %i\n", err, func, file, line);
        return false;
    }
    return true;
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    auto* window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    float vertexData[] = {
    /*    Positions      Indices    */
        -0.5f, -0.5f,      //0
         0.5f, -0.5f,      //1
         0.5f,  0.5f,      //2
        -0.5f,  0.5f       //3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buffer;
    glCall(glGenBuffers(1, &buffer));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    glCall(glBufferData(GL_ARRAY_BUFFER, 6*2 * sizeof(float), vertexData, GL_STATIC_DRAW));

    glCall(glEnableVertexAttribArray(0));
    glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    unsigned int ibo;
    glCall(glGenBuffers(1, &ibo));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    ShadersUtil shaderUtil;
    unsigned int shader = shaderUtil.CreateShader("Main/");

    glCall(glUseProgram(shader));

    glUniform3f(shaderUtil.UniformLocation(shader, "uColor"), 0.35f, 0.1f, 0.85f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}