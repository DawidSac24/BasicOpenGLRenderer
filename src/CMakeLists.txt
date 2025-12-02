add_library(Engine STATIC
    Renderer.cpp
    OpenGLContext.cpp
)


target_include_directories(MyEngine 
    PUBLIC  ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(MyEngine 
    PUBLIC 
        glm
    PRIVATE 
        glfw
        glad
)

if(MSVC)
  target_compile_definitions(Engine PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
