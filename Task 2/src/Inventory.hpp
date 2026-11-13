#pragma once
#include <string>
#include <ostream>
#include <memory>

// Абстрактный базис всего, что стоит на балансе
class InventoryItem {
public:
    virtual ~InventoryItem() = default;

    virtual std::string inventoryId() const = 0;
    virtual std::string name() const = 0;
    virtual std::string describe() const = 0;

    // По умолчанию энергия = 0 (переопределяется у потребителей энергии)
    virtual double dailyEnergy() const { return 0.0; }

    // Для сортировки по инвентарному номеру
    bool operator<(const InventoryItem& other) const {
        return inventoryId() < other.inventoryId();
    }
};

// Объявление оператора вывода
std::ostream& operator<<(std::ostream& os, const InventoryItem& item);
