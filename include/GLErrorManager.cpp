#include "GLErrorManager.h"

bool glCheckError(const char* func, const char* file, int line)
{
    while (GLenum err = glGetError())
    {
        fprintf(stderr, "[OpenGL Error] ( %u ) %s || %s: %i\n", err, func, file, line);
        std::cin.get();
        return false;
    }
    return true;
}