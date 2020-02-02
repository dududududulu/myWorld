#ifndef _OBJECT_H
#define _OBJECT_H

#include <iostream>
#include <cstring>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Reference.h"
#include "Entity.h"
#include "CGeometry.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Object.h
	Date of Creation:       20200202
	Latest Revise:          20200202

	Description:
		This file claims Entity classes.

	Structure of Classes:
		Entity
		1	Individual
		1	2	Object
		1	2	3	Element
		1	2	3	4	Geometry
		1	2	3	4	5	Line
		1	2	3	4	5	Shape: Square / Rectangle / Circle / Polygon / FreeShape
		1	2	3	4	5	Solid: Cube / Cuboid / Globe / Cylinder / Prism / Ditto
		1	2	3	4	*Pattern
		1	2	3	Combine



	///////////////////////////////////////////////////////////////

*/


///////////////////////////////////
// Class Object.
class Object :public Individual
{
protected:
	double mass;
	double volume;
	double density;
public:
	Object() :Individual() {};
	~Object() {};
	virtual void init() {};
	virtual void print() {};
};

class Element :public Object
{
protected:
	int material;
protected:
	virtual void physical_init() {};
public:
	Element() :Object() {};
	~Element() {};
	virtual void init() {};
	virtual void print() {};
};

class Geometry :public Element
{
protected:
	CGeometry* cgeo;
protected:
	void physical_init();
public:
	Geometry(int = cube_geo, int = 0);
	~Geometry() {};
	void resize(double, double = 1, double = 1);
	virtual void init() {};
	virtual void print() {};
};

Geometry::Geometry(int GType, int GMaterial)
{
	switch (GType)
	{
	case line_geo: cgeo = new CLine; break;

	case circle_geo: cgeo = new CCircle; break;
	case square_geo: cgeo = new CSquare; break;
	case rectangle_geo: cgeo = new CRectangle; break;
	case triangle_geo: cgeo = new CPolygon<3>; break;
	case pendagon_geo: cgeo = new CPolygon<5>; break;
	case hexagon_geo: cgeo = new CPolygon<6>; break;

	case globe_geo: cgeo = new CGlobe; break;
	case cube_geo: cgeo = new CCube; break;
	case cuboid_geo: cgeo = new CCuboid; break;
	case cylinder_geo: cgeo = new CCylinder; break;
	
	default: cgeo = new CCube; break;
	}

	material = GMaterial;
	physical_init();
}

void Geometry::physical_init()
{
	volume = cgeo->getVolume();
	density = material_density(material);
	mass = volume * density;
}

void Geometry::resize(double size1, double size2, double size3)
{
	cgeo->resize(size1, size2, size3);
}


class Combine :public Object
{
protected:
	Element* elem;
public:
	Combine() :Object() {};
	~Combine() {};
	virtual void init() {};
	virtual void print() {};
};


#endif