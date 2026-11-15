#include "Transport.hpp"
#include "Errors.hpp"

Transport::Transport(std::string id, std::string name, int score)
    : id_(std::move(id)), name_(std::move(name)), simplicityScore_(score)
{
    if (simplicityScore_ < 1 || simplicityScore_ > 10) {
        throw InvalidCommand("simplicity score must be in range 1..10");
    }
}

std::string Transport::inventoryId() const {
  return id_;
}

std::string Transport::name() const {
  return name_;
}

std::string Transport::describe() const {
  return "транспорт";
}

int Transport::getSimplicityScore() const {
  return simplicityScore_;
}

bool Transport::isNoviceFriendly() const {
  return (simplicityScore_ >= 6);
}


Bike::Bike (std::string id, std::string name, int score)
  : Transport(std::move(id), std::move(name), score) {}

ElectricScooter::ElectricScooter(std::string id, std::string name, double energy, int score,
                                 std::shared_ptr<ModelSpec> spec)
    : Transport(std::move(id), std::move(name), score),
      energyPerDay_(energy),
      spec_(std::move(spec))
{
    if (energyPerDay_ < 0) {
        throw InvalidCommand("energy cannot be negative");
    }
}

double ElectricScooter::dailyEnergy() const {
  return energyPerDay_;
}

std::string ElectricScooter::describe() const {
  return "электросамокат " + name() + " (" + inventoryId() + ")";
}

EBike::EBike(std::string id, std::string name, double energy, int score,
                                 std::shared_ptr<ModelSpec> spec)
    : Transport(std::move(id), std::move(name), score),
      energyPerDay_(energy),
      spec_(std::move(spec))
{
    if (energyPerDay_ < 0) {
        throw InvalidCommand("energy cannot be negative");
    }
}

double EBike::dailyEnergy() const {
  return energyPerDay_;
}

std::string EBike::describe() const {
  return "электровелосипед " + name() + " (" + inventoryId() + ")";
}