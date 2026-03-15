#ifndef SPELLBLADE_H
#define SPELLBLADE_H
#include "Warrior.h"
#include "MagicalEntity.h"

class Spellblade : public Warrior, public MagicalEntity {
public:
Spellblade(const string& name, int hp, int power, int armor, int mana, int spell);
    int calculateHybridDamage() const;
};

#endif