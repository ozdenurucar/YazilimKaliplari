#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "vectorhelper.h"

using namespace std;

class ObstacleContext {
private:
	bool is_Active;
	//Nesnenin kullanili kullanilmadiği bilgisini tutar
public:
	const bool &getisActive() const;
	void setisActive(const bool &value);
	ObstacleContext();
	void Open();
	void Close();
	void Execute(const string &query);
};
class PoolManager;
class Obstacle {
private:
	string ObstacleString;
	PoolManager *poolManager;
	ObstacleContext *con;

public:
	const string &getObstacleString() const;
	void setObstacleString(const string &value);
	Obstacle(const string &ObstacleString);
	void Open();
	void Close();
	void Execute(const string &query);
};
class PoolManager {
private:
	static const int POOL_SİZE = 5;
	unordered_map<string, vector<ObstacleContext*>> pools;
protected:
	static PoolManager *pm;
	PoolManager();
public:
	static PoolManager *createPool();
	ObstacleContext *TakeObstacle(const string &key);
	void ReleaseObstacle(ObstacleContext *Obstacle);

};
