#include "Knight.h"

// Matching the const string& signature
Knight::Knight(const string& name, int hp, int power, int armor, int charge)
    : Warrior(name, hp, power, armor), chargeBonus(charge) {}

// Adding the missing destructor definition
Knight::~Knight() {}

int Knight::getChargeBonus() const { return chargeBonus; }

int Knight::calculateBurstDamage() const {
    return getPower() + chargeBonus;
}