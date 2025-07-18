#include "PlatformUtils.h"

#include <windows.h>
#include <commdlg.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

std::string FileDialogs::OpenFile(const char* filter, GLFWwindow* window)
{
    OPENFILENAMEA ofn;                                                           // common dialog box structure
    char szFile[MAX_PATH] = { 0 };                                              // if using TCHAR macros
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = glfwGetWin32Window(window);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameA(&ofn) == TRUE)
        return ofn.lpstrFile;

    return std::string();
}


std::string FileDialogs::SaveFile(const char* filter, GLFWwindow* window)
{
    OPENFILENAMEA ofn;                                                           // common dialog box structure
    char szFile[MAX_PATH] = { 0 };                                              // if using TCHAR macros
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = glfwGetWin32Window(window);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    std::string extension = ".todo";

    if (GetSaveFileNameA(&ofn))
        return (std::string(ofn.lpstrFile)+extension).c_str(); //ofn.lpstrFile;

    return std::string();
}