#include <iostream>
#include "include/var_exporter.hpp"
#include <Windows.h>

void call_save() {
    SET(bool, "bool_example", true);
    SET(int, "integer_example", 110);
    SET(float, "float_example", 521.f);
    SET(std::string, "string_example", "string_example");

    n_var_exporter::save("test");
}

void call_clear() {
    if (!n_var_exporter::n_detail::values.empty())
        n_var_exporter::n_detail::values.clear();

    printf("cleared unordered map \n");
}

void create_variables() {
    SET(bool, "bool_example", false);
    SET(int, "integer_example", 0);
    SET(float, "float_example", 0.f);
    SET(std::string, "string_example", "empty");
}

void call_load() {
    n_var_exporter::load("test");

    std::cout << "bool_example " << GET(bool, "bool_example") << "\n";
    std::cout << "float_example " << GET(float, "float_example") << "\n";
    std::cout << "int_example " << GET(int, "int_example") << "\n";
    std::cout << "string_example " << GET(std::string, "string_example") << "\n";
    std::cout << "values_size " << n_var_exporter::n_detail::values.size() << "\n";


    if (GET(bool, "bool_example")) {
        std::cout << "bool_example " << GET(bool, "bool_example") << "\n";
    }
}

int main() {
    create_variables(); //add variables to map (requires being called once upon initialisation)

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
