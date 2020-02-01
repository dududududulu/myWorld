#ifndef _CONCEPT_H
#define _CONCEPT_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Entity.h"
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
		1	Effect
		1	2	Motion
		1	2	Force
		1	2	Light
				

	///////////////////////////////////////////////////////////////

*/

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

class CGeometry:public CFigure
{
public:
	CGeometry():CFigure() {};
	~CGeometry() {};
	virtual void scaling(double) {};
	virtual void print() {};
};

class CLine :public CGeometry
{
protected:
	double length;
public:
	CLine();
	CLine(double);
	~CLine() {};
	void scaling(double);
	void print();
};

class CShape :public CGeometry
{
protected:
	double perimeter;
	double area;
public:
	CShape();
	~CShape() {};
	double getPerim();
	double getArea();
	virtual void calPerim() {};
	virtual void calArea() {};
	virtual void scaling(double) {};
	virtual void print() {};
};

class CCircle :public CShape
{
	double radius;
public:
	CCircle();
	CCircle(double);
	~CCircle() {};
	void calPerim();
	void calArea();
	void scaling(double);
	void print();
};

template<int SideNum> class CPolygon;
using CTriangle = CPolygon<3>;
using CPentagon = CPolygon<5>;
using CHexagon = CPolygon<6>;

template<int SideNum>
class CPolygon :public CShape
{
	double side;
	double angle;
	double realm;
public:
	CPolygon();
	CPolygon(double);
	~CPolygon() {};
	void setSide(double = 1);
	double getSide();
	void calPerim();
	void calArea();
	void scaling(double);
	void print();
};

template<int SideNum>
CPolygon<SideNum>::CPolygon()
{
	realm = 1;
	angle = 2 * PI / SideNum;
	side = 2 * realm * sin(angle / 2);
	calPerim();
	calArea();
}

template<int SideNum>
CPolygon<SideNum>::CPolygon(double len)
{
	realm = 1;
	angle = 2 * PI / SideNum;
	side = 2 * realm * sin(angle / 2);\
	setSide(len);
}

template<int SideNum>
void CPolygon<SideNum>::setSide(double len)
{
	realm = len / side;
	side = len;
	calPerim();
	calArea();
}

template<int SideNum>
double CPolygon<SideNum>::getSide()
{
	return side;
}

template<int SideNum>
void CPolygon<SideNum>::calPerim()
{
	this->perimeter = side * SideNum;
}

template<int SideNum>
void CPolygon<SideNum>::calArea()
{
	this->area = side * realm * cos(angle / 2) * SideNum / 2;
}

template<int SideNum>
void CPolygon<SideNum>::scaling(double factor)
{
	if (factor <= 0) return;
	side = side * factor;
	realm = realm * factor;
	this->perimeter = this->perimeter * factor;
	this->area = this->area * factor * factor;
}

template<int SideNum>
void CPolygon<SideNum>::print()
{
	int i;
	cout << "    Type: Polygon - ";
	switch (SideNum)
	{
	case 3: cout << "Triangle"; break;
	case 4: cout << "Rectangle"; break;
	case 5: cout << "Pentagon"; break;
	case 6: cout << "Hexagon"; break;
	default: cout << "Not Defined"; break;
	}
	cout << endl;
	cout << "    Realm Radius = " << realm << endl;
	cout << "    Number of Sides = " << SideNum << endl;
	cout << "    Length of Sides = " << side << endl;
	cout << "    Angle of Each Side = " << angle * 180 / PI << endl;
	cout << "    Area of the Shape = " << this->area << endl;
	cout << endl;
}


class CSquare :public CShape
{
	double side;
public:
	CSquare();
	CSquare(double);
	~CSquare() {};
	void calPerim();
	void calArea();
	void scaling(double);
	void print();
};

class CRectangle :public CShape
{
	double xside, yside;
public:
	CRectangle();
	CRectangle(double);
	CRectangle(double, double);
	~CRectangle() {};
	void calPerim();
	void calArea();
	void scaling(double);
	void print();
};

class CFreeShape :public CShape
{
	double side;
	// mapping function needed. unfinished. 2001291922
public:
	CFreeShape();
	CFreeShape(double);
	~CFreeShape() {};
	void calPerim();
	void calArea();
	void scaling(double);
	void print();
};


/* Solid Geometry */
class CSolid :public CGeometry
{
protected:
	double surfaceArea;
	double volume;
public:
	CSolid();
	~CSolid() {};
	double getSurface();
	double getVolume();
	virtual void calSurface() {};
	virtual void calVolume() {};
	virtual void scaling(double) {};
	virtual void print() {};
};

class CGlobe :public CSolid
{
	double radius;
public:
	CGlobe();
	CGlobe(double);
	~CGlobe() {};
	void calSurface();
	void calVolume();
	void scaling(double);
	void print();
};

class CCube :public CSolid
{
	double edge;
public:
	CCube();
	CCube(double);
	~CCube() {};
	void calSurface();
	void calVolume();
	void scaling(double);
	void print();
};

class CCuboid :public CSolid
{
	double xedge, yedge, zedge;
public:
	CCuboid();
	CCuboid(double);
	CCuboid(double, double, double);
	~CCuboid() {};
	void calSurface();
	void calVolume();
	void scaling(double);
	void print();
};

class CCylinder :public CSolid
{
	double radius, height;
public:
	CCylinder();
	CCylinder(double, double);
	~CCylinder() {};
	void calSurface();
	void calVolume();
	void scaling(double);
	void print();
};

template<int SideNum>
class CPrism :public CSolid
{
	CPolygon<SideNum> polygon;
	double height;
public:
	CPrism();
	CPrism(double, double);
	~CPrism() {};
	void calSurface();
	void calVolume();
	void scaling(double);
	void print();
};

template<int SideNum>
CPrism<SideNum>::CPrism()
{
	height = 1;
	calSurface();
	calVolume();
}

template<int SideNum>
CPrism<SideNum>::CPrism(double len, double high)
{
	polygon.setSide(len);
	height = high;
	calSurface();
	calVolume();
}

template<int SideNum>
void CPrism<SideNum>::calSurface()
{
	this->surfaceArea = polygon.getArea() * 2 + polygon.getSide() * height * SideNum;
}

template<int SideNum>
void CPrism<SideNum>::calVolume()
{
	this->volume = height * polygon.getArea();
}

template<int SideNum>
void CPrism<SideNum>::scaling(double factor)
{
	if (factor <= 0) return;
	polygon.scaling(factor);
	height = height * factor;
	this->surfaceArea = this->surfaceArea * factor * factor;
	this->volume = height * polygon.getArea();
}

template<int SideNum>
void CPrism<SideNum>::print()
{
	int i;
	cout << "    Type: Prism - ";
	switch (SideNum)
	{
	case 3: cout << "Trianglar Prism"; break;
	case 4: cout << "Tetrahedron Prism"; break;
	case 5: cout << "Pentagonal Prism"; break;
	case 6: cout << "Hexagonal Prism"; break;
	default: cout << "Not Defined"; break;
	}
	cout << endl;
	cout << "Bottom Plate:";
	polygon.print();
	cout << "    Height = " << height << endl;
	cout << "    Volume of the Prism = " << this->volume << endl;
	cout << endl;
}



#endif