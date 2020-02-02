#ifndef _EFFECT_H
#define _EFFECT_H

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

class Effect :public Applied
{
public:
	Effect() :Applied() {};
	Effect(Entity* tar) :Applied(tar) {};
	~Effect() {
		//if (this->target != nullptr)
			//delete this->target;
	};
	virtual void function() {};
	virtual void print() {};
};

class Motion :public Effect
{
	bool is_balanced, is_origin;
	dVector<Dimension> translate;
	dVector<Dimension> axis;
	uMatrix<double, Dimension, Dimension> rotMatrix;
protected:
	void checkBalanced();
	void checkOrigin();
	void update();
public:
	Motion();
	Motion(Entity*);
	Motion(Motion&);
	~Motion() {};
	void setDrift(const dVector<Dimension>&);
	void setRot(const dVector<Dimension>&);
	void addDrift(const dVector<Dimension>&);
	void addRot(const dVector<Dimension>&);
	dVector<Dimension> deviate(const dVector<Dimension>&)const;
	LnBase<Dimension> deflect(const LnBase<Dimension>&)const;
	void function();
	void print();
};

class Shaping :public Effect
{
public:
	Shaping() :Effect() {};
	~Shaping() {};
	void function() {};
	void print() {};
};

class Filter :public Effect
{
public:
	Filter() :Effect() {};
	~Filter() {};
	void function() {};
	void print() {};
};


#endif