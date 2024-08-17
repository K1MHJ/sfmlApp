#include "SfmlPF.h"
#include <Core/EntryPoint.h>
#include "TopLayer.h"

class TetrisApp : public Application
{
public:
  TetrisApp(const ApplicationSpecification& specification)
  : Application(specification)
  {
    PushLayer(new TopLayer());
  }
  ~TetrisApp()
  {
  }
};
Application* CreateApplication(ApplicationCommandLineArgs args)
{
  ApplicationSpecification spec;
  spec.Name = "SfmlApp";
  spec.WorkingDirectory = "./bin";
  spec.CommandLineArgs = args;

  return new TetrisApp(spec);
}

