#ifdef SHOULD_LOG
#define LOG(str, ...) printf(str, __VA_ARGS__)
#else
#define LOG(str) 
#endif

#include "var_exporter.hpp"

#include <shlobj.h>
#include <filesystem>
#include <fstream>
#include <iostream>

void n_var_exporter::save(std::string_view file_name) {
	std::filesystem::path file(file_name);
	if (file.extension() != ".cfg")
		file.replace_extension(".cfg");

	char folder_buffer[MAX_PATH] = { 0 };
	if (GetModuleFileNameA(NULL, folder_buffer, MAX_PATH) == 0)
		LOG("failed to save file {GetModuleFileNameA} \n");

	std::string::size_type last_backspace_pos = std::string(folder_buffer).find_last_of("\\/");
	std::string file_path = std::string(folder_buffer).substr(0, last_backspace_pos);

	std::filesystem::path path = file_path / file;

	std::ofstream stream_file;
	stream_file.open(path, std::ios::trunc);

	if (!stream_file.good()) {
		LOG("failed to save file {stream_file.good} \n");
		return;
	}

	for (std::pair<const std::string, std::variant<int, float, bool, std::string>>& data : n_detail::values) {
		std::visit([&](std::variant<int, float, bool, std::string>&& data_variant) {
			if (std::holds_alternative<int>(data_variant)) {
				int value = std::get<int>(data_variant);
				stream_file << "int; " << data.first.data() << ": " << std::to_string(value) << "\n";
			}
			else if (std::holds_alternative<float>(data_variant)) {
				float value = std::get<float>(data_variant);
				stream_file << "float; " << data.first.data() << ": " << std::to_string(value) << "\n";
			}
			else if (std::holds_alternative<bool>(data_variant)) {
				bool value = std::get<bool>(data_variant);
				stream_file << "bool; " << data.first.data() << ": " << std::to_string(value) << "\n";
			}
			else if (std::holds_alternative<std::string>(data_variant)) {
				std::string_view value = std::get<std::string>(data_variant);
				stream_file << "string; " << data.first.data() << ": " << value << "\n";
			}
		}, data.second);
	}
	stream_file.close();

	LOG("saved file %s \n", file_name.data());
}

void n_var_exporter::load(std::string_view file_name) {
	std::filesystem::path file(file_name);
	if (file.extension() != ".cfg")
		file.replace_extension(".cfg");

	char folder_buffer[MAX_PATH] = { 0 };
	if (GetModuleFileNameA(NULL, folder_buffer, MAX_PATH) == 0)
		LOG("failed to load file {GetModuleFileNameA} \n");

	std::string::size_type last_backspace_pos = std::string(folder_buffer).find_last_of("\\/");
	std::string file_path = std::string(folder_buffer).substr(0, last_backspace_pos);

	std::filesystem::path path = file_path / file;

	std::ifstream stream_file;

	stream_file.open(path, std::ios::in);

	if (!stream_file.good()) {
		LOG("failed to load file {stream_file.good} \n");
		return;
	}

	for (std::string line; std::getline(stream_file, line); ) {
		std::string value = line;

		size_t colon_pos = value.find(":");
		size_t semicolon_pos = value.find(";");

		std::string datatype = value;
		datatype.erase(semicolon_pos, datatype.size() - 1);

		std::string variable = value;
		variable.erase(0, colon_pos + 2);

		value.erase(0, semicolon_pos + 2);
		colon_pos = value.find(":");
		value.erase(colon_pos, value.size() - 1);

		if (datatype == "int") {
			int int_value = std::stoi(variable);
			set<int>(value, int_value);
		}

		if (datatype == "float") {
			float float_value = std::stof(variable);
			set<float>(value, float_value);
		}

		if (datatype == "bool") {
			int int_value = std::stoi(variable);
			set<bool>(value, int_value);
		}

		if (datatype == "string")
			set<std::string>(value, variable);

		datatype.clear();
		variable.clear();
		value.clear();
	}

	stream_file.close();

	LOG("loaded file %s \n", file_name.data());
}