#include "Recorder.h"

using namespace std;

Recorder::Recorder(string name, string fraction, char symbol,
                   int width, int heigth, int health, int damage, int cooldown,
                   int attackRadius, int speedDelay, int manaCount,
                   vector<string> spells, int cost, int eats, int productionTime, vector<string> production)
{
    this->name = name;
    this->fraction = fraction;
    this->symbol = symbol;
    this->width = width;
    this->heigth = heigth;
    this->health = health;
    this->damage = damage;
    this->cooldown = cooldown;
    this->attackRadius = attackRadius;
    this->speedDelay = speedDelay;
    this->manaCount = manaCount;
    this->spells.assign(spells.begin(), spells.end());
    this->production.assign(production.begin(), production.end());
    this->cost = cost;
    this->eats = eats;
    this->productionTime = productionTime;
}

int Recorder::printUnit()
{
    string directoryPath = "units/" + name + ".unit";
    ofstream out(directoryPath);
    if (out.fail())
    {
        cout << "Error while creating file, creating directory" << endl;
        if (CreateDirectory("units", NULL) != TRUE)
            return -1;
        out.clear();
        out.open(directoryPath);
    }
    cout << "Printing into file..." << endl;
    out << "unit " << name << "{    "
    << "beatyName: \"" << name << "\";    "
    << "fraction: \"" << fraction << "\";    "
    << "symbol: \'" << symbol << "\';    "
    << "width: " << width << ";    "
    << "heigth: " << heigth << ";    "
    << "health: " << health << ";    "
    << "damage: " << damage << ";    "
    << "cooldown: " << cooldown << ";    "
    << "attackRadius: " << attackRadius << ";    "
    << "speedDelay: " << speedDelay << ";    "
    << "mana: " << manaCount << ";    "
    << "spells: [";
    for (auto i = spells.begin(); i != spells.end(); i++)
    {
        if (i != spells.end() - 1)
            out << '"' << *i << "\", ";
        else
        {
            out << '"' << *i << '"';
        }
    }
    out << "];    "
    << "cost: " << cost << ";    "
    << "productionTime: " << productionTime << ";    " << "type: " << numberType << ';' << '}';
    out.close();
    return 1;
}

int Recorder::printSpell()
{
    string directoryPath = "spells/" + name + ".spell";
    ofstream out(directoryPath);
    if (out.fail())
    {
        cout << "Error while creating file, creating directory" << endl;
        if (CreateDirectory("spells", NULL) != TRUE)
            return -1;
        out.clear();
        out.open(directoryPath);
        //return -1;
    }
    cout << "Printing into file..." << endl;
    out << "spell " << name << "{    "
    << "beatyName: \"" << name << "\";    "
    << "type: " << type << ";    "
    << "symbol: \'" << symbol << "\';    "
    << "damage: " << damage << ";    "
    << "cooldown: " << cooldown << ";    "
    << "castCooldown: " << castCooldown << ";    "
    << "heal: " << heal << ";    "
    << "attackRadius: " << attackRadius << ";    " 
    << "cost: " << cost << ";    "
    << "productionTime: " << productionTime << ";"
        << '}';
    out.close();
    return 1;
}

int Recorder::printBuilding()
{
    string directoryPath = "buildings/" + name + ".building";
    ofstream out(directoryPath);
    if (out.fail())
    {
        cout << "Error while creating file, creating directory" << endl;
        if (CreateDirectory("buildings", NULL) != TRUE)
            return -1;
        out.clear();
        out.open(directoryPath);
        //return -1;
    }
    cout << "Printing into file..." << endl;
    out << "building " << name << "{    "
    << "beatyName: \"" << name << "\";    "
    << "" << "fraction: \"" << fraction << "\";    "
    << "symbol: \'" << symbol << "\';    "
    << "width: " << width << ";   "
    << "heigth: " << heigth << ";   "
    << "health: " << health << ";   "
    << "damage: " << damage << ";   "
    << "cooldown: " << cooldown << ";   "
    << "attackRadius: " << attackRadius << ";   "
    << "mana: " << manaCount << ";   "
    << "spells: [";
    for (auto i = spells.begin(); i != spells.end(); ++i)
    {
        if (i != spells.end() - 1)
            out << '"' << *i << "\", ";
        else
        {
            out << '"' << *i << '"';
        }
    }
    out << "];    "
    << "production: [";
    for (auto i = production.begin(); i != production.end(); ++i)
    {
        if (i != production.end() - 1)
            out << '"' << *i << "\", ";
        else
        {
            out << '"' << *i << '"';
        }
    }
    out << "];    "
    << "cost: " << cost << ";   "
    << "productionTime: " << productionTime << ';'
        << '}';
    out.close();
    return 1;
}

