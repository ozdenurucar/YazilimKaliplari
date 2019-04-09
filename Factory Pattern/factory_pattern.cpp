
//Factory Pattern
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "nav_msgs/OccupancyGrid.h"
#include "geometry_msgs/PointStamped.h"
#include "std_msgs/Header.h"
#include "nav_msgs/MapMetaData.h"
#include "geometry_msgs/Point.h"

class Notification
{
public:
	virtual void Alarm() {}
};

class BatteryAlert : public Notification
{
	//Batarya alarminin frekansi dusuk olacak
public:
	void Alarm()
	{
		std::cout << "Battery Alert!" << std::endl;
	}
};
class CollisionAlert : public Notification
{
	//Carpisma alarminin frekansi yuksek olacak
public:
	void Alarm()
	{
		std::cout << "Collision Alert!" << std::endl;
	}
};


int main()
{
	
}