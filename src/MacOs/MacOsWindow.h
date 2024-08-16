#pragma once

#include "Window.h"
#include "Renderer/GraphicsContext.h"
#include <SFML/Graphics.hpp>

class MacOsWindow : public Window {
public:
  MacOsWindow(const WindowProps &props);
  virtual ~MacOsWindow();

  void OnUpdate() override;

  unsigned int GetWidth() const override { return m_Data.Width; }
  unsigned int GetHeight() const override { return m_Data.Height; }

  // MacOs attributes
  void SetEventCallback(const EventCallbackFn &callback) override {
    m_Data.EventCallback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  void *GetNativeWindow() const override { return (void*)&m_window; }

private:
  virtual void Init(const WindowProps &props);
  virtual void Shutdown();

private:
  sf::RenderWindow m_window;
  sf::Event m_event;
  Scope<GraphicsContext> m_Context;
  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;
    EventCallbackFn EventCallback;
  };
  WindowData m_Data;
};
