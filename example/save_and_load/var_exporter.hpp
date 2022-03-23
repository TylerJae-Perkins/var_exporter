#pragma once

#include <any>
#include <unordered_map>
#include <variant>

namespace n_var_exporter {
	template <class T>
	T get(std::string_view key) {
		return std::get<T>(detail::values[key.data()]);
	}
	
	template<typename T>
	void set(std::string_view key, const T& value) {
		detail::values[key.data()] = value;
	}

	namespace n_detail {
		inline std::unordered_map<std::string, std::variant<int, float, bool, std::string>> values;
	}

	void save(std::string_view file_name);
	void load(std::string_view file_name);
}

#define ADD(type, name, value) \
	n_var_exporter::set<type>(name, value);