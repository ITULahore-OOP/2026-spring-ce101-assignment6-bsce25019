#include "Guild.h"
#include "Hero.h"
#include "Knight.h"
#include "Spellblade.h"
#include "Warrior.h"

#include <iostream>
#include <string>

using namespace std;

const int kMaxRecruits = 64;

struct HeroRecord {
    Hero* hero = nullptr;
    string type;
};

int readInt(const string& prompt, int minValue, int maxValue) {
    while (true) {
        cout << prompt;
        int value{};
        if ((cin >> value) && value >= minValue && value <= maxValue) {
            cin.ignore(1024, '\n');
            return value;
        }
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Please enter a number between " << minValue << " and " << maxValue << ".\n";
    }
}

string readLine(const string& prompt) {
    string value;
    do {
        cout << prompt;
        getline(cin, value);
    } while (value.empty());
    return value;
}

void listRecruits(const HeroRecord recruits[], int recruitCount) {
    if (recruitCount == 0) {
        cout << "No recruits on the roster yet. Recruit someone first.\n";
        return;
    }

    cout << "\nCurrent recruits:\n";
    for (int index = 0; index < recruitCount; ++index) {
        const HeroRecord& record = recruits[index];
        cout << (index + 1) << ") [" << record.type << "] " << record.hero->getName()
             << " (HP: " << record.hero->getHealth() << ", Power: " << record.hero->getPower();

        if (record.type == "Warrior" || record.type == "Knight" || record.type == "Spellblade") {
            Warrior* warrior = static_cast<Warrior*>(record.hero);
            cout << ", Armor: " << warrior->getArmor();
        }

        if (record.type == "Knight") {
            Knight* knight = static_cast<Knight*>(record.hero);
            cout << ", Charge: " << knight->getChargeBonus();
        }

        if (record.type == "Spellblade") {
            Spellblade* spellblade = static_cast<Spellblade*>(record.hero);
            cout << ", Mana: " << spellblade->getMana()
                 << ", Spell Power: " << spellblade->getSpellPower()
                 << ", Hybrid: " << spellblade->calculateHybridDamage();
        }

        cout << ")\n";
    }
}

void registerHero(HeroRecord recruits[], int& recruitCount, Hero* hero, const string& type) {
    if (recruitCount >= kMaxRecruits) {
        cout << "Roster has reached its limit. Reassignment denied.\n";
        delete hero;
        return;
    }

    recruits[recruitCount].hero = hero;
    recruits[recruitCount].type = type;
    ++recruitCount;
}

void recruitHero(HeroRecord recruits[], int& recruitCount) {
    const string name = readLine("\nHero name: ");
    const int hp = readInt("Base health (1-9999): ", 1, 9999);
    const int power = readInt("Base power (0-9999): ", 0, 9999);

    registerHero(recruits, recruitCount, new Hero(name, hp, power), "Hero");
    cout << name << " joins the training grounds as a plain hero.\n";
}

void recruitWarrior(HeroRecord recruits[], int& recruitCount) {
    const string name = readLine("\nWarrior name: ");
    const int hp = readInt("Warrior health (1-9999): ", 1, 9999);
    const int power = readInt("Warrior power (0-9999): ", 0, 9999);
    const int armor = readInt("Armor rating (0-500): ", 0, 500);

    registerHero(recruits, recruitCount, new Warrior(name, hp, power, armor), "Warrior");
    cout << name << " is now shielding our cause with " << armor << " armor.\n";
}

void recruitKnight(HeroRecord recruits[], int& recruitCount) {
    const string name = readLine("\nKnight name: ");
    const int hp = readInt("Knight health (1-9999): ", 1, 9999);
    const int power = readInt("Knight power (0-9999): ", 0, 9999);
    const int armor = readInt("Knight armor (0-500): ", 0, 500);
    const int charge = readInt("Charge bonus (0-500): ", 0, 500);

    registerHero(recruits, recruitCount, new Knight(name, hp, power, armor, charge), "Knight");
    cout << name << " rides in with a charge bonus of " << charge << ".\n";
}

void recruitSpellblade(HeroRecord recruits[], int& recruitCount) {
    const string name = readLine("\nSpellblade name: ");
    const int hp = readInt("Spellblade health (1-9999): ", 1, 9999);
    const int power = readInt("Spellblade power (0-9999): ", 0, 9999);
    const int armor = readInt("Spellblade armor (0-500): ", 0, 500);
    const int mana = readInt("Mana pool (0-9999): ", 0, 9999);
    const int spell = readInt("Spell power (0-9999): ", 0, 9999);

    registerHero(recruits, recruitCount,
                 new Spellblade(name, hp, power, armor, mana, spell),
                 "Spellblade");
    cout << name << " bounds onto the field with fire and steel.\n";
}

void assignToGuild(Guild& guild, const HeroRecord recruits[], int recruitCount) {
    if (recruitCount == 0) {
        cout << "You need recruits before assigning anyone to the guild.\n";
        return;
    }

    listRecruits(recruits, recruitCount);
    const int choice = readInt("Select hero number to assign to the guild: ", 1, recruitCount);
    guild += recruits[choice - 1].hero;
    cout << recruits[choice - 1].hero->getName() << " now serves the guild proudly.\n";
}

void showMenu() {
    cout << "\n=== Guild Manager Menu ===\n"
         << "1) Recruit a Hero\n"
         << "2) Recruit a Warrior\n"
         << "3) Recruit a Knight\n"
         << "4) Recruit a Spellblade\n"
         << "5) List all recruits\n"
         << "6) Create or rename the guild\n"
         << "7) Assign a recruit to the guild\n"
         << "8) Inspect the guild\n"
         << "9) Exit\n";
}

int main() {
    HeroRecord recruits[kMaxRecruits];
    int recruitCount = 0;
    Guild* guild = nullptr;
    bool running = true;

    while (running) {
        showMenu();
        const int option = readInt("Choose an option (1-9): ", 1, 9);

        switch (option) {
            case 1:
                recruitHero(recruits, recruitCount);
                break;
            case 2:
                recruitWarrior(recruits, recruitCount);
                break;
            case 3:
                recruitKnight(recruits, recruitCount);
                break;
            case 4:
                recruitSpellblade(recruits, recruitCount);
                break;
            case 5:
                listRecruits(recruits, recruitCount);
                break;
            case 6: {
                const string name = readLine("\nGuild name: ");
                delete guild;
                guild = new Guild(name);
                cout << name << " is ready to rally heroes.\n";
                break;
            }
            case 7:
                if (guild) {
                    assignToGuild(*guild, recruits, recruitCount);
                } else {
                    cout << "Create a guild before assigning recruits.\n";
                }
                break;
            case 8:
                if (guild) {
                    guild->displayGuildStats();
                    cout << *guild;
                } else {
                    cout << "No guild exists yet. Create one first.\n";
                }
                break;
            case 9:
                cout << "Farewell! Your guild stands ready.\n";
                running = false;
                break;
            default:
                cout << "Unexpected choice; try again.\n";
                break;
        }
    }

    delete guild;
    for (int i = 0; i < recruitCount; ++i) {
        delete recruits[i].hero;
        recruits[i].hero = nullptr;
    }

    return 0;
}
