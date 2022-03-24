#pragma once

#include <unordered_map>
#include <variant>

namespace n_var_exporter {
	namespace n_detail {
		inline std::unordered_map<std::string, std::variant<int, float, bool, std::string>> values;
	}

	template <typename T>
	T get(std::string_view key) {
		return std::get<T>(n_detail::values[key.data()]);
	}
	
	template<typename T>
	void set(std::string_view key, const T& value) {
		n_detail::values[key.data()] = value;
	}

	void save(std::string_view file_name);
	void load(std::string_view file_name);
}

#define SET(type, name, value) \
	n_var_exporter::set<type>(name, value);

#define GET(type, name) \
	n_var_exporter::get<type>(name)