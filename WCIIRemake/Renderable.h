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
	virtual void render(int layer) = 0;
	virtual void render() = 0;
	void setParentScreen(CScreen* iparent);
};

