#include "pch.h"
#include <iostream>
#include <vector>

class Memento
{
private:
	int param;
	friend class ParameterOriginator;

	Memento(const int p) : param(p) {}

	void setParam(const int p)
	{
		param = p;
	}

	int getParam()
	{
		return param;
	}
};


class ParameterOriginator
{
private:
	int param;
public:
	void setParam(const int p)
	{
		std::cout << "Set params to " << p << "." << std::endl;
		param = p;
	}

	int getParam()
	{
		return param;
	}

	void setMemento(Memento* const p)
	{
		param = p->getParam();
	}

	Memento *createMemento()
	{
		return new Memento(param);
	}
};

class CareTaker
{
private:
	ParameterOriginator *originator;
	std::vector<Memento*> history;

public:
	CareTaker(ParameterOriginator* const o) : originator(o) {}
	void save()
	{
		std::cout << "Saved parameters before." << std::endl;
		history.push_back(originator->createMemento());
	}

	void loadOldParam()
	{
		if (history.empty())
		{
			std::cout << "Unable to load params." << std::endl;
			return;
		}

		Memento *m = history.back();
		originator->setMemento(m);
		std::cout << "Old params loaded." << std::endl;

		history.pop_back();
		delete m;
	}
};


int main()
{
	ParameterOriginator *originator = new ParameterOriginator();
	CareTaker *caretaker = new CareTaker(originator);
	//// This part is for old params. //////
	std::cout << "In the past the program was run like this:" << std::endl;
	originator->setParam(1);
	caretaker->save();
	std::cout << "--------------------------------" << std::endl;
	///////////////////////////////////////
	originator->setParam(2);

	bool file = true; // its true if params's file is exist
	if(file)
		caretaker->loadOldParam();

	std::cout << "Actual params are " << originator->getParam() << "." << std::endl;

	return 0;
}