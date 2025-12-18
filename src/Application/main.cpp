#include "Application/MVPTestLayer.h"
#include "Application/SandboxLayer.h"
#include "Core/Application.h"
int main() {
  Core::ApplicationSpecification spec;
  spec.applicationName = "BasicOpenGLRenderer";
  spec.windowSpec.isInDEbugMode = true;

  Core::Application application(spec);
  application.pushLayer<MVPTestLayer>();
  application.run();
}
