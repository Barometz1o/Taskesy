# pragma once

#include <string>
#include <imgui.h>
#include <vector>

class DataSerializer
{
public:
	void Serialize(ImVec4* main_color, ImVec4 boxColor, size_t taskesyRows, size_t taskesyColumns, std::vector<const char*> columnNames, std::vector<const char*> text, const std::string& filepath);
	void Deserialize(ImVec4* main_color, ImVec4& boxColor, int& taskesyRows, int& taskesyColumns, std::vector<const char*>& columnNames, std::vector<const char*>& text, const std::string& filepath);
};