#ifndef _ENTITY_H
#define _ENTITY_H

#include <iostream>
#include <cstring>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Entity.h
	Date of Creation:       20200130
	Latest Revise:          20200130

	Description:
		This file claims Entity classes.

	Structure of Classes:
		Entity
		1	Object
		1	2	Line
		1	2	Shape: Square / Rectangle / Circle / Polygon / FreeShape
		1	2	Solid: Cube / Cuboid / Globe / Cylinder / Prism / Ditto
		1	Effect
		1	2	Force: Gravity
		1	2	Light: Sunshine


	///////////////////////////////////////////////////////////////

*/

///////////////////////////////////
// Class Entity.

class Entity
{
	string Name;
	int validTime;
	int validZone;
public:
	Entity();
	Entity(string&);
	Entity(string&, int, int);
	~Entity() {};
	virtual void init();
	virtual void print();
};

///////////////////////////////////
// Class Object.
class Object :public Entity
{
public:
	Object();
	~Object() {};
	virtual void init();
	virtual void print();
};



#endif