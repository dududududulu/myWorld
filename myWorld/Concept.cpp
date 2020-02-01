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

	File Name:              Concept.cpp
	Date of Creation:       20200202
	Latest Revise:          20200202

	Description:
		This file defines Concept classes.

	///////////////////////////////////////////////////////////////

*/


Applied::Applied() :Concept()
{
	target = nullptr;
}

Applied::Applied(Entity* tar) : Concept()
{
	target = tar;
}

void Applied::setTarget(Entity* tar)
{
	target = tar;
}

Entity* Applied::getTarget()
{
	return target;
}

void Applied::printTarget()
{
	cout << "Target:" << endl << target << endl;
}

void Applied::print()
{
	cout << "Effect:" << endl << "    ";
	printTarget();
}
