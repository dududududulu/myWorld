#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Entity.h"
#include "Effect.h"
using namespace std;


/*

	///////////////////////////////////////////////////////////////

	File Name:              Effect.cpp
	Date of Creation:       20200131
	Latest Revise:          20200131

	Description:
		This file defines Effect classes.

	///////////////////////////////////////////////////////////////

*/

Effect::Effect() :Concept()
{
	target = nullptr;
}

Effect::Effect(Entity* tar) : Concept()
{
	target = tar;
}

void Effect::setTarget(Entity* tar)
{
	target = tar;
}