#pragma once

#include "Application.h"
#include "Base.h"
#include "Instrumentor.h"
#include <iostream>

extern Application *CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char **argv) {
  Log::Init();

  PROFILE_BEGIN_SESSION("Startup", "Profile-Startup.json");
  auto app = CreateApplication({argc, argv});
  PROFILE_END_SESSION();

  PROFILE_BEGIN_SESSION("Runtime", "Profile-Runtime.json");
  app->Run();
  PROFILE_END_SESSION();

  PROFILE_BEGIN_SESSION("Shutdown", "Profile-Shutdown.json");
  delete app;
  PROFILE_END_SESSION();
  return 0;
}
