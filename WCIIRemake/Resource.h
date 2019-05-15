#pragma once


class Resource {
public:
	string name;
	int count;
public:
	Resource(string name, int startCount) : count(startCount), name(name) {}
	Resource(string name) : Resource(name, 0) {}
	virtual ~Resource();
};

