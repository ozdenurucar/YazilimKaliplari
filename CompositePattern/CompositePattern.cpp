// CompositePattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;
class ComponentTree
{
public:
	virtual void traverse() = 0;
};
class Leaf : public ComponentTree
{
	int value;
public:
	Leaf(int val)
	{
		value = val;
	}
	void traverse()
	{
		cout << value << ' ';
	}
};

class Composite : public ComponentTree
{
	vector < ComponentTree * > children;
public:
	void add(ComponentTree *ele)
	{
		children.push_back(ele);
	}
	void traverse()
	{
		for (int i = 0; i < children.size(); i++)
			children[i]->traverse();
	}
};
int main()
{
	Composite containers[4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			containers[i].add(new Leaf(i * 3 + j));

	for (int i = 1; i < 4; i++)
		containers[0].add(&(containers[i]));

	for (int i = 0; i < 4; i++)
	{
		containers[i].traverse();
		cout << endl;
	}
}