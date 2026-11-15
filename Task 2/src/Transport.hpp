#pragma once

#include "Inventory.hpp"
#include "EnergyConsumer.hpp"

#include <string>
#include <memory>

struct ModelSpec {
    std::string modelName;
    std::string manufacturer;
    int year = 2024;
};

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
    std::shared_ptr<ModelSpec> spec_;

public:
    ElectricScooter(std::string id, std::string name, double energy, int score,
                    std::shared_ptr<ModelSpec> spec = nullptr);

    double dailyEnergy() const override;
    std::string describe() const override;
};

class EBike : public Transport, public EnergyConsumer {
private:
    double energyPerDay_;
    std::shared_ptr<ModelSpec> spec_;

public:
    EBike(std::string id, std::string name, double energy, int score,
          std::shared_ptr<ModelSpec> spec = nullptr);

    double dailyEnergy() const override;
    std::string describe() const override;
};

class PowerBank : public InventoryItem, public EnergyConsumer {
private:
    std::string id_;
    std::string name_;
    double energyPerDay_;

public:
    PowerBank(std::string id, std::string name, double energy);

    std::string inventoryId() const override;
    std::string name() const override;
    std::string describe() const override;
    double dailyEnergy() const override;
};