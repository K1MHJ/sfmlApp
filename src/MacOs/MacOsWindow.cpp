#include "MacOs/MacOsWindow.h"
#include "Core/Input.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <SFML/Window/Keyboard.hpp>

#include "pch.h"

static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char *description) {
  CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

MacOsWindow::MacOsWindow(const WindowProps &props) {
  PROFILE_FUNCTION();

  Init(props);
}

MacOsWindow::~MacOsWindow() {
  PROFILE_FUNCTION();

  Shutdown();
}

void MacOsWindow::Init(const WindowProps &props) {
  PROFILE_FUNCTION();

  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
            props.Height);
  m_window.create(sf::VideoMode(props.Width, props.Height), "My window");

  m_Context = GraphicsContext::Create(&m_window);
  m_Context->Init();
}

void MacOsWindow::Shutdown() {
  PROFILE_FUNCTION();
  CORE_INFO("Close window");
  m_window.close();
}

void MacOsWindow::OnUpdate() {
  PROFILE_FUNCTION();
  
  if (m_window.isOpen()) {
    if (m_window.pollEvent(m_event)) {
      switch (m_event.type) {
      case sf::Event::Closed: {
        WindowCloseEvent event;
        m_Data.EventCallback(event);
      } break;
      case sf::Event::KeyPressed: {
        if(m_event.key.scancode == sf::Keyboard::Scancode::Escape){
          WindowCloseEvent event;
          m_Data.EventCallback(event);
        }else{
          KeyPressedEvent event(m_event.key.scancode, 0);
          m_Data.EventCallback(event);
        }
      } break;
      case sf::Event::KeyReleased: {
        KeyReleasedEvent event(m_event.key.scancode);
        m_Data.EventCallback(event);
      } break;
      case sf::Event::Resized: {
        WindowResizeEvent event(m_event.size.width, m_event.size.height);
        m_Data.EventCallback(event);
      } break;
      case sf::Event::LostFocus: {

      } break;
      case sf::Event::GainedFocus: {

      } break;
      case sf::Event::TextEntered: {
        KeyTypedEvent event(m_event.text.unicode);
        m_Data.EventCallback(event);
      } break;
      case sf::Event::MouseWheelScrolled: {
        if (m_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
          MouseScrolledEvent event((float)0, (float)m_event.mouseWheelScroll.y);
          m_Data.EventCallback(event);
        } else if (m_event.mouseWheelScroll.wheel ==
                   sf::Mouse::HorizontalWheel) {
          MouseScrolledEvent event((float)m_event.mouseWheelScroll.x, (float)0);
          m_Data.EventCallback(event);
        }
      } break;
      case sf::Event::MouseButtonPressed: {
        MouseButtonPressedEvent event(m_event.mouseButton.button);
        m_Data.EventCallback(event);
      } break;
      case sf::Event::MouseButtonReleased: {
        MouseButtonReleasedEvent event(m_event.mouseButton.button);
        m_Data.EventCallback(event);
      } break;
      case sf::Event::MouseMoved: {
        MouseMovedEvent event((float)m_event.mouseMove.x,
                              (float)m_event.mouseMove.y);
        m_Data.EventCallback(event);
      } break;
      case sf::Event::MouseLeft:
        break;
      default:
        break;
      }
      //m_Context->SwapBuffers();
    }
  }
}

void MacOsWindow::SetVSync(bool enabled) {
  PROFILE_FUNCTION();

  m_Data.VSync = enabled;
}

bool MacOsWindow::IsVSync() const { return m_Data.VSync; }

void MacOsWindow::OnTimer()
{

}
