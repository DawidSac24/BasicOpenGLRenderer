# --- 1. The Engine Library ---
file(GLOB_RECURSE ENGINE_SOURCES "Engine/*.cpp" "Engine/*.h")

add_library(MyEngine STATIC ${ENGINE_SOURCES})

target_compile_definitions(MyEngine PUBLIC PROJECT_ROOT="${CMAKE_SOURCE_DIR}")
target_include_directories(MyEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# --- Find Packages (Names taken from your Vcpkg logs) ---
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nfd CONFIG REQUIRED)   # <--- CORRECT NAME
find_package(Stb REQUIRED)          # <--- CORRECT NAME (Capital S)

# --- Link Libraries ---
target_link_libraries(MyEngine PUBLIC 
    glm::glm
    OpenGL::GL
    GLEW::GLEW                   # <--- Capitalized
    glfw                            # <--- Lowercase (from vcpkg log)
    assimp::assimp
    nfd::nfd                        # <--- CORRECT NAME
    imgui::imgui
)

# --- STB is a special case (Variables, not Targets) ---
if(Stb_FOUND)
    target_include_directories(MyEngine PUBLIC ${Stb_INCLUDE_DIR})
endif()

# --- 2. The Application Executable ---
file(GLOB_RECURSE APP_SOURCES "Application/*.cpp" "Application/*.h")

add_executable(SandboxApp ${APP_SOURCES})

target_link_libraries(SandboxApp PRIVATE MyEngine)

# (Keep your Asset Copying commands below...)
