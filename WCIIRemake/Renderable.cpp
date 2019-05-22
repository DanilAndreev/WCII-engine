#include "pch.h"
#include "Renderable.h"


Renderable::Renderable(){
	this->parentScreen = NULL;
}


Renderable::~Renderable() {
}

void Renderable::setParentScreen(CScreen* iparent) {
	this->parentScreen = iparent;
}

