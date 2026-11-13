#pragma once

#include "Inventory.hpp"
#include "EnergyConsumer.hpp"
#include <string>

// Базвоый класс для транспорта
class Transport : public InventoryItem {
protected:
    std::string id_;
    std::string name_;
    int simplicityScore_;

public:
    Transport(std::string id, std::string name, int score);

    std::string inventoryId() const override;
    std::string name() const override;
    std::string describe() const override;

    int getSimplicityScore() const;
    bool isNoviceFriendly() const;
};

class Bike : public Transport {
public:
    Bike(std::string id, std::string name, int score);
};

class ElectricScooter : public Transport, public EnergyConsumer {
private:
    double energyPerDay_;

public:
    ElectricScooter(std::string id, std::string name, double energy, int score);

    double dailyEnergy() const override;
    std::string describe() const override;
};

class EBike : public Transport, public EnergyConsumer {
private:
    double energyPerDay_;

public:
    EBike(std::string id, std::string name, double energy, int score);

    double dailyEnergy() const override;
    std::string describe() const override;
};