#include "GameLayer.h"

#include "Engine/Renderer/Renderer.h"

GameLayer::GameLayer()
{
    m_application = &Core::Application::get();
    m_scene = m_application->getActiveScene();
    m_scene->init();
}

GameLayer::~GameLayer() { }

void GameLayer::onUpdate()
{
}

void GameLayer::onRender()
{
    Renderer::RenderCommand::clear();
    Renderer::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });

    m_scene->onRender();
}

void GameLayer::onEvent(Core::Event& event) { }
void GameLayer::onDetach() { }
