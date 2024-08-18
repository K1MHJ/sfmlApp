#pragma once

#include "RendererAPI.h"
#include <cstdint>
#include <SFML/Graphics.hpp>

class SFMLRendererAPI : public RendererAPI
{
public:
  SFMLRendererAPI();
  virtual void Init() override;
  virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

  virtual void SetClearColor(uint8_t red, uint8_t green, uint8_t blue) override;
  virtual void GetClearColor(uint8_t& red, uint8_t& green, uint8_t& blue) override;
  virtual void Clear() override;

  virtual void SetLineWidth(float width) override;
private:
  uint8_t m_red;
  uint8_t m_green;
  uint8_t m_blue;
};
