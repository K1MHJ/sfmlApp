#include "SfmlPF.h"
#include "TopLayer.h"
#include <Core/EntryPoint.h>
#include <chrono>
#include <thread>

class TetrisApp : public Application {
public:
  TetrisApp(const ApplicationSpecification &specification)
      : Application(specification) {
    PushLayer(new TopLayer());
  }
  ~TetrisApp() {
  }
};
Application *CreateApplication(ApplicationCommandLineArgs args) {
  ApplicationSpecification spec;
  spec.Name = "TetrisApp";
  spec.WorkingDirectory = "";
  spec.CommandLineArgs = args;
  spec.Width = 600;
  spec.Height = 800;

  return new TetrisApp(spec);
}
