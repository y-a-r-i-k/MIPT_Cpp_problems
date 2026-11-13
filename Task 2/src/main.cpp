#include <iostream>
#include <string>
#include "Errors.hpp"
#include "Inventory.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "ФизКат — система учёта парка\n";
    std::cout << "Введите команду (пока только quit):\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "quit" || line == "exit" || line == "0") {
            break;
        }
        try {
            // Здесь позже будет разбор команд
            std::cout << "Неизвестная команда: " << line << "\n";
        } catch (const FleetError& e) {
            std::cout << "error: " << e.what() << "\n";
        }
    }

    std::cout << "До свидания!\n";
    return 0;
}