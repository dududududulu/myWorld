#ifndef _STATUS_H
#define _STATUS_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Concept.h"
#include "InterAct.h"
#include "Effect.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Status.h
	Date of Creation:       20200202
	Latest Revise:          20200202

	Description:
		This file claims and defines Status classes.

	Structure of Classes:
		Status


	///////////////////////////////////////////////////////////////

*/

class Status
{
	Motion motion;
	Shaping shaping;
	Filter filter;
public:
	Status() {};
	~Status() {};
};


#endif