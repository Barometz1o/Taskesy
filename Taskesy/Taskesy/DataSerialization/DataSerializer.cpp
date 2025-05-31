#include "DataSerializer.h"

#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

void DataSerializer::Serialize(ImVec4 main_color, size_t taskesyRows, size_t taskesyColumns, std::vector<const char*> columnNames, std::vector<const char*> text, const std::string& filepath)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Main Colour";
	out << YAML::Value << main_color.x, main_color.y, main_color.z, main_color.w;
	out << YAML::Key << "position";
	out << YAML::Value << "LF";
	out << YAML::EndMap;

}

void DataSerializer::Deserialize(const std::string& filepath)
{

}