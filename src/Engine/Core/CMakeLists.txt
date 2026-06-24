add_subdirectory(Events)
add_subdirectory(Reflection)

target_sources(Engine PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/AssetManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/AssetManager.h
    ${CMAKE_CURRENT_LIST_DIR}/FileSystem.h
    ${CMAKE_CURRENT_LIST_DIR}/keyCodes.h
    ${CMAKE_CURRENT_LIST_DIR}/Layer.h
    ${CMAKE_CURRENT_LIST_DIR}/LayerStack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LayerStack.h
    ${CMAKE_CURRENT_LIST_DIR}/Log.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Log.h
    ${CMAKE_CURRENT_LIST_DIR}/UUID.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UUID.h
)


