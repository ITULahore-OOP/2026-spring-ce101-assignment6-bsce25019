#include "MagicalEntity.h"

MagicalEntity::MagicalEntity(int mana, int spell) : manaPool(mana), spellPower(spell) {}

int MagicalEntity::getMana() const { return manaPool; }
int MagicalEntity::getSpellPower() const { return spellPower; }