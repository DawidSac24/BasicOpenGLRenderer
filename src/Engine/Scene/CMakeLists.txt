add_subdirectory(Components)

target_sources(Engine PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/EditorCamera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EditorCamera.h
    ${CMAKE_CURRENT_LIST_DIR}/Entity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Entity.h
    ${CMAKE_CURRENT_LIST_DIR}/EntityFactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EntityFactory.h
    ${CMAKE_CURRENT_LIST_DIR}/Scene.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Scene.h
    ${CMAKE_CURRENT_LIST_DIR}/SceneSerializer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SceneSerializer.h
)
