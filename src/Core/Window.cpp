#include "Core/Window.h"
#include "pch.h"

#ifdef PLATFORM_MACOS
#include "MacOs/MacOsWindow.h"
#endif

Scope<Window> Window::Create(const WindowProps &props) {
#ifdef PLATFORM_MACOS
  return CreateScope<MacOsWindow>(props);
#else
  CORE_ASSERT(false, "Unknown platform");
  return nullptr;
#endif
}
