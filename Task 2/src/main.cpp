#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>

#include "Fleet.hpp"
#include "Transport.hpp"
#include "Things.hpp"
#include "Errors.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Fleet fleet;

    // Общая спецификация модели (shared_ptr)
    auto modelX = std::make_shared<ModelSpec>();
    modelX->modelName = "ModelX";
    modelX->manufacturer = "Физтех";
    modelX->year = 2024;

    std::cout << "ФизКат — система учёта парка\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        try {
            if (cmd == "quit" || cmd == "exit") {
                break;
            }
            else if (cmd == "add") {
                std::string type;
                iss >> type;

                if (type == "scooter") {
                    std::string id, name;
                    double energy;
                    int score;
                    if (!(iss >> id >> name >> energy >> score)) {
                        throw InvalidCommand("invalid arguments for scooter");
                    }
                    auto scooter = std::make_shared<ElectricScooter>(id, name, energy, score, modelX);
                    fleet.add(scooter);
                }
                else if (type == "bike") {
                    std::string id, name;
                    int score;
                    if (!(iss >> id >> name >> score)) {
                        throw InvalidCommand("invalid arguments for bike");
                    }
                    auto bike = std::make_shared<Bike>(id, name, score);
                    fleet.add(bike);
                }
                else if (type == "ebike") {
                    std::string id, name;
                    double energy;
                    int score;
                    if (!(iss >> id >> name >> energy >> score)) {
                        throw InvalidCommand("invalid arguments for ebike");
                    }
                    auto ebike = std::make_shared<EBike>(id, name, energy, score, modelX);
                    fleet.add(ebike);
                }
                else if (type == "helmet") {
                    std::string id, name;
                    if (!(iss >> id >> name)) {
                        throw InvalidCommand("invalid arguments for helmet");
                    }
                    auto helmet = std::make_shared<Helmet>(id, name);
                    fleet.add(helmet);
                }
                else if (type == "dock") {
                    std::string id, name;
                    double energy;
                    if (!(iss >> id >> name >> energy)) {
                        throw InvalidCommand("invalid arguments for dock");
                    }
                    auto dock = std::make_shared<DockStation>(id, name, energy);
                    fleet.add(dock);
                }
                else if (type == "powerbank") {
                    std::string id, name;
                    double energy;
                    if (!(iss >> id >> name >> energy)) {
                        throw InvalidCommand("invalid arguments for powerbank");
                    }
                    auto pb = std::make_shared<PowerBank>(id, name, energy);
                    fleet.add(pb);
                }
                else {
                    throw InvalidCommand("unknown add type");
                }
            }
            else if (cmd == "energy") {
                std::cout << std::fixed << std::setprecision(1) << fleet.totalEnergy() << "\n";
            }
            else if (cmd == "novice") {
                fleet.printNovice(std::cout);
            }
            else if (cmd == "list") {
                fleet.printAll(std::cout);
            }
            else if (cmd == "focus") {
                std::string id;
                if (!(iss >> id)) {
                    throw InvalidCommand("focus requires id");
                }
                fleet.setFocus(id);
            }
            else if (cmd == "show_focus") {
                fleet.showFocus(std::cout);
            }
            else if (cmd == "remove") {
                std::string id;
                if (!(iss >> id)) {
                    throw InvalidCommand("remove requires id");
                }
                fleet.remove(id);
            }
            else if (cmd == "count") {
                std::cout << fleet.size() << "\n";
            }
            else {
                throw InvalidCommand("unknown command");
            }
        }
        catch (const FleetError& e) {
            std::cout << "error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "error: " << e.what() << "\n";
        }
    }

    std::cout << "До свидания!\n";
    return 0;
}