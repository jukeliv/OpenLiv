#pragma once

#include <GL/glew.h>
#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"
#include "Utils/Shader.h"

//Static renderer cuz i dont want to fucking add a "Renderer" everytime i need to draw something
class Renderer {
public:
    static void RenderScene(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
    {
        shader.Bind();

        va.Bind();
        ib.Bind();

        glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetType(), NULL));
    }
    static void Clear()
    {
        glCall(glClear(GL_COLOR_BUFFER_BIT));
    }
};