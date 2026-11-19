#include "Fleet.hpp"
#include "Errors.hpp"
#include "Transport.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>

static bool containsBroken(const std::string& name) {
  std::string lower = name;
  std::transform(lower.begin(), lower.end(), lower.begin(), 
                 [](unsigned char c) {return std::tolower(c);});
  return lower.find("broken") != std::string::npos;
}

void Fleet::add(std::shared_ptr<InventoryItem> item) {
    if (!item) {
        throw InvalidCommand("cannot add null item");
    }

    if (containsBroken(item->name())) {
        throw InspectionRejected("inspection rejected");
    }

    items_.push_back(std::move(item));
    recent_.add(items_.back().get());
}

void Fleet::setFocus(const std::string& id) {
    for (const auto& item : items_) {
        if (item->inventoryId() == id) {
            focus_ = item;
            return;
        }
    }
    focus_.reset();
}

double Fleet::totalEnergy() const {
  double totalEnergySum = 0;

  for (const auto& item : items_) {
    totalEnergySum += item->dailyEnergy();
  }

  return totalEnergySum;
}

void Fleet::printNovice(std::ostream& os) const {
    for (const auto& item : items_) {
        if (const Transport* transport = dynamic_cast<const Transport*>(item.get())) {
            if (transport->isNoviceFriendly()) {
                os << transport->name() << " " << transport->inventoryId() << "\n";
            }
        }
    }
}

void Fleet::printAll(std::ostream& os) const {
    std::vector<const InventoryItem*> sorted;
    sorted.reserve(items_.size());

    for (const auto& item : items_) {
        sorted.push_back(item.get());
    }

    std::sort(sorted.begin(), sorted.end(),
              [](const InventoryItem* a, const InventoryItem* b) {
                  return *a < *b;
              });

    for (const InventoryItem* item : sorted) {
        os << *item << "\n";
    }
}

void Fleet::setFocus(const std::string& id) {
    for (const auto& item : items_) {
        if (item->inventoryId() == id) {
            std::shared_ptr<InventoryItem> temp(item.get(), [](InventoryItem*) {});
            focus_ = temp;
            return;
        }
    }
    focus_.reset();
}

void Fleet::showFocus(std::ostream& os) const {
    if (auto locked = focus_.lock()) {
        os << *locked << "\n";
    } else {
        os << "removed\n";
    }
}

size_t Fleet::size() const {
  return items_.size();
}