// ObjectPoolExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Program.h"

int main()
{
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

	getchar();
    return 0;
}

