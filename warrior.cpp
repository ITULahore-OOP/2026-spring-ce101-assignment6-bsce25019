#include "Warrior.h"

Warrior::Warrior(string name, int hp, int power, int armor) 
    : Hero(name, hp, power), armorRating(armor) {}

int Warrior::getArmor() const { return armorRating; }

int Warrior::calculateEffectiveHealth() const {
    return getHealth() + (armorRating * 2);
}