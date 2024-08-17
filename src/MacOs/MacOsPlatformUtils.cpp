#include "Core/Application.h"
#include "Utils/PlatformUtils.h"
#include "pch.h"
#include <chrono>

using namespace std::chrono;

uint64_t Time::GetTime() {
  uint64_t ms =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();
  //uint64_t sec = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
  return ms;
}

std::string FileDialogs::OpenFile(const char *filter) {
  // OPENFILENAMEA ofn;
  // CHAR szFile[260] = {0};
  // CHAR currentDir[256] = {0};
  // ZeroMemory(&ofn, sizeof(OPENFILENAME));
  // ofn.lStructSize = sizeof(OPENFILENAME);
  // ofn.hwndOwner = glfwGetWin32Window(
  //     (GLFWwindow *)Application::Get().GetWindow().GetNativeWindow());
  // ofn.lpstrFile = szFile;
  // ofn.nMaxFile = sizeof(szFile);
  // if (GetCurrentDirectoryA(256, currentDir))
  //   ofn.lpstrInitialDir = currentDir;
  // ofn.lpstrFilter = filter;
  // ofn.nFilterIndex = 1;
  // ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

  // if (GetOpenFileNameA(&ofn) == TRUE)
  //   return ofn.lpstrFile;

  return std::string();
}

std::string FileDialogs::SaveFile(const char *filter) {
  // OPENFILENAMEA ofn;
  // CHAR szFile[260] = {0};
  // CHAR currentDir[256] = {0};
  // ZeroMemory(&ofn, sizeof(OPENFILENAME));
  // ofn.lStructSize = sizeof(OPENFILENAME);
  // ofn.hwndOwner = glfwGetWin32Window(
  //     (GLFWwindow *)Application::Get().GetWindow().GetNativeWindow());
  // ofn.lpstrFile = szFile;
  // ofn.nMaxFile = sizeof(szFile);
  // if (GetCurrentDirectoryA(256, currentDir))
  //   ofn.lpstrInitialDir = currentDir;
  // ofn.lpstrFilter = filter;
  // ofn.nFilterIndex = 1;
  // ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

  // // Sets the default extension by extracting it from the filter
  // ofn.lpstrDefExt = strchr(filter, '\0') + 1;

  // if (GetSaveFileNameA(&ofn) == TRUE)
  //   return ofn.lpstrFile;

  return std::string();
}
