#include "Inventory.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
    os << item.name() << " " << item.inventoryId();
    return os;
}
