#pragma once
#include <iostream>
#include <string>
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
		std::cout << "Parametreler " << p << " olarak ayarlandi." << std::endl;
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
	ParameterOriginator * originator;
	std::vector<Memento*> history;
public:
	CareTaker(ParameterOriginator* const o) : originator(o) {}
	void save()
	{
		std::cout << "Parametreler gecmiste kaydedilmisti." << std::endl;
		history.push_back(originator->createMemento());
	}
	void loadOldParam()
	{
		if (history.empty())
		{
			std::cout << "Yuklenemiyor." << std::endl;
			return;
		}
		Memento *m = history.back();
		originator->setMemento(m);
		std::cout << "Eski parametrele yuklendi." << std::endl;
		history.pop_back();
		delete m;
	}
};