#include <fstream>

#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

#include "DataSerializer.h"

void DataSerializer::Serialize(ImVec4* main_color, ImVec4 boxColor, size_t taskesyRows, size_t taskesyColumns, std::vector<const char*> columnNames, std::vector<const char*> text, std::vector<int> numberColumn, const std::string& filepath)
{
	ImVec4 mainColor = *main_color;
	YAML::Emitter out;

	// Taskesy Globals
	out << YAML::BeginMap;

	// Taskesy file identification
	out << YAML::Key << "Taskesy";
	out << YAML::Value << true;

	// Main backgroud color
	out << YAML::Key << "Main Color";
	out << YAML::Value << YAML::Flow << YAML::BeginSeq;
	out << mainColor.x << mainColor.y << mainColor.z << mainColor.w;				// Alpha is not needed but still useful to have it
	out << YAML::Value << YAML::EndSeq;

	// Main box color
	out << YAML::Key << "Box Color";
	out << YAML::Value << YAML::Flow << YAML::BeginSeq;
	out << boxColor.x << boxColor.y << boxColor.z << boxColor.w;					// Alpha is not needed but still useful to have it
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

	// Number of Boxes per Column
	out << YAML::Key << "Number of Boxes per Column";
	out << YAML::Value << YAML::BeginSeq;
	for (int i = 0; i < taskesyColumns; ++i)
	{
		out << numberColumn[i];
	}
	out << YAML::Value << YAML::EndSeq;

	// Box text
	out << YAML::Key << "Box Text";
	out << YAML::Value << YAML::BeginSeq;

	for (int column = 0; column < taskesyColumns; column++)
	{
		for (int row = 0; row < taskesyRows; row++)
		{
			out << text[row * taskesyColumns + column];
		}
	}

	out << YAML::Value << YAML::EndSeq;
	out << YAML::EndMap;

	// We save our .todo file
	std::ofstream fout(filepath);
	fout << out.c_str();
}

void DataSerializer::Deserialize(ImVec4* main_color, ImVec4& boxColor, int& taskesyRows, int& taskesyColumns, std::vector<const char*>& columnNames, std::vector<const char*>& text, std::vector<int>& numberColumn, const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::stringstream strStream;
	strStream << stream.rdbuf();

	YAML::Node data = YAML::Load(strStream.str());
	if (!data["Taskesy"])
		return;

	// Color
	if (!data["Main Color"])
		return;
	*main_color = ImVec4(data["Main Color"][0].as<float>(), data["Main Color"][1].as<float>(), data["Main Color"][2].as<float>(), data["Main Color"][3].as<float>());

	if (!data["Box Color"])
		return;
	boxColor = ImVec4(data["Box Color"][0].as<float>(), data["Box Color"][1].as<float>(), data["Box Color"][2].as<float>(), data["Box Color"][3].as<float>());

	// Table
	if (!data["Rows"])
		return;
	taskesyRows = data["Rows"].as<int>();

	if (!data["Columns"])
		return;
	taskesyColumns = data["Columns"].as<int>();

	if (!data["Column Names"])
		return;

	if (!data["Number of Boxes per Column"])
		return;

	if (!data["Box Text"])
		return;

	// If everything is fine, we load the table
	while (!columnNames.empty())
		columnNames.pop_back();
	while (!numberColumn.empty())
		numberColumn.pop_back();
	while (!text.empty())
		text.pop_back();

	std::string columnName;
	int numCols;
	std::string boxText;

	// Column Names
	for (int i = 0; i < taskesyColumns; ++i)
	{
		columnName = data["Column Names"][i].as<std::string>();
		columnNames.push_back(_strdup(columnName.c_str()));
		numCols = data["Number of Boxes per Column"][i].as<int>();
		numberColumn.push_back(numCols);
	}

	// Text boxes
	for (int column = 0; column < taskesyColumns; column++)
	{
		for (int row = 0; row < taskesyRows; row++)
		{
			if (data["Box Text"][row * taskesyColumns + column].as<std::string>() == "None")
				text.push_back("None");
			else
			{
				boxText = data["Box Text"][row * taskesyColumns + column].as<std::string>();
				text.push_back(_strdup(boxText.c_str()));
			}
		}
	}
}