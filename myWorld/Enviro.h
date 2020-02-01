#ifndef _ENVIRO_H
#define _ENVIRO_H

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

	File Name:              Enviro.h
	Date of Creation:       20200202
	Latest Revise:          20200202

	Description:
		This file claims Enviro classes.

	Structure of Classes:
		Entity
		1	Individual
		1	2	Enviro
		1	2	3	LightSource
		1	2	3	Field
		1	2	3	4	Gravity



	///////////////////////////////////////////////////////////////

*/


///////////////////////////////////
// Class Enviro.
class Enviro :public Individual
{
public:
	Enviro() :Individual() {};
	~Enviro() {};
	virtual void init() {};
	virtual void print() {};
};


#endif