// ytk.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "Factoryh.h"
#include "IteratorPattern.h"
#include "rrt.h"
#include "Singleton.h"
#include "AbstractFactoryP.h"
#include "MementoPattern.h"
#include "DecaratorP.h"
#include "Builder.h"
#include "vertex.h"
#include "ObjectPooling.h"

int main()
{
	//----------------------------------------------------------------------Decorator Pattern icin
	std::cout << "Robot sensor eklemesi yapilirsa diye DECORATOR PATTERN";
	Robot* pTurtleBot = new TurtleBot();
	pTurtleBot->Add();

	Robot* pTurtleBotWithFrontCamera = new WithFrontCamera(*pTurtleBot);
	pTurtleBotWithFrontCamera->Add();

	Robot* pTurtleBotWithFrontCameraAndFallDetection = new WithFallDetection(*pTurtleBotWithFrontCamera);
	pTurtleBotWithFrontCameraAndFallDetection->Add();
	//----------------------------------------------------------------------Builder Pattern icin
	std::cout << "\nKamera ayarlamasi icin BUILDER PATTERN\n";
	CameraBuilder *burgerwithfrontcamera = new RobotBurgerWithFC();
	CameraBuilder *wafflewithfrontcamera = new RobotWaffleWithoutFC();

	Contractor *ctr1 = new Contractor(burgerwithfrontcamera);
	Contractor *ctr2 = new Contractor(wafflewithfrontcamera);

	ctr1->buildCamera();
	Camera *r1 = ctr1->getCamera();

	cout << "Kamera 1 : \n";
	cout << "Olusturulan: " << r1 << "\n";
	cout << r1->CameratoString();

	ctr2->buildCamera();
	Camera *r2 = ctr2->getCamera();
	cout << "Kamera 2 : \n";
	cout << "Olusturulan: " << r2 << "\n";
	cout << r2->CameratoString();

	//----------------------------------------------------------------------Iterator Pattern icin
	std::cout << "\nHaritaya nesne eklenmesi ve o nesnelerin okunmasi icin ITERATOR PATTERN\n";
	DinamicEnvironment *de = new DinamicEnvironment();
	Iterator *itr = de->getIterator();
	itr->loadMap();
	while (itr->next()) {
		Object *t = (Object*)itr->getItem();
		std::cout << t->toString() << std::endl;
	}
	StaticEnvironment *se = new StaticEnvironment();
	itr = se->getIterator();
	itr->loadMap();
	while (itr->next()) {
		Object *t = (Object*)itr->getItem();
		std::cout << t->toString() << std::endl;
	}
	//----------------------------------------------------------------------Object Pooling Pattern icin
	std::cout << "\nDunyaya sonradan eklenecek engeller icin  OBJECT POOLING PATTERN\n";
	Obstacle *cnn = new Obstacle("k1");
	cnn->Open();
	cnn->Execute("obs1 ");
	cnn->Close();
	cout << "----------------------" << endl;
	Obstacle *cnn2 = new Obstacle("k1");
	cnn2->Open();
	cnn2->Execute("obs2 ");
	cnn2->Close();
	cout << "----------------------" << endl;
	Obstacle *cnn3 = new Obstacle("k1");
	cnn3->Open();
	cnn3->Execute("obs3 ");
	cnn3->Close();
	cout << "----------------------" << endl;

	//----------------------------------------------------------------------Factory Pattern icin 
	std::cout << "\nRobot calisirken uyarilar icin ses biildirimi (ture gore frekansli) icin  FACTORY PATTERN\n";
	bool collision = true;
	if (collision) {
		Notification *pcollision = new CollisionAlert();
		pcollision->Alarm();
	}
	bool batteryLow = true;
	if (batteryLow) {
		Notification *pbatteryLow = new BatteryAlert();
		pbatteryLow->Alarm();
	}
	std::cout << "\nRobot calisirken uyarilar icin ses biildirimi (ture gore frekansli) icin  FACTORY PATTERN\n";
	bool collision = true;
	if (collision) {
		Notification *pcollision = new CollisionAlert();
		pcollision->Alarm();
	}
	bool batteryLow = true;
	if (batteryLow) {
		Notification *pbatteryLow = new BatteryAlert();
		pbatteryLow->Alarm();
	}
	getchar();
	//----------------------------------------------------------------------Memento Pattern icin
	std::cout << "Eski parametrelerin yuklenmesi icin MEMENTO PATTERN\n";
	ParameterOriginator *param = new ParameterOriginator();
	CareTaker *caretaker = new CareTaker(param);

	// Parametreler gecmiste calistiginda 1 idi.
	param->setParam(1);
	caretaker->save();

	// Parametrelerin şuan 2 olarak default olarak atandigi dusunulsun
	param->setParam(2);

	// Gecmiste program calismis da parametrelere 1 atanmis ve dosyaya kaydedilmis olarak dusunulsun
	bool file = true;
	if (file)
		caretaker->loadOldParam();

	std::cout << "Parametreler suan " << param->getParam() << "." << std::endl;
    return 0;
}

