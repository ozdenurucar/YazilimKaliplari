#pragma once
#include <iostream>
#include <string>
#include <vector>

class Iterator {
public:
	virtual bool next() = 0;
	virtual void* getItem() = 0;
	virtual void loadMap() = 0;
};

class Iterable {
public:
	virtual Iterator* getIterator() = 0;
};

class Object {
private:
	std::string name;
public:
	Object(std::string name) {
		this->name = name;
	}
	std::string toString() {
		return this->name;
	}
};
class StaticEnvironment : public Iterable {
private:
	Object * *objects;
public:
	StaticEnvironment() {
		objects = new Object*[3];
		objects[0] = new Object("bookshelf");
		objects[1] = new Object("chair");
		objects[2] = new Object("desk");
	}
	Object** GetObjects() {
		return objects;
	}
	Iterator* getIterator();
};

class DinamicEnvironment : public Iterable {
private:
	std::vector<Object*> objects;
public:
	DinamicEnvironment() {
		objects = std::vector<Object*>();
		objects.push_back(new Object("person"));
		objects.push_back(new Object("dog"));
		objects.push_back(new Object("cat"));
	}

	std::vector<Object*> GetObjects() {
		return objects;
	}
	Iterator* getIterator();
};

class StaticEIterator : public Iterator {
private:
	StaticEnvironment * staticE;
	int index;
public:
	StaticEIterator() {
		staticE = new StaticEnvironment();
	}
	void* getItem() {
		Object **c = &(staticE->GetObjects()[index]);
		++index;
		return *c;
	}
	bool next() {
		if (index < 3) {
			return true;
		}
		else {
			return false;
		}
	}
	void loadMap() {
		std::cout << "static map" << std::endl;
	}

};

class DinamicEIterator : public Iterator {
private:
	DinamicEnvironment * dinamicE;
	int index;
public:
	DinamicEIterator() {
		dinamicE = new DinamicEnvironment();
	}
	void *getItem() {
		Object *c = dinamicE->GetObjects()[index];
		++index;
		return c;
	}
	bool next() {
		if (index < (int)dinamicE->GetObjects().size()) {
			return true;
		}
		else {
			return false;
		}
	}
	void loadMap() {
		std::cout << "dinamic map" << std::endl;
	}
};

Iterator* DinamicEnvironment::getIterator()
{
	return new DinamicEIterator();
}

Iterator* StaticEnvironment::getIterator()
{
	return new StaticEIterator();
}