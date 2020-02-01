#ifndef _EFFECT_H
#define _EFFECT_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Entity.h"
#include "Concept.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Effect.h
	Date of Creation:       20200131
	Latest Revise:          20200131

	Description:
		This file claims Effect classes.

	Structure of Classes:
		Concept
		1	Effect
		1	2	Status
		1	2	3	Motion
		1	2	3	Color
		1	2	3	Tmprtr
		1	2	InterAction
		1	2	3	Force
		1	2	3	Illumin

	///////////////////////////////////////////////////////////////

*/

class Effect :public Concept
{
protected:
	Entity* target;
public:
	Effect();
	Effect(Entity*);
	~Effect() {
		//if (target)
			//delete target;
	};
	void setTarget(Entity*);
	virtual void function() {};
	virtual void print() {};
};

class Status :public Effect
{
public:
	Status() :Effect() {};
	Status(Entity* tar) :Effect(tar) {};
	~Status() {
		//if (this->target != nullptr)
			//delete this->target;
	};
	virtual void function() {};
	virtual void print() {};
};

class Motion :public Status
{
public:
	Motion() :Status() {};
	Motion(Entity* tar) :Status(tar) {};
	~Motion() {};
	void function() {};
	void print() {};
};

class Color :public Status
{
public:
	Color() :Status() {};
	~Color() {};
	void function() {};
	void print() {};
};

class Tmprtr :public Status
{
public:
	Tmprtr() :Status() {};
	~Tmprtr() {};
	void function() {};
	void print() {};
};



class InterAction :public Effect
{
public:
	InterAction() :Effect() {};
	~InterAction() {};
	virtual void function() {};
	virtual void print() {};
};

class Force :public InterAction
{
public:
	Force() :InterAction() {};
	~Force() {};
	void function() {};
	void print() {};
};

class Illumin :public InterAction
{
public:
	Illumin() :InterAction() {};
	~Illumin() {};
	void function() {};
	void print() {};
};



#endif