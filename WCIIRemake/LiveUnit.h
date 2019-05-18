#pragma once
#include "Unit.h"
#include "AttackTHREAD.h"
#include "FileWriter.h"
#include "Eventable.h"

struct LiveUnitPreset {
public:
	string name;
	string beautyName;
	string fraction;
	char symbol;
	int width;
	int heigth;
	int health;
	int damage;
	int cooldown;
	int attackRadius;
	int speedDelay;
	int mana;
    vector <string> spells;
	int cost;
	int eats;
	int productionTime;
public:
	LiveUnitPreset(string name, string beautyName, string fraction, char symbol, int width, int heigth, int health, int damage, int cooldown, int attackRadius, int speedDelay, int mana, vector <string> spells, int cost, int eats, int productionTime);
	LiveUnitPreset() : LiveUnitPreset("default", "Dafault", "Alliance", 'd', 1, 1, 100, 30, 1000, 5, 1000, 100, vector<string>(), 100, 1, 10000) {}
	~LiveUnitPreset();
	void print();
};

class LiveUnit : public Unit {
private:
	cordScr moveDest;
//	ThreadId MoveToTHRDDescriptor;
	ThreadId AttackTHRDDescriptor;
	time_t lastAttackTime;
	time_t cooldown; // cooldown between attacks
	time_t moveSpeed; // cooldown between steps
	int attackPower;
public:
	bool moveNoAttack;
public:
	LiveUnit(char value, int type, Field* field, int health, int team, int attackLength, time_t cooldown, time_t moveSpeed, int attackPower);
	LiveUnit(LiveUnitPreset preset, Field* field, int team) : LiveUnit(preset.symbol, 1, field, preset.health, team, preset.attackRadius, preset.cooldown, preset.speedDelay, preset.damage) {}
	LiveUnit() : LiveUnit('d', 1, NULL, 100, 0, 0, 1000, 1000, 40) {}
	~LiveUnit();
	cordScr* getMoveDest();
	bool goTo(cordScr* dest, bool & flag);
	bool attack(bool & flag); // attacks the available nearby unit, flag for checking if thread not stopped
	time_t getLastAttackTime();
	bool setLastAttackTime(time_t iclock);
	time_t getCooldown();
private:
	int findPath(cordScr destC); // запустить поиск пути(в процессе)
	int move(int direction); //подвинуться на поле, direction: 1-up,2-down,3-rigth,4-left,5-up right,6-up left,7-down right,8-down left;
	virtual void stopAllThreads();
protected:
	virtual void fillEventPatterns();
public: //LIVEUNIT EVENTS
	static void tpToCordsCommand(Command_c* command, Eventable* oParent);
	static void moveToCordsCommand(Command_c* command, Eventable* oParent);
	static void attackToCordsCommand(Command_c* command, Eventable* oParent);
	static void stopThreadsCommand(Command_c* command, Eventable* oParent);
	static void writeToCommand(Command_c* command, Eventable* oParent);
	

};

// tp id [int:id] to [int:x] [int:y]
// move id [int:id] to [int:x] [int:y]
// attack id [int:id] to [int:x] [int:y]
// stop threads 
// write data to [string:filename]
