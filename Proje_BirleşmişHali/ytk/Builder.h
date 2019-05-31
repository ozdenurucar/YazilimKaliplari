#pragma once
#include <iostream>
#include <string>
using namespace std;
// Donecek olan urun
class Camera {

private:
	string CameraType, FrontCameraType, BackCameraType;
public:
	void setCameraType(string CameraType)
	{
		this->CameraType = CameraType;
	}
	void setFrontCameraType(string FrontCameraType)
	{
		this->FrontCameraType = FrontCameraType;
	}
	void setBackCameraType(string BackCameraType)
	{
		this->BackCameraType = BackCameraType;
	}
	string CameratoString()
	{
		string features = "Kamera Ozellikleri \n";
		features += "Kamera Turu: ";
		features += this->CameraType;
		features += "\n";
		features += "On Kamera Turu: ";
		features += this->FrontCameraType;
		features += "\n";
		features += "Arka Kamera Turu: ";
		features += this->BackCameraType;
		features += "\n";
		return features;
	}
};
// Builder sinif
class CameraBuilder
{
public:
	/* Abstract functions to build parts */
	virtual void buildBackCameraType() = 0;
	virtual void buildCameraType() = 0;
	virtual void buildFrontCameraType() = 0;
	/* The product is returned by this function */
	virtual Camera* getCamera() = 0;
};

// RobotBuilder arayuzunun Concrete sinifi
class RobotBurgerWithFC :public CameraBuilder {
private:
	Camera * camera;
public:
	RobotBurgerWithFC()
	{
		camera = new Camera();
	}
	void buildCameraType()
	{
		camera->setCameraType("LIDAR");
	}
	void buildFrontCameraType()
	{
		camera->setFrontCameraType("NormalKamera");
	}
	void buildBackCameraType()
	{
		camera->setBackCameraType("None");
	}
	Camera* getCamera()
	{
		return this->camera;
	}
};

// RobotBuilder arayuzunun baska bir Concrete sinifi
class RobotWaffleWithoutFC :public CameraBuilder {
private:
	Camera * camera;
public:
	RobotWaffleWithoutFC()
	{
		camera = new Camera();
	}

	void buildBackCameraType()
	{
		camera->setBackCameraType("None");
	}

	void buildCameraType()
	{
		camera->setCameraType("LIDAR");
	}

	void buildFrontCameraType()
	{
		camera->setFrontCameraType("None");
	}

	Camera* getCamera()
	{
		return this->camera;
	}
};

/* Director veya Client denebilir. Kamerayi insa eder */
class Contractor
{
private:
	CameraBuilder * cameraBuilder;

public:
	Contractor(CameraBuilder *robotBuilder)
	{
		this->cameraBuilder = robotBuilder;
	}

	Camera *getCamera()
	{
		return cameraBuilder->getCamera();
	}

	void buildCamera()
	{
		cameraBuilder->buildBackCameraType();
		cameraBuilder->buildCameraType();
		cameraBuilder->buildFrontCameraType();
	}
};