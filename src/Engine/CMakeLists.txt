add_subdirectory(Core)
add_subdirectory(Platform)
add_subdirectory(Renderer)
add_subdirectory(Scene)

target_sources(Engine PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Editor/EditorLayer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Editor/EditorLayer.h
  ${CMAKE_CURRENT_LIST_DIR}/Editor/EditorPanels.h
  ${CMAKE_CURRENT_LIST_DIR}/ImGui/ImGuiImpl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ImGui/ImGuiImpl.h
  ${CMAKE_CURRENT_LIST_DIR}/ImGui/MenuItems.h
)
