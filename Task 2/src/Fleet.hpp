#pragma once

#include "Inventory.hpp"
#include <vector>
#include <memory>
#include <string>

class Fleet {
private:
    std::vector<std::unique_ptr<InventoryItem>> items_;
    std::weak_ptr<InventoryItem> focus_;

public:
    void add(std::unique_ptr<InventoryItem> item);
    bool remove(const std::string& id);

    double totalEnergy() const;
    void printNovice(std::ostream& os) const;
    void printAll(std::ostream& os) const;

    void setFocus(const std::string& id);
    void showFocus(std::ostream& os) const;

    size_t size() const;
};