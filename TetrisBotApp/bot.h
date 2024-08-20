#pragma once

#include "SfmlPF.h"
#include "Utils/PlatformUtils.h"

class Bot
{
public:
  void Init();
  void OnUpdate(Timestep ts);
  void OnRender();
  void Reset();
  void GameOver();
private:

};
