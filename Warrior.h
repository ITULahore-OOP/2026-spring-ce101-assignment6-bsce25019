#ifndef WARRIOR_H
#define WARRIOR_H
#include "Hero.h"
#include <string>
using namespace std;

class Warrior : public Hero {
private:
    int armorRating;

public:
    Warrior(string name, int hp, int power, int armor);
    int getArmor() const;
    int calculateEffectiveHealth() const;
};

#endif