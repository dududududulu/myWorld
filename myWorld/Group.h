#ifndef _GROUP_H
#define _GROUP_H

#include <iostream>
#include <cstring>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Reference.h"
#include "Concept.h"
#include "Entity.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Group.h
	Date of Creation:       20200202
	Latest Revise:          20200202

	Description:
		This file claims Group classes.

	Structure of Classes:
		Entity
		1	Group
		1	2	Structure
		1	2	3	Array
		1	2	Scene
		1	2	Light: Sunshine


	///////////////////////////////////////////////////////////////

*/

class Group :public Entity
{
public:
	Group() :Entity() {};
	~Group() {};
	virtual void init() {};
	virtual void print() {};
};



#endif