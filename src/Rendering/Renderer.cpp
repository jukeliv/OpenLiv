#include "Renderer.h"

void Renderer::RenderScene(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();

    va.Bind();
    ib.Bind();

    glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetType(), NULL));
}

void Renderer::Clear() const
{
    glCall(glClear(GL_COLOR_BUFFER_BIT));
}