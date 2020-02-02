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
Motion::Motion() :Effect()
{
	update();
}

Motion::Motion(Entity* tar) : Effect(tar)
{
	update();
}

Motion::Motion(Motion& motion)
{
	this->target = motion.target;
	translate = motion.translate;
	axis = motion.axis;
	rotMatrix = motion.rotMatrix;
	update();
}

void Motion::checkBalanced()
{
	is_balanced = rotMatrix.isIdentity();
}

void Motion::checkOrigin()
{
	is_origin = translate.isOrigin();
}

void Motion::update()
{
	checkBalanced();
	checkOrigin();
}

void Motion::setDrift(const dVector<Dimension>& drift)
{
	translate = drift;
	checkOrigin();
}

void Motion::setRot(const dVector<Dimension>& torque)
{
	axis = torque;
	rotMatrix = rotator<double, Dimension>(torque);
	checkBalanced();
}

void Motion::addDrift(const dVector<Dimension>& drift)
{
	translate = translate + drift;
	checkOrigin();
}

void Motion::addRot(const dVector<Dimension>& torque)
{
	setRot(axis + torque);
	checkBalanced();
}

dVector<Dimension> Motion::deviate(const dVector<Dimension>& vec)const
{
	if (is_origin) return vec;
	dVector<Dimension> result = vec + translate * TimeElapse;
	return result;
}

LnBase<Dimension> Motion::deflect(const LnBase<Dimension>& base)const
{
	if (is_balanced) return base;
	LnBase<Dimension> result(base);
	result.rotate(rotMatrix);
	return result;
}

void Motion::function()
{
	//this->target->movement();
}

void Motion::print()
{
	cout << "Drift:" << translate << endl;
	cout << "Rotation:   " << axis.getLen() << "/s clockwise around " << axis << endl;
	cout << rotMatrix << endl;
}