void Recorder::mainMenu()
{
    cout << "\n1. Create unit" << endl;
    cout << "2. Create spell" << endl;
    cout << "3. Create building" << endl;
    cout << "(0)     Exit" << endl
         << '\v';
    cout << "Choose your event : ";
}

void Recorder::menuInterface()
{
    string msg = "HELLO! Welcome to WCIIRemake GameMaker! Here you can create buildings, spells, units";
    cout << msg << endl;
    while (choice != 0)
    {
        mainMenu();
        clearVectors();
        choice = analyzeInput();
        switch (choice)
        {
        case 1:
            system("cls");
            subMenuInterface();
            printUnit();
            break;
        case 2:
            system("cls");
            subMenuInterface();
            printSpell();
            break;
        case 3:
            system("cls");
            subMenuInterface();
            printBuilding();
            break;
        case 0:
            cout << "Exitting...";
            exit(1);
        default:
            //menuInterface();//you have entered wrong menu item
            //Sleep(2000);
            system("cls");	//clear screen		//show menu again
            break;
        }
        system("cls");
    }
}

int main()
{
    Recorder a;
    a.menuInterface();
    return 0;
}

inline void Recorder::inputName()
{
    cout << "Input beauty name: ";
    getline(cin, name);
    cout << "You entered: " << name << endl;
}

inline void Recorder::inputFraction()
{
    cout << "Input fraction: ";
    getline(cin, fraction);
    cout << "You entered: " << fraction << endl;
}

inline void Recorder::inputType()
{
    cout << "Input type : ";
    getline(cin, type);
    cout << "You entered: " << type << endl;
}

inline void Recorder::clearVectors()
{
    spells.clear();
    production.clear();
}

inline void Recorder::inputWidth()
{
    width = analyzeInput();
}

inline void Recorder::inputHeight()
{
    heigth = analyzeInput();
}

inline void Recorder::inputHealth()
{
    health = analyzeInput();
}

inline void Recorder::inputCooldown()
{
    cooldown = analyzeInput();
}

inline void Recorder::inputCastCooldown()
{
    castCooldown = analyzeInput();
}

inline void Recorder::inputSpeedDelay()
{
    speedDelay = analyzeInput();
}

inline void Recorder::inputCost()
{
    cost = analyzeInput();
}

inline void Recorder::inputEats()
{
    eats = analyzeInput();
}

inline void Recorder::inputDamage()
{
    damage = analyzeInput();
}

inline void Recorder::inputProductionTime()
{
    productionTime = analyzeInput();
}

inline void Recorder::inputMana()
{
    manaCount = analyzeInput();
}

inline void Recorder::inputHeal()
{
    heal = analyzeInput();
}

inline void Recorder::inputAttackRadius()
{
    attackRadius = analyzeInput();
}

inline void Recorder::inputSymbol()
{
    cin >> symbol;
    cin.get();
}

void Recorder::inputSpells()
{
    cout << "(empty line for stop): ";
    string buffer;
    do
    {
        getline(cin, buffer);
        spells.push_back(buffer);
    } while (buffer != "");
    spells.pop_back();
}

void Recorder::inputProduction()
{
    cout << "(empty line for stop): ";
    string buffer;
    do
    {
        getline(cin, buffer);
        production.push_back(buffer);
    } while (buffer != "");
    production.pop_back();
}

