#pragma once

#include <unordered_map>
#include <variant>

namespace n_var_exporter {
	namespace n_detail {
		inline std::unordered_map<std::string, std::variant<int, float, bool, std::string>> values;
	}

	template <class T>
	T get(std::string_view key) {
		return std::get<T>(n_detail::values[key.data()]);
	}
	
	template<typename T>
	void set(std::string_view key, T value) {
		n_detail::values[key.data()] = value;
	}

	void save(std::string_view file_name);
	void load(std::string_view file_name);
}

#define ADD(type, name, value) \
	n_var_exporter::set<type>(name, value);

#define SAVE(file_name) \
	n_var_exporter::save(file_name);

#define LOAD(file_name) \
	n_var_exporter::load(file_name);