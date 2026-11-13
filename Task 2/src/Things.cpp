#include "Things.hpp"
#include "Errors.hpp"

Helmet::Helmet(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name))
{
  if (id_.empty()) {
    throw InvalidCommand("id must not be empty");
  }
}

std::string Helmet::inventoryId() const {
  return id_;
}

std::string Helmet::name() const {
  return name_;
}

std::string Helmet::describe() const {
  return "шлем " + name() + " (" + inventoryId() + ")";
}

DockStation::DockStation (std::string id, std::string name, double energy)
  : id_(std::move(id)), name_(std::move(name)), energyPerDay_(energy) 
{
  if (energy < 0) {
    throw InvalidCommand("energy cannot be negative");
  }
}

std::string DockStation::inventoryId() const {
  return id_;
}

std::string DockStation::name() const {
  return name_;
}

std::string DockStation::describe() const {
  return "док-станция " + name() + " (" + inventoryId() + ")";
}