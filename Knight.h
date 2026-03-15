#ifndef KNIGHT_H
#define KNIGHT_H
#include "Warrior.h"

class Knight : public Warrior {
private:
    int chargeBonus;

public:
    Knight(const string& name, int hp, int power, int armor, int charge);
    
    ~Knight();

    int getChargeBonus() const;
    int calculateBurstDamage() const;
};

#endif // KNIGHT_H