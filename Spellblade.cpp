#include "Spellblade.h"

Spellblade::Spellblade(const string& name, int hp, int power, int armor, int mana, int spell)
    : Warrior(name, hp, power, armor), MagicalEntity(mana, spell) {}

int Spellblade::calculateHybridDamage() const {
    return getPower() + getSpellPower();
}