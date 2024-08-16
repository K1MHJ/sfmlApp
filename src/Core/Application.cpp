#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Renderer/Renderer.h"
#include "Utils/PlatformUtils.h"
#include "pch.h"

Application *Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecification &specification)
    : m_Specification(specification) {
  PROFILE_FUNCTION();

  CORE_ASSERT(!s_Instance, "Application already exists!");
  s_Instance = this;

  // Set working directory here
  if (!m_Specification.WorkingDirectory.empty())
    std::filesystem::current_path(m_Specification.WorkingDirectory);

  m_Window = Window::Create(WindowProps(m_Specification.Name));
  m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

  Renderer::Init();
}

Application::~Application() {
  PROFILE_FUNCTION();
  Renderer::Shutdown();
}

void Application::PushLayer(Layer *layer) {
  PROFILE_FUNCTION();

  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
  PROFILE_FUNCTION();

  m_LayerStack.PushOverlay(layer);
  layer->OnAttach();
}

void Application::Close() { m_Running = false; }

void Application::SubmitToMainThread(const std::function<void()> &function) {
  std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

  m_MainThreadQueue.emplace_back(function);
}

void Application::OnEvent(Event &e) {
  PROFILE_FUNCTION();

  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      BIND_EVENT_FN(Application::OnWindowClose));
  dispatcher.Dispatch<WindowResizeEvent>(
      BIND_EVENT_FN(Application::OnWindowResize));

  for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
    if (e.Handled)
      break;
    (*it)->OnEvent(e);
  }
}

void Application::Run() {
  PROFILE_FUNCTION();

  while (m_Running) {
    PROFILE_SCOPE("RunLoop");

    float time = Time::GetTime();
    Timestep timestep = time - m_LastFrameTime;
    m_LastFrameTime = time;

    ExecuteMainThreadQueue();

    if (!m_Minimized) {
      {
        PROFILE_SCOPE("LayerStack OnUpdate");

        for (Layer *layer : m_LayerStack)
          layer->OnUpdate(timestep);
      }
    }
    m_Window->OnUpdate();
  }
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

bool Application::OnWindowResize(WindowResizeEvent &e) {
  PROFILE_FUNCTION();

  if (e.GetWidth() == 0 || e.GetHeight() == 0) {
    m_Minimized = true;
    return false;
  }
  m_Minimized = false;
  Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
  return false;
}

void Application::ExecuteMainThreadQueue() {
  std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

  for (auto &func : m_MainThreadQueue)
    func();

  m_MainThreadQueue.clear();
}
