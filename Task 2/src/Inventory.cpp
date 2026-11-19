#include "Inventory.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
    os << item.inventoryId() << " " << item.name();
    return os;
}