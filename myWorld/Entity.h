#ifndef _ENTITY_H
#define _ENTITY_H

#include <iostream>
#include <cstring>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Reference.h"
#include "Status.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Entity.h
	Date of Creation:       20200130
	Latest Revise:          20200202

	Description:
		This file claims Entity classes.

	Structure of Classes:
		Entity
		1	Individual
		1	2	Object
		1	2	3	Element
		1	2	3	4	Geometry
		1	2	3	4	5	Line
		1	2	3	4	5	Shape: Square / Rectangle / Circle / Polygon / FreeShape
		1	2	3	4	5	Solid: Cube / Cuboid / Globe / Cylinder / Prism / Ditto
		1	2	3	4	*Pattern
		1	2	3	Combine
		1	2	Enviro
		1	2	3	LightSource
		1	2	3	Field
		1	2	3	4	Gravity
		1	Group
		1	2	Structure
		1	2	3	Array
		1	2	Stew
		1	2	3	Machine
		1	2	3	Scene


	///////////////////////////////////////////////////////////////

*/

///////////////////////////////////
// Class Entity.

class Entity
{
protected:
	string Name;
	Ref<Dimension>* ref;
	Status* status;
	//int validTime;
	//int validZone;
protected:
	void new_init();
	void empty();
public:
	Entity();
	Entity(string&);
	~Entity() {
		empty();
	};
	void setName(string&);
	virtual void init();
	virtual void status_update();
	virtual void print() {};
};

Entity::Entity()
{
	new_init();
}

Entity::Entity(string& name)
{
	new_init();
	setName(name);
}

void Entity::new_init()
{
	empty();
	ref = new Ref<Dimension>;
	status = new Status;
}

void Entity::empty()
{
	if (ref) delete ref;
	if (status) delete status;
}

void Entity::setName(string& name)
{
	Name = name;
}

void Entity::init()
{
	new_init();
}

void Entity::status_update()
{
	ref->movement(status->motion);
}


class Individual :public Entity
{
public:
	Individual() :Entity() {};
	Individual(string& name) :Entity(name) {};
	~Individual() {};
	virtual void init() {};
	virtual void print() {};
};




#endif