#include "Hero.h"

Hero::Hero(const string& name, int hp, int power) : heroName(name), health(hp), basePower(power) {}
Hero::~Hero() {}

string Hero::getName() const { return heroName; }
int Hero::getHealth() const { return health; }
int Hero::getPower() const { return basePower; }

void Hero::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

bool Hero::operator>(const Hero &other) const {
    return this->basePower > other.basePower;
}

int Hero::operator+(const Hero &other) const {
    return this->health + other.health;
}