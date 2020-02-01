#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Effect.h"
using namespace std;


/*

	///////////////////////////////////////////////////////////////

	File Name:              Effect.cpp
	Date of Creation:       20200131
	Latest Revise:          20200202

	Description:
		This file defines Effect classes.

	///////////////////////////////////////////////////////////////

*/

/* Functions of class Motion */
void Motion::setDrift(const dVector<Dimension>& drift)
{
	translate = drift;
}

void Motion::setRot(const dVector<Dimension>& torque)
{
	axis = torque;
	rotMatrix = rotator<double, Dimension>(torque);
}

void Motion::addDrift(const dVector<Dimension>& drift)
{
	translate = translate + drift;
}

void Motion::addRot(const dVector<Dimension>& torque)
{
	setRot(axis + torque);
}

void Motion::function()
{
	//this->target->movement();
}

void Motion::print()
{

}
