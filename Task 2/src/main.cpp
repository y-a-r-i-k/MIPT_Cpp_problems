#include <iostream>
#include <string>
#include <sstream>
#include <memory>
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
                    iss >> id >> name >> energy >> score;
                    auto scooter = std::make_unique<ElectricScooter>(id, name, energy, score);
                    fleet.add(std::move(scooter));
                }
                else if (type == "bike") {
                    std::string id, name;
                    int score;
                    iss >> id >> name >> score;
                    auto bike = std::make_unique<Bike>(id, name, score);
                    fleet.add(std::move(bike));
                }
                else if (type == "ebike") {
                    std::string id, name;
                    double energy;
                    int score;
                    iss >> id >> name >> energy >> score;
                    auto ebike = std::make_unique<EBike>(id, name, energy, score);
                    fleet.add(std::move(ebike));
                }
                else if (type == "helmet") {
                    std::string id, name;
                    iss >> id >> name;
                    auto helmet = std::make_unique<Helmet>(id, name);
                    fleet.add(std::move(helmet));
                }
                else if (type == "dock") {
                    std::string id, name;
                    double energy;
                    iss >> id >> name >> energy;
                    auto dock = std::make_unique<DockStation>(id, name, energy);
                    fleet.add(std::move(dock));
                }
                else {
                    throw InvalidCommand("unknown add type");
                }
            }
            else if (cmd == "energy") {
                std::cout << fleet.totalEnergy() << "\n";
            }
            else if (cmd == "novice") {
                fleet.printNovice(std::cout);
            }
            else if (cmd == "list") {
                fleet.printAll(std::cout);
            }
            else if (cmd == "focus") {
                std::string id;
                iss >> id;
                fleet.setFocus(id);
            }
            else if (cmd == "show_focus") {
                fleet.showFocus(std::cout);
            }
            else if (cmd == "remove") {
                std::string id;
                iss >> id;
                fleet.remove(id);
            }
            else {
                throw InvalidCommand("unknown command");
            }
        }
        catch (const FleetError& e) {
            std::cout << "error: " << e.what() << "\n";
        }
    }

    std::cout << "До свидания!\n";
    return 0;
}