#pragma once
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

//Global Variables
//nav_msgs::OccupancyGrid mapData;

class Map_singleton
{
private:
	static Map_singleton *map;// sınıfa ait mapdata nesnesi.
	nav_msgs::OccupancyGrid mapData;
public:
	static Map_singleton *CreateMap(void);
	void SetData(const nav_msgs::OccupancyGrid::ConstPtr& data);
	/*void mapCallBack(const nav_msgs::OccupancyGrid::ConstPtr& msg)
	{
	mapData = *msg;
	}*/
};

Map_singleton *Map_singleton::CreateMap()
{
	if (map == nullptr)
	{
		map = new Map_singleton();
	}
	return map;
}
void Map_singleton::SetData(const nav_msgs::OccupancyGrid::ConstPtr& data)
{

}