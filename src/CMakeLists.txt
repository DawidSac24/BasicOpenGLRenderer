# --- 1. The Engine Library ---
# Gather all files inside /src/Engine recursively
file(GLOB_RECURSE ENGINE_SOURCES "Engine/*.cpp" "Engine/*.h")

add_library(MyEngine STATIC ${ENGINE_SOURCES})

# Define Includes
# "PUBLIC" means: The Engine uses this, AND anyone using the Engine sees this.
# This allows you to do #include "Engine/Core/Log.h" anywhere.
target_include_directories(MyEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link Dependencies
# PUBLIC because the Application will likely need GLM/Imgui types too
target_link_libraries(MyEngine PUBLIC 
    glfw        
    OpenGL::GL
    GLEW::glew
    stb_image
    glm::glm   
    imgui
)

# --- 2. The Application Executable ---
# Gather all files inside /src/Application recursively
file(GLOB_RECURSE APP_SOURCES "Application/*.cpp" "Application/*.h")

add_executable(SandboxApp ${APP_SOURCES})

# The App only needs to link to the Engine. 
# It inherits OpenGL, ImGui, etc., because MyEngine linked them as PUBLIC.
target_link_libraries(SandboxApp PRIVATE MyEngine)
