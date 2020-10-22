#pragma once
#include <iostream>

using namespace std;

class CScreen;

class Renderable{
public:
	CScreen* parentScreen;
public:
	Renderable();
	virtual ~Renderable();
	virtual void render(int layer, int team) = 0;
	virtual void render(int team) = 0;
	void setParentScreen(CScreen* iparent);
};

