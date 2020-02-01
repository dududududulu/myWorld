
#ifndef _INTERACT_H
#define _INTERACT_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Concept.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              InterAct.h
	Date of Creation:       20200202
	Latest Revise:          20200202

	Description:
		This file claims and defines InterAct classes.

	Structure of Classes:
		Concept
		1	InterAct
		1	2	Force
		1	2	Illumin


	///////////////////////////////////////////////////////////////

*/


class InterAct :public Applied
{
public:
	InterAct() :Applied() {};
	~InterAct() {};
	virtual void function() {};
	virtual void print() {};
};

class Force :public InterAct
{
public:
	Force() :InterAct() {};
	~Force() {};
	void function() {};
	void print() {};
};

class Illumin :public InterAct
{
public:
	Illumin() :InterAct() {};
	~Illumin() {};
	void function() {};
	void print() {};
};




#endif