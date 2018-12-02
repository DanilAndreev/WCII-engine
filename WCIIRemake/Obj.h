#pragma once
class Obj {
	private:
		const char *className;
	public:
		Obj();
		Obj(const char* className);
		virtual ~Obj();
		const char* getClassName();
	protected:
		void setClassName(const char* className);
};

