file(GLOB_RECURSE ENGINE_SOURCES "Engine/*.cpp" "Engine/*.h")

add_library(MyEngine STATIC ${ENGINE_SOURCES})

target_compile_definitions(MyEngine PUBLIC PROJECT_ROOT="${CMAKE_SOURCE_DIR}")
target_include_directories(MyEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nfd CONFIG REQUIRED)   
find_package(Stb REQUIRED)          
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(MyEngine PUBLIC 
    glm::glm
    OpenGL::GL
    GLEW::GLEW                   
    glfw                           
    imgui::imgui
    fmt::fmt
    PRIVATE
    nfd::nfd                      
    assimp::assimp
)

if(Stb_FOUND)
    target_include_directories(MyEngine PUBLIC ${Stb_INCLUDE_DIR})
endif()

file(GLOB_RECURSE APP_SOURCES "Application/*.cpp" "Application/*.h")

add_executable(SandboxApp ${APP_SOURCES})

target_link_libraries(SandboxApp PRIVATE MyEngine)

# (Keep your Asset Copying commands below...)