int Recorder::analyzeInput()
{
    int value;
    while (!(cin >> value))
    {
        cout << "Please enter a valid integer" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.get();
    return value;
}

void Recorder::subMenuBuilding()
{
    cout << "\n1. Input beauty name ";
    if (name != "")
        cout << ':' <<name << endl;
    else
        cout << endl;
    cout << "2. Input symbol ";
    if (symbol != '#')
        cout << ':' <<symbol << endl;
    else
        cout << endl;
    cout << "3. Input fraction ";
    if (fraction != "")
        cout << ':' <<fraction << endl;
    else
        cout << endl;
    cout << "4. Input width ";
    if (width != 0)
        cout << ':' <<width << endl;
    else
        cout << endl;
    cout << "5. Input heigth ";
    if (heigth != 0)
        cout << ':' <<heigth << endl;
    else
        cout << endl;
    cout << "6. Input health ";
    if (health != 0)
        cout << ':' <<health << endl;
    else
        cout << endl;
    cout << "7. Input mana ";
    if (manaCount != 0)
        cout << ':' <<manaCount << endl;
    else
        cout << endl;
    cout << "8. Input spells " <<':';
    if (!spells.empty()){
        cout << '[';
        for (auto i = spells.begin(); i != spells.end(); ++i)
        {
            if (i != spells.end() - 1)
                cout << '"' << *i << "\", ";
            else
                cout << '"' << *i << '"';
        }
        cout << ']' << endl;
    }
    else
        cout << endl;
    cout << "9. Input damage ";
    if (damage != 0)
        cout << ':' <<damage << endl;
    else
        cout << endl;
    cout << "10. Input attack radius ";
    if (attackRadius != 0)
        cout << ':' <<attackRadius << endl;
    else
        cout << endl;
    cout << "11. Input cooldown ";
    if (cooldown != 0)
        cout << ':' <<cooldown << endl;
    else
        cout << endl;
    cout << "12. Input cost ";
    if (cost != 0)
        cout << ':' <<cost << endl;
    else
        cout << endl;
    cout << "13. Input production time ";
    if (productionTime != 0)
        cout << ':' <<productionTime << endl;
    else
        cout << endl;
    cout << "14. Input production " << ':';
    if (!production.empty())
    {
        cout << '[';
        for (auto i = production.begin(); i != production.end(); ++i)
        {
            if (i != production.end() - 1)
                cout << '"' << *i << "\", ";
            else
                cout << '"' << *i << '"';
        }
        cout << ']' << endl;
    }
    else
        cout << endl;
    cout << "15. Input name ";
    if (nameFact != " ")
        cout <<':' << nameFact << endl;
    else
        cout << endl;
    cout << "(0)     Quit to main menu" << endl
         << '\v';
    cout << "Choose your event : ";
}

void Recorder::subMenuSpell()
{
    cout << "\n1. Input beauty name ";
    if (name != "")
        cout <<':' << name << endl;
    else
        cout << endl;
    cout << "2. Input symbol ";
    if (symbol != '#')
        cout <<':' << symbol << endl;
    else
        cout << endl;
    cout << "3. Input type" << endl;
    if (type != "")
        cout << ':' <<type << endl;
    else
        cout << endl;
    cout << "4. Input damage ";
    if (damage != 0)
        cout << ':' <<damage << endl;
    else
        cout << endl;
    cout << "5. Input attack radius ";
    if (attackRadius != 0)
        cout << ':' <<attackRadius << endl;
    else
        cout << endl;
    cout << "6. Input cooldown ";
    if (cooldown != 0)
        cout << ':' <<cooldown << endl;
    else
        cout << endl;
    cout << "7. Input cost ";
    if (cost != 0)
        cout << ':' <<cost << endl;
    else
        cout << endl;
    cout << "8. Input production time ";
    if (productionTime != 0)
        cout << ':' <<productionTime << endl;
    else
        cout << endl;
    cout << "9. Input cast cooldown ";
    if (castCooldown != 0)
        cout << ':' <<castCooldown << endl;
    else
        cout << endl;
    cout << "10. Input heal ";
    if (heal != 0)
        cout << ':' <<heal << endl;
    else
        cout << endl;
    cout << "11. Input name ";
    if (name != "")
        cout <<':' << nameFact << endl;
    else
        cout << endl;
    cout << "(0)     Quit to main menu" << endl
         << '\v';
    cout << "Choose your event : ";
}

void Recorder::subMenuUnit()
{
    cout << "\n1. Input beauty name ";
    if (name != "")
        cout << ':' << name << endl;
    else
        cout << endl;
    cout << "2. Input symbol ";
    if (symbol != '#')
        cout <<  ':' <<symbol << endl;
    else
        cout << endl;
     cout << "3. Input fraction ";
    if (fraction != "")
        cout << ':' << fraction << endl;
    else
        cout << endl;
    cout << "4. Input width ";
    if (width != 0)
        cout <<  ':' <<width << endl;
    else
        cout << endl;
    cout << "5. Input heigth ";
    if (heigth != 0)
        cout <<   ':' <<heigth << endl;
    else
        cout << endl;
    cout << "6. Input health ";
    if (health != 0)
        cout <<  ':' << health << endl;
    else
        cout << endl;
    cout << "7. Input mana ";
    if (manaCount != 0)
        cout <<  ':' << manaCount << endl;
    else
        cout << endl;
    cout << "8. Input spells " << ':';
    if (!spells.empty()){
        cout << '[';
        for (auto i = spells.begin(); i != spells.end(); ++i)
        {
            if (i != spells.end() - 1)
                cout << '"' << *i << "\", ";
            else
                cout << '"' << *i << '"';
        }
        cout << ']' << endl;
    }
    else
        cout << endl;
    cout << "9. Input damage ";
    if (damage != 0)
        cout <<  ':' <<damage << endl;
    else
        cout << endl;
    cout << "10. Input attack radius ";
    if (attackRadius != 0)
        cout << ':' <<attackRadius << endl;
    else
        cout << endl;
    cout << "11. Input cooldown ";
    if (cooldown != 0)
        cout << ':' <<cooldown << endl;
    else
        cout << endl;
    cout << "12. Input cost ";
    if (cost != 0)
        cout << ':' <<cost << endl;
    else
        cout << endl;
    cout << "13. Input production time ";
    if (productionTime != 0)
        cout << ':' <<productionTime << endl;
    else
        cout << endl;
    cout << "14. Input speed delay ";
    if (speedDelay != 0)
        cout << ':' <<speedDelay << endl;
    else
        cout << endl;
    cout << "15. Input eat count ";
    if (eats != 0)
        cout << ':' <<eats << endl;
    else
        cout << endl;
     cout << "16. Input type ";
    if (numberType != 0)
        cout <<':' << numberType << endl;
    else
        cout << endl;
    cout << "17. Input name ";
    if (nameFact != "")
        cout <<':' << nameFact << endl;
    else
        cout << endl;
    cout << "(0)     Quit to main menu" << endl
         << '\v';
    cout << "Choose your event : ";
}

int Recorder::subMenuInterface()
{
    subMenuChoice = 1;
    while (subMenuChoice != 0)
    {
        if (choice == 1)
            subMenuUnit();
        if (choice == 2)
            subMenuSpell();
        if (choice == 3)
            subMenuBuilding();
        subMenuChoice = analyzeInput();
        switch (subMenuChoice)
        {
        case 1:
            inputName();
            break;
        case 2:
            inputSymbol();
            break;
        case 3:
            if (choice == 1 || choice == 3)
                inputFraction();
            if (choice == 2)
                inputType();
            break;
        case 4:
            if (choice == 1 || choice == 3)
                inputWidth();
            else
                inputDamage();
            break;
        case 5:
            if (choice == 1 || choice == 3)
                inputHeight();
            else
                inputAttackRadius();
            break;
        case 6:
            if (choice == 1 || choice == 3)
                inputHealth();
            else
                inputCooldown();
            break;
        case 7:
            if (choice == 1 || choice == 3)
                inputMana();
            else
                inputCost();
            break;
        case 8:
            if (choice == 1 || choice == 3)
                inputSpells();
            else
                inputProductionTime();
            break;
        case 9:
            if (choice == 1 || choice == 3)
                inputDamage();
            else
                inputCastCooldown();
            break;
        case 10:
            if (choice == 1 || choice == 3)
                inputAttackRadius();
            else
                inputHeal();
            break;
        case 11:
            if (choice == 1 || choice == 3)
                inputCooldown();
            if(choice == 2) {nameFact = ""; getline(cin, nameFact);}
            break;
        case 12:
            if (choice == 1 || choice == 3)
                inputCost();
            else
                break;
            break;
        case 13:
            if (choice == 1 || choice == 3)
                inputProductionTime();
            else
                break;
            break;
        case 14:
            if (choice == 1)
                inputSpeedDelay();
            else if (choice == 3)
                inputProduction();
            else
                break;
            break;
        case 15:
            if (choice == 1)
                inputEats();
            if(choice == 2) {nameFact = ""; getline(cin, nameFact);}
            break;
        case 16:
            if (choice == 1)
                numberType = analyzeInput();
            else
                break;
            break;
        case 17:
            if (choice == 1)
                getline(cin, nameFact);
            break;
        case 0:
            return 0;
        default:
            break;
        }
        system("cls");
    }
    return 0;
}