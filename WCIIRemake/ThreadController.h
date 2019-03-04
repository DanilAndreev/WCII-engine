#pragma once
#include "DynArr.h"

class ThreadController : public DynArr {
public:
	ThreadController();
	~ThreadController();
	bool add(Threadable thread);
};

