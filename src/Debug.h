#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

// TODO:
// ADD a line error printing

namespace Core
{
// THIS PART IS FROM :
// https://blog.nobel-joergensen.com/2013/02/17/debugging-opengl-part-2-using-gldebugmessagecallback
inline void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                            const GLchar *message, const void *userParam)
{
    std::cout << "message: " << message << std::endl;
    std::cout << "type: ";
    std::string returnType = "";
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        returnType = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        returnType = "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        returnType = "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        returnType = "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        returnType = "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        returnType = "OTHER";
        break;
    }
    std::cout << returnType << std::endl;

    std::cout << "id: " << id << std::endl;
    std::cout << "severity: ";

    std::string returnSeverity = "";
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_LOW:
        returnSeverity = "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        returnSeverity = "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        returnSeverity = "HIGH";
        break;
    }
}

inline void getOpenGLErrors()
{
    if (glDebugMessageCallback)
    {
        std::cout << "Register OpenGL debug callback " << std::endl;
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(openglCallbackFunction, nullptr);
        GLuint unusedIds = 0;
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
    }
}
} // namespace Core
