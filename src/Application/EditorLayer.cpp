#include "EditorLayer.h"

#include "Engine/Platform/OpenGL/Application.h"
#include "imgui.h"

EditorLayer::EditorLayer() { }

EditorLayer::~EditorLayer() { }

void EditorLayer::onUpdate() { }

void EditorLayer::onRender() { }

void EditorLayer::onGuiRender()
{
    // 1. Get the scene
    m_scene = Core::Application::get().getActiveScene().get();

    m_scene->onGuiRender();

    if (m_selectedContext)
    {
        m_selectedContext->onGuiRender();
    }
}

void EditorLayer::onEvent(Core::Event& event) { }

void EditorLayer::onDetach() { }
