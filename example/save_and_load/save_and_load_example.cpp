#include <iostream>
#include "var_exporter/var_exporter.hpp"
#include <Windows.h>

void call_save() {
    ADD(bool, "bool_example", true);
    ADD(int, "integer_example", 110);
    ADD(float, "float_example", 521.f);
    ADD(std::string, "string_example", "sexy beast");

    SAVE("test");
}

void call_clear() {
    if (!n_var_exporter::n_detail::values.empty())
        n_var_exporter::n_detail::values.clear();

    printf("cleared unordered map \n");
}

void call_load() {
    LOAD("test");

    std::cout << "bool_example " << n_var_exporter::get<bool>("bool_example") << "\n";
    std::cout << "float_example " << n_var_exporter::get<float>("float_example") << "\n";
    std::cout << "int_example " << n_var_exporter::get<int>("int_example") << "\n";
    std::cout << "string_example " << n_var_exporter::get<std::string>("string_example") << "\n";
    std::cout << "values_size " << n_var_exporter::n_detail::values.size() << "\n";
}

int main()
{
    while (true) {
        if ((GetAsyncKeyState('V') & 1)) {
            call_save();
        }

        if ((GetAsyncKeyState('B') & 1)) {
            call_clear();
        }

        if ((GetAsyncKeyState('N') & 1)) {
            call_load();
        }
    }
}