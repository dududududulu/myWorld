#ifndef _CONCEPT_H
#define _CONCEPT_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Concept.h
	Date of Creation:       20200129
	Latest Revise:          20200129

	Description:
		This file claims and defines Concept classes.

	Structure of Classes:
		Concept
		1	CFigure
		1	2	CGeometry
		1	2	3	CLine
		1	2	3	CShape: CSquare / CRectangle / CCircle / CPolygon<SideNum> / CFreeShape / *CCurve
		1	2	3	CSolid: CCube / CCuboid / CGlobe / CCylinder / CPrism<SideNum> / CFreeSolid / *CSurface
		1	2	*CPattern
		1	Applied
		1	2	InterAct
		1	2	3	Force
		1	2	3	Illumin
		1	2	Effect
		1	2	3	Motion
		1	2	3	Shaping
		1	2	3	Filter
				

	///////////////////////////////////////////////////////////////

*/

class Entity;

class Concept
{
public:
	Concept() {};
	~Concept() {};
	virtual void print() {};
	// 2001291652.
};

class CFigure :public Concept
{
public:
	CFigure() :Concept() {};
	~CFigure() {};
	virtual void scaling(double) {};
	virtual void print() {};
};

class Applied :public Concept
{
protected:
	Entity* target;
public:
	Applied();
	Applied(Entity*);
	~Applied() {
		//if (target)
			//delete target;
	};
	void setTarget(Entity*);
	Entity* getTarget();
	void printTarget();
	virtual void function() {};
	virtual void print();

};


#endif