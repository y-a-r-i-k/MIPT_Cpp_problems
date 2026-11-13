#pragma once

#include "Inventory.hpp"
#include "EnergyConsumer.hpp"
#include <string>

class Helmet : public InventoryItem {
private:
    std::string id_;
    std::string name_;

public:
    Helmet(std::string id, std::string name);

    std::string inventoryId() const override;
    std::string name() const override;
    std::string describe() const override;
};

class DockStation : public InventoryItem, public EnergyConsumer {
private:
    std::string id_;
    std::string name_;
    double energyPerDay_;

public:
    DockStation(std::string id, std::string name, double energy);

    std::string inventoryId() const override;
    std::string name() const override;
    std::string describe() const override;

    double dailyEnergy() const override;
};