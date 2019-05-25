#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <limits>

using namespace std;

class Recorder
{
private:
    int choice;
    int subMenuChoice;
    int numberType;
    string name;
    string nameFact;
    string fraction;
    char symbol;
    int width;
    int heigth;
    int health;
    int damage;
    int cooldown;
    int attackRadius;
    int speedDelay;
    int manaCount;
    vector<string> spells;
    int cost;
    int eats;
    int productionTime;
    string type;               // for spell
    int heal;                  // for spell
    int castCooldown;          // for spell and building
    vector<string> production; // for building
    void mainMenu();
    int printUnit();
    int printSpell();
    int printBuilding();
    void inputName();
    void inputFraction();
    void inputType();
    void inputAttributes();
    void clearVectors();
    void inputWidth();
    void inputHeight();
    void inputHealth();
    void inputDamage();
    void inputCooldown();
    void inputCastCooldown();
    void inputSpeedDelay();
    void inputCost();
    void inputEats();
    void inputProductionTime();
    void inputSpells();
    void inputProduction();
    void inputMana();
    void inputHeal();
    void inputAttackRadius();
    void inputSymbol();
    int analyzeInput();
    void subMenuUnit();
    void subMenuSpell();
    void subMenuBuilding();
    int subMenuInterface();

public:
    Recorder()
    {
        numberType = 0;
        choice = -1;
        subMenuChoice = -1;
        symbol = '#';
        name = "";
        fraction = "";
        width = 0;
        heigth = 0;
        health = 0;
        damage = 0;
        cooldown = 0;
        attackRadius = 0;
        speedDelay = 0;
        manaCount = 0;
        spells = {};
        cost = 0;
        eats = 0;
        productionTime = 0;
        type = "";               // for spell
        heal = 0;                  // for spell
        castCooldown = 0;          // for spell and building
        production = {}; // for building
    }
    Recorder(string name, string fraction, char symbol,
             int width, int heigth, int health, int damage, int cooldown,
             int attackRadius, int speedDelay, int manaCount,
             vector<string> spells, int cost, int eats, int productionTime, vector<string> production);
    void menuInterface();
};