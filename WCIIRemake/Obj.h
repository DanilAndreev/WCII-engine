#pragma once
class Obj {
	private:
		const char *className;
	public:
		Obj();
		Obj(const char* className);
		virtual ~Obj();
		const char* getClassName(); // возвращает имя класса
	protected:
		void setClassName(const char* className); // записать имя класса(для наследования)
};

