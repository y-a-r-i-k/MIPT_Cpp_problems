#pragma once
#include <stdexcept>
#include <string>

// Базовый класс исключений парка
class FleetError : public std::runtime_error {
public:
    explicit FleetError(const std::string& msg) : std::runtime_error(msg) {}
};

// Отказ техосмотра
class InspectionRejected : public FleetError {
public:
    explicit InspectionRejected(const std::string& msg = "inspection rejected")
        : FleetError(msg) {}
};

// Некорректная команда или аргументы
class InvalidCommand : public FleetError {
public:
    explicit InvalidCommand(const std::string& msg = "invalid command")
        : FleetError(msg) {}
};
