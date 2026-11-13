#pragma once

// Абстрактный базис потребителя энергии
class EnergyConsumer {
public:
    virtual ~EnergyConsumer() = default;
    virtual double dailyEnergy() const = 0;
};
