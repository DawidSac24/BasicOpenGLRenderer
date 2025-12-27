#include "EditorLayer.h"
#include "Engine/Platform/OpenGL/Application.h"

#include "SandboxLayer.h"

int main()
{
    Core::ApplicationSpecification spec;
    spec.applicationName = "BasicOpenGLRenderer";
    spec.windowSpec.isInDEbugMode = true;

    Core::Application application(spec);
    application.pushLayer<SandboxLayer>();
    // application.pushLayer<EditorLayer>();
    application.run();
}
