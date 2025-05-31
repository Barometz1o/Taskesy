#include <fstream>

#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

#include "DataSerializer.h"

void DataSerializer::Serialize(ImVec4* main_color, ImVec4 boxColor, size_t taskesyRows, size_t taskesyColumns, std::vector<const char*> columnNames, std::vector<const char*> text, const std::string& filepath)
{
	ImVec4 mainColor = *main_color;
	YAML::Emitter out;

	// Taskesy Globals
	out << YAML::BeginMap;

	// Main backgroud color
	out << YAML::Key << "Main Color";
	out << YAML::Value << YAML::Flow << YAML::BeginSeq;
	out << mainColor.x << mainColor.y << mainColor.z << mainColor.w;				// Alpha is not needed but still useful to have it
	out << YAML::Value << YAML::EndSeq;

	// Main box color
	out << YAML::Key << "Main Color";
	out << YAML::Value << YAML::Flow << YAML::BeginSeq;
	out << boxColor.x << boxColor.y << boxColor.z << boxColor.w;				// Alpha is not needed but still useful to have it
	out << YAML::Value << YAML::EndSeq;

	// Number of rows
	out << YAML::Key << "Rows";
	out << YAML::Value << taskesyRows;

	// Number of columns
	out << YAML::Key << "Columns";
	out << YAML::Value << taskesyColumns;

	// Column Names
	out << YAML::Key << "Column Names";
	out << YAML::Value << YAML::BeginSeq;
	for (int i = 0; i < taskesyColumns; ++i)
	{
		out << columnNames[i];
	}
	out << YAML::Value << YAML::EndSeq;

	// Box text
	out << YAML::Key << "Box Text";
	out << YAML::Value << YAML::BeginSeq;

	for (int i = 0; i < taskesyColumns*taskesyRows; ++i)
	{
		out << text[i];
	}
	out << YAML::Value << YAML::EndSeq;
	out << YAML::EndMap;

	// We save our .todo file
	std::ofstream fout(filepath);
	fout << out.c_str();
}

void DataSerializer::Deserialize(ImVec4* main_color, ImVec4* boxColor, size_t* taskesyRows, size_t* taskesyColumns, std::vector<const char*>* columnNames, std::vector<const char*>* text, const std::string& filepath)
{

}