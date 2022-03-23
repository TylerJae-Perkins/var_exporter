#include "var_exporter.hpp"

#include <shlobj.h>
#include <filesystem>
#include <fstream>

void n_var_exporter::save(std::string_view file_name) {
	std::filesystem::path file(file_name);
	if (file.extension() != ".cfg")
		file.replace_extension(".cfg");


	CHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string file_path = std::string(buffer).substr(0, pos);

	std::filesystem::path path = file_path / file;

	std::ifstream stream_file;
	stream_file.open(path, std::ios::out | std::ios::app);



	stream_file.close();
}

void n_var_exporter::load(std::string_view file_load) {

}