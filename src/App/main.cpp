#include "App/SandboxLayer.h"
#include "Core/Application.h"
int main()
{
    Core::ApplicationSpecification spec;
    spec.applicationName = "BasicOpenGLRenderer";
    spec.windowSpec.isInDEbugMode = true;

    Core::Application application(spec);
    application.pushLayer<SandboxLayer>();
    application.run();
}
