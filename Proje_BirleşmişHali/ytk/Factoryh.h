#pragma once
#include <iostream>

class Notification
{
public:
	Notification() {}
	virtual void Alarm() {}
};

class BatteryAlert : public Notification
{
	//Batarya alarminin frekansi dusuk olacak
public:
	void Alarm()
	{
		std::cout << "\nBatarya Bitmesi Alarmi!" << std::endl;
	}
};
class CollisionAlert : public Notification
{
	//Carpisma alarminin frekansi yuksek olacak
public:
	CollisionAlert() {}
	void Alarm()
	{
		std::cout << "Çarpisma Alarmi!" << std::endl;
	}
};