#pragma once

#include <GL/glew.h>
#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"
#include "Utils/Shader.h"

class Renderer {
public: 
    void RenderScene(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};