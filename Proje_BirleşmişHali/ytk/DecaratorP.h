#pragma once
#include <iostream>
#include <string>
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
	Robot & m_Decorator;
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