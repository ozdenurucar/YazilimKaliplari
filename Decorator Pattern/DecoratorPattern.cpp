#include "pch.h"

#include <iostream>

class Robot
{
public:
	virtual void Add() = 0;
	virtual ~Robot()
	{
		std::cout << "delete Robot";
	}
};

class TurtleBot : public Robot
{
public:
	virtual void Add()
	{
		std::cout << "\n TurtleBot";
	}
};

class RobotDecorator : public Robot
{
public:
	RobotDecorator(Robot& decorator) :m_Decorator(decorator) {}
	virtual void Make()
	{
		m_Decorator.Add();
	}
private:
	Robot& m_Decorator;
};

class WithFrontCamera : public RobotDecorator
{
public:
	WithFrontCamera(Robot& decorator) :RobotDecorator(decorator) {}
	virtual void Add()
	{
		RobotDecorator::Make();
		std::cout << " + FrontCamera";
	}
	virtual ~WithFrontCamera()
	{
		std::cout << "delete FrontCamera";
	}
};

class WithFallDetection : public RobotDecorator
{
public:
	WithFallDetection(Robot& decorator) :RobotDecorator(decorator) {}
	virtual void Add()
	{
		RobotDecorator::Make();
		std::cout << " + FallDetection";
	}
	virtual ~WithFallDetection()
	{
		std::cout << "delete FallDetection";
	}
};

int main()
{
	Robot* pTurtleBot = new TurtleBot();
	pTurtleBot->Add();

	Robot* pTurtleBotWithFrontCamera = new WithFrontCamera(*pTurtleBot);
	pTurtleBotWithFrontCamera->Add();

	Robot* pTurtleBotWithFrontCameraAndFallDetection = new WithFallDetection(*pTurtleBotWithFrontCamera);
	pTurtleBotWithFrontCameraAndFallDetection->Add();


	std::cout << "\n----------------------Del pTurtleBot----------------------\n";

	delete pTurtleBot;
	std::cout << "\n---------------Del pTurtleBotWithFrontCamera---------------\n";
	delete pTurtleBotWithFrontCamera;
	std::cout << "\n-------Del pTurtleBotWithFrontCameraAndFallDetection-------\n";
	delete pTurtleBotWithFrontCameraAndFallDetection;


	return 0;
}