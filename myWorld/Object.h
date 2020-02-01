#ifndef _OBJECT_H
#define _OBJECT_H

#include <iostream>
#include <cstring>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Reference.h"
#include "Entity.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Object.h
	Date of Creation:       20200202
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



	///////////////////////////////////////////////////////////////

*/


///////////////////////////////////
// Class Object.
class Object :public Individual
{
public:
	Object() :Individual() {};
	~Object() {};
	virtual void init() {};
	virtual void print() {};
};


#endif