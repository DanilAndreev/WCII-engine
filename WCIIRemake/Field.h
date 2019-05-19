#pragma once
#include "pch.h"
#include "Screenable.h"


class FieldPreset {
public:
	int width;
	int heigth;
	
};

class Unit;

class Field : public Screenable {
private:
	int fieldLen;
protected:
	DynArr* members;
public:
	Field(int width, int heigth);
	Field() : Field(30, 30) {}
	Field(FieldPreset preset) : Field(preset.width, preset.heigth) {}
	virtual ~Field();
	DynArr* getMembers();
	void freeElements(); // Удалить всех детей поля(из пямяти, указатели останутся, но будут указывать в небо)
	int setCell(cordScr cordsNew, Unit * target); // установить на клетку с данными координатам данный юнит
	int changeCell(cordScr cords, Unit * target); // поменять клетку(прыгнуть в клетку с данными координатами)
	virtual void render(int layer); // отрисоваться(просчитаться)
	bool checkFree(cordScr cords, int type); // проверить клетку на наличие юнита даного типа (вернет истину если нету и ложь если есть)
	virtual void catchEvent(Command_c* command, bool showHelp);
protected:
	virtual void fillEventPatterns();
public:// FIELD EVENTS
	static void writeDataToCommand(Command_c* command, Eventable* oParent);
	static void spawnUnitArgsCommand(Command_c* command, Eventable* oParent);
	static void spawnUnitPresetCommand(Command_c* command, Eventable* oParent);
	static void spawnBuildingArgsCommand(Command_c* command, Eventable* oParent);
};

// write data to [string:savename]
// spawn unit cords [int:x] [int:y] team [int:team] health [int:health] attackLength [int:length] type [int:type] symbol [char:symbol] cooldown [int:cooldown] speed [int:speed] power [int:power]
// spawn team [int:team] unit [string:preset name] cords [int:x] [int:y]
// spawn building cords [int:x] [int:y] team [int:team] health [int:health] type [int:type] symbol [char:symbol]
