#ifndef _OBJECT_H
#define _OBJECT_H

#include <iostream>
#include <cstring>
#include <cmath>
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
	int color;		// should be Vector<int, 3>. unfinished, 2002022050
protected:
	virtual void materialize() {};
public:
	Object() :Individual() { color = 0; }; // unfinished, 2002022050
	~Object() {};
	double getMass() { return mass; };
	double getVolume() { return volume; };
	double getDensity() { return density; };
	int getColor() { return color; };
	virtual void init() {};
	virtual void print() {};
	virtual void display(Observer*) {};
};

class Element :public Object
{
protected:
	int material;
protected:
	virtual void physical_init() {};
	virtual void materialize() {};
public:
	Element() :Object() {};
	~Element() {};
	virtual void init() {};
	virtual void print() {};
	virtual void display(Observer*) {};
};

class Geometry :public Element
{
protected:
	CGeometry* cgeo;
protected:
	void physical_init();
	virtual void materialize() {};
public:
	Geometry(int = null_geo, int = 0, double = 1, double = 1, double = 1);
	~Geometry() {
		if (cgeo) delete cgeo;
	};
	void resize(double, double = 1, double = 1);
	void init();
	void print();
	virtual void display(Observer*) {};
};

class Line :public Geometry
{
public:
	Line(double len = 1) :Geometry(line_geo, 0, len) {};
	~Line() {};
	void display(Observer*);
};

class Shape :public Geometry
{
public:
	Shape(int GType = null_geo, int GMaterial = 0, double size1 = 1, double size2 = 1, double size3 = 1)
		:Geometry(GType, GMaterial, size1, size2, size3) {};
	~Shape() {};
	virtual void display(Observer*) {};
};

class Circle :public Shape
{
public:
	Circle(double r = 1, int GMaterial = 0)
		:Shape(circle_geo, GMaterial, r) {};
	~Circle() {};
	void display(Observer*);
};

class Square :public Shape
{
public:
	Square(double side = 1, int GMaterial = 0)
		:Shape(square_geo, GMaterial, side) {};
	~Square() {};
	void display(Observer*);
};

class Rectangle :public Shape
{
public:
	Rectangle(double xside = 1, double yside = 1, int GMaterial = 0)
		:Shape(rectangle_geo, GMaterial, xside, yside) {};
	~Rectangle() {};
	void display(Observer*);
};

template<int SideNum>
class Polygon :public Shape
{
public:
	Polygon(double side = 1, int GMaterial = 0)
		:Shape(polygon_geo + SideNum - 2, GMaterial, side) {};
	~Polygon() {};
	void display(Observer* eye)
	{
		double realm = this->cgeo->getRealm(), rr;
		double itr = -realm, jtr, jend;
		double step = eye->mapping(this->ref->getOrigin());
		int i, j;
		while(itr < realm)
		{
			jend = sqrt(rr - itr * itr);
			jtr = -jend;
			while (jtr < 0)
			{
				//if (this->cgeo->isInside(/* unfinished */)) break;
				jtr = jtr + step;
			}
			itr = itr + step;
		}
	}
};




class Solid :public Geometry
{
	Line* line;
	Shape* shape;
protected:
	virtual void materialize() {};
public:
	Solid(int GType = null_geo, int GMaterial = 0, double size1 = 1, double size2 = 1, double size3 = 1)
		:Geometry(GType, GMaterial, size1, size2, size3) {};
	~Solid() {};
	void display(Observer*);
};

class Globe :public Solid
{
protected:
	void materialize();
public:
	Globe(double r = 1, int GMaterial = 0)
		:Solid(globe_geo, GMaterial, r) {
		materialize();
	};
	~Globe() {};
};

class Cube :public Solid
{
protected:
	void materialize();
public:
	Cube(double edge = 1, int GMaterial = 0)
		:Solid(cube_geo, GMaterial, edge) {
		materialize();
	};
	~Cube() {};
};

class Cuboid :public Solid
{
protected:
	void materialize();
public:
	Cuboid(double xedge = 1, double yedge = 1, double zedge = 1, int GMaterial = 0)
		:Solid(cuboid_geo, GMaterial, xedge, yedge, zedge) {
		materialize();
	};
	~Cuboid() {};
};

class Cylinder :public Solid
{
protected:
	void materialize();
public:
	Cylinder(double r = 1, double height = 1, int GMaterial = 0)
		:Solid(cylinder_geo, GMaterial, r, height) {
		materialize();
	};
	~Cylinder() {};
};

class triPrism :public Solid
{
protected:
	void materialize();
public:
	triPrism(double realm = 1, double height = 1, int GMaterial = 0)
		:Solid(triprism_geo, GMaterial, realm, height) {
		materialize();
	};
	~triPrism() {};
};



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