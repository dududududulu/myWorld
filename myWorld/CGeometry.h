#ifndef _CGEOMETRY_H
#define _CGEOMETRY_H

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

	File Name:              CGeometry.h
	Date of Creation:       20200202
	Latest Revise:          20200202

	Description:
		This file claims and defines CFigure classes.

	Structure of Classes:
		Concept
		1	CFigure
		1	2	CGeometry
		1	2	3	CLine
		1	2	3	CShape: CSquare / CRectangle / CCircle / CPolygon<SideNum> / CFreeShape / *CCurve
		1	2	3	CSolid: CCube / CCuboid / CGlobe / CCylinder / CPrism<SideNum> / CFreeSolid / *CSurface
		1	2	*CPattern


	///////////////////////////////////////////////////////////////

*/

class CGeometry :public CFigure
{
protected:
	virtual void calPerim() {};
	virtual void calArea() {};
	virtual void calSurface() {};
	virtual void calVolume() {};
	void update()
	{
		calPerim();
		calArea();
		calSurface();
		calVolume();
	};
public:
	CGeometry() :CFigure() {};
	~CGeometry() {};
	//virtual bool isInside(const dVector2d&) { return 0; };
	virtual double getPerim() { return 0; };
	virtual double getArea() { return 0; };
	virtual double getSurface() { return 0; };
	virtual double getVolume() { return 0; };
	virtual void resize(double, double = 1, double = 1) {};
	virtual void scaling(double) {};
	virtual void print() {};
};

class CLine :public CGeometry
{
protected:
	double length;
public:
	CLine(double = 1);
	~CLine() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

class CShape :public CGeometry
{
protected:
	virtual void calPerim() {};
	virtual void calArea() {};
	virtual void calSurface() {};
	virtual void calVolume() {};
	double perimeter;
	double area;
public:
	CShape();
	~CShape() {};
	double getPerim();
	double getArea();
	virtual void resize(double, double = 1, double = 1) {};
	virtual void scaling(double) {};
	virtual void print() {};
};

class CCircle :public CShape
{
	double radius;
protected:
	void calPerim();
	void calArea();
public:
	CCircle(double = 1);
	~CCircle() {};
	void resize(double, double = 1, double = 1);
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
protected:
	void calPerim();
	void calArea();
public:
	CPolygon();
	CPolygon(double);
	~CPolygon() {};
	bool isInside(const dVector2d&);
	void setRealm(double = 1);
	double getRealm();
	void setSide(double = 1);
	double getSide();
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

template<int SideNum>
CPolygon<SideNum>::CPolygon()
{
	realm = 1;
	angle = 2 * PI / SideNum;
	side = 2 * realm * sin(angle / 2);
	this->update();
}

template<int SideNum>
CPolygon<SideNum>::CPolygon(double len)
{
	realm = 1;
	angle = 2 * PI / SideNum;
	side = 2 * realm * sin(angle / 2);
	setRealm(len);
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
void CPolygon<SideNum>::setRealm(double len)
{
	scaling(len);
}

template<int SideNum>
double CPolygon<SideNum>::getRealm()
{
	return realm;
}

template<int SideNum>
void CPolygon<SideNum>::setSide(double len)
{
	scaling(len / side);
}

template<int SideNum>
double CPolygon<SideNum>::getSide()
{
	return side;
}

template<int SideNum>
void CPolygon<SideNum>::resize(double realm, double ash1, double ash2)
{
	setRealm(realm);
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
protected:
	void calPerim();
	void calArea();
public:
	CSquare(double = 1);
	~CSquare() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

class CRectangle :public CShape
{
	double xside, yside;
protected:
	void calPerim();
	void calArea();
public:
	CRectangle(double = 1);
	CRectangle(double, double);
	~CRectangle() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

class CFreeShape :public CShape
{
	double side;
	// mapping function needed. unfinished. 2001291922
protected:
	void calPerim();
	void calArea();
	// unfinished. 2002021607
public:
	CFreeShape(double = 1);
	~CFreeShape() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};


/* Solid Geometry */
class CSolid :public CGeometry
{
protected:
	double surfaceArea;
	double volume;
protected:
	virtual void calSurface() {};
	virtual void calVolume() {};
public:
	CSolid();
	~CSolid() {};
	double getSurface();
	double getVolume();
	virtual void resize(double, double = 1, double = 1) {};
	virtual void scaling(double) {};
	virtual void print() {};
};

class CGlobe :public CSolid
{
	double radius;
protected:
	void calSurface();
	void calVolume();
public:
	CGlobe(double = 1);
	~CGlobe() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

class CCube :public CSolid
{
	double edge;
protected:
	void calSurface();
	void calVolume();
public:
	CCube(double = 1);
	~CCube() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

class CCuboid :public CSolid
{
	double xedge, yedge, zedge;
protected:
	void calSurface();
	void calVolume();
public:
	CCuboid(double = 1);
	CCuboid(double, double, double);
	~CCuboid() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

class CCylinder :public CSolid
{
	double radius, height;
protected:
	void calSurface();
	void calVolume();
public:
	CCylinder(double = 1, double = 1);
	~CCylinder() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

template<int SideNum>
class CPrism :public CSolid
{
	CPolygon<SideNum> polygon;
	double height;
protected:
	void calSurface();
	void calVolume();
public:
	CPrism();
	CPrism(double, double);
	~CPrism() {};
	void resize(double, double = 1, double = 1);
	void scaling(double);
	void print();
};

template<int SideNum>
CPrism<SideNum>::CPrism()
{
	height = 1;
	this->update();
}

template<int SideNum>
CPrism<SideNum>::CPrism(double len, double high)
{
	polygon.setSide(len);
	height = high;
	this->update();
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
void CPrism<SideNum>::resize(double realm, double high, double ash)
{
	polygon.setRealm(realm);
	height = high;
	this->update();
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