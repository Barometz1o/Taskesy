#pragma once
#include <string>
#include <imgui.h>

class FileDialogs {
	public:
		// These return an empty string if cancelled
		static std::string OpenFile(const char* filter, GLFWwindow* window);
		static std::string SaveFile(const char* filter, GLFWwindow* window);
};
