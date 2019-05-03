#pragma once
#include "Unit.h"
#include "AttackTHREAD.h"

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
	~LiveUnitPreset();
	void print();
};

class LiveUnit : public Unit {
private:
	cordScr moveDest;
	ThreadId MoveToTHRDDescriptor;
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
	ThreadId getMoveToTHRDDescriptor();
	cordScr* getMoveDest();
	bool goTo(cordScr* dest);
	bool attack();
	time_t getLastAttackTime();
	bool setLastAttackTime(time_t iclock);
	time_t getCooldown();
private:
	int findPath(cordScr destC); // запустить поиск пути(в процессе)
	int move(int direction); //подвинуться на поле, direction: 1-up,2-down,3-rigth,4-left,5-up right,6-up left,7-down right,8-down left;
	bool classifyEvent(Command_c* command);
	virtual void operateEvent(Command_c* command);
	virtual void stopAllThreads();
//LIVEUNIT COMMANDS(EVENTS)
protected:
	bool tpEvent(Command_c* command);
	bool moveEvent(Command_c* command);
	bool stopEvent(Command_c * command);
	bool attackEvent(Command_c* command);
};

