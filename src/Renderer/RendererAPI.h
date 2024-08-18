#pragma once

#include "Base.h"

class RendererAPI {
public:
  enum class API { None = 0, SFML = 1 };

public:
  virtual ~RendererAPI() = default;

  virtual void Init() = 0;
  virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width,
                           uint32_t height) = 0;
  virtual void SetClearColor(uint8_t red, uint8_t green, uint8_t blue) = 0;
  virtual void GetClearColor(uint8_t& red, uint8_t& green, uint8_t& blue) = 0;
  virtual void Clear() = 0;

  virtual void SetLineWidth(float width) = 0;

  static API GetAPI() { return s_API; }
  static Scope<RendererAPI> Create();

private:
  static API s_API;
};
