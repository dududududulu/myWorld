#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Concept.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              CGeometry.cpp
	Date of Creation:       20200129
	Latest Revise:          20200129

	Description:
		This file claims and defines Concept classes.

	Structure of Classes:
		Concept
		1	CGeometry
		1	2	CLine
		1	2	CShape: CSquare / CRectangle / CCircle / CTriangle / CPolygon<SideNum> / CFreeShape
		1	2	CSolid: CCube / CCuboid / CGlobe / CCylinder / CPrism<SideNum> / CFreeSolid


	///////////////////////////////////////////////////////////////

*/

/* Public functions of class CLine */
CLine::CLine() :CGeometry()
{
	length = -1;
}

CLine::CLine(double len) : CGeometry()
{
	if (len > 0) length = len;
	else length = -1;
}

void CLine::scaling(double factor)
{
	if (factor <= 0) return;
	length = length * factor;
}

void CLine::print()
{
	cout << "    Length = " << length << endl;
}


/* Public functions of class CShape */
CShape::CShape() :CGeometry()
{
	perimeter = -1;
	area = -1;
}

double CShape::getPerim()
{
	return perimeter;
}

double CShape::getArea()
{
	return area;
}

/* Public functions of class CCircle */
CCircle::CCircle() :CShape()
{
	radius = 1;		// unit circle.
	calPerim();
	calArea();
}

CCircle::CCircle(double r)
{
	if (r > 0) radius = r;
	else radius = 1;
	calPerim();
	calArea();
}

void CCircle::calPerim()
{
	this->perimeter = PI * 2 * radius;
}

void CCircle::calArea()
{
	this->area = PI * radius * radius;
}

void CCircle::scaling(double factor)
{
	if (factor <= 0) return;
	radius = radius * factor;
	this->perimeter = this->perimeter * factor;
	this->area = this->area * factor * factor;
}

void CCircle::print()
{
	cout << "    Type: Flate Shape - Circle";
	cout << "    Radius = " << radius << endl;
	cout << "    Perimeter = " << this->perimeter << endl;
	cout << "    Area = " << this->area << endl;
	cout << endl;
}

/* Public functions of class CSquare */
CSquare::CSquare() :CShape()
{
	side = 2;		// unit square.
	calPerim();
	calArea();
}

CSquare::CSquare(double len) : CShape()
{
	if (len > 0) side = len;
	else side = 2;
	calPerim();
	calArea();
}

void CSquare::calPerim()
{
	this->perimeter = side * 4;
}

void CSquare::calArea()
{
	this->area = side * side;
}

void CSquare::scaling(double factor)
{
	if (factor <= 0) return;
	side = side * factor;
	this->perimeter = this->perimeter * factor;
	this->area = this->area * factor * factor;
}

void CSquare::print()
{
	cout << "    Type: Flate Shape - Square";
	cout << "    Length of Sides = " << side << endl;
	cout << "    Perimeter = " << this->perimeter << endl;
	cout << "    Area = " << this->area << endl;
	cout << endl;
}

/* Public functions of class CRectangle */
CRectangle::CRectangle() :CShape()
{
	xside = 2;		// unit square.
	yside = 2;
	calPerim();
	calArea();
}

CRectangle::CRectangle(double len) : CShape()
{
	// unprotected. 2001292308
	xside = len;
	yside = len;
	calPerim();
	calArea();
}

CRectangle::CRectangle(double xlen, double ylen) : CShape()
{
	// unprotected. 2001292308
	xside = xlen;
	yside = ylen;
	calPerim();
	calArea();
}

void CRectangle::calPerim()
{
	this->perimeter = (xside + yside) * 2;
}

void CRectangle::calArea()
{
	this->area = xside * yside;
}

void CRectangle::scaling(double factor)
{
	if (factor <= 0) return;
	xside = xside * factor;
	yside = yside * factor;
	this->perimeter = this->perimeter * factor;
	this->area = this->area * factor * factor;
}

void CRectangle::print()
{
	cout << "    Type: Flate Shape - Rectangle";
	cout << "    Length of Sides = " << xside << ", " << yside << endl;
	cout << "    Perimeter = " << this->perimeter << endl;
	cout << "    Area = " << this->area << endl;
	cout << endl;
}

/* Public functions of class CFreeShape */
// unfinished. 2001292303


/* Public functions of class CSolid */
CSolid::CSolid() :CGeometry()
{
	surfaceArea = -1;
	volume = -1;
}

double CSolid::getSurface()
{
	return surfaceArea;
}

double CSolid::getVolume()
{
	return volume;
}

/* Public functions of class CGlobe */
CGlobe::CGlobe() :CSolid()
{
	radius = 1;		// unit globe.
	calSurface();
	calVolume();
}

CGlobe::CGlobe(double r) :CSolid()
{
	if (r > 0) radius = r;
	else radius = 1;
	calSurface();
	calVolume();
}

void CGlobe::calSurface()
{
	this->surfaceArea = 4 * PI * radius * radius;
}

void CGlobe::calVolume()
{
	this->volume = 4 * PI * radius * radius * radius / 3;
}

void CGlobe::scaling(double factor)
{
	if (factor <= 0) return;
	radius = radius * factor;
	this->surfaceArea = this->surfaceArea * factor * factor;
	this->volume = this->volume * factor * factor * factor;
}

void CGlobe::print()
{
	cout << "    Type: Solid Shape - Globe";
	cout << "    Radius = " << radius << endl;
	cout << "    Area of Surface = " << this->surfaceArea << endl;
	cout << "    Volume = " << this->volume << endl;
	cout << endl;
}

/* Public functions of class CCube */
CCube::CCube() :CSolid()
{
	edge = 1;		// unit globe.
	calSurface();
	calVolume();
}

CCube::CCube(double len) :CSolid()
{
	if (len > 0) edge = len;
	else edge = 1;
	calSurface();
	calVolume();
}

void CCube::calSurface()
{
	this->surfaceArea = 6 * edge * edge;
}

void CCube::calVolume()
{
	this->volume = edge * edge * edge;
}

void CCube::scaling(double factor)
{
	if (factor <= 0) return;
	edge = edge * factor;
	this->surfaceArea = this->surfaceArea * factor * factor;
	this->volume = this->volume * factor * factor * factor;
}

void CCube::print()
{
	cout << "    Type: Solid Shape - Cube";
	cout << "    Length of Edges = " << edge << endl;
	cout << "    Area of Surface = " << this->surfaceArea << endl;
	cout << "    Volume = " << this->volume << endl;
	cout << endl;
}

/* Public functions of class CCuboid */
CCuboid::CCuboid() :CSolid()
{
	xedge = 1;		// unit globe.
	yedge = 1;
	zedge = 1;
	calSurface();
	calVolume();
}

CCuboid::CCuboid(double len) :CSolid()
{
	// unprotected. 2001292319
	xedge = len;
	yedge = len;
	zedge = len;
	calSurface();
	calVolume();
}

CCuboid::CCuboid(double xlen, double ylen, double zlen) :CSolid()
{
	// unprotected. 2001292319
	xedge = xlen;
	yedge = ylen;
	zedge = zlen;
	calSurface();
	calVolume();
}

void CCuboid::calSurface()
{
	this->surfaceArea = (xedge * yedge + yedge * zedge + zedge * xedge) * 2;
}

void CCuboid::calVolume()
{
	this->volume = xedge * yedge * zedge;
}

void CCuboid::scaling(double factor)
{
	if (factor <= 0) return;
	xedge = xedge * factor;
	yedge = yedge * factor;
	zedge = zedge * factor;
	this->surfaceArea = this->surfaceArea * factor * factor;
	this->volume = this->volume * factor * factor * factor;
}

void CCuboid::print()
{
	cout << "    Type: Solid Shape - Cuboid";
	cout << "    Length of Edges = " << xedge << ", " << yedge << ", " << zedge << endl;
	cout << "    Area of Surface = " << this->surfaceArea << endl;
	cout << "    Volume = " << this->volume << endl;
	cout << endl;
}

/* Public functions of class CCylinder */
CCylinder::CCylinder() :CSolid()
{
	radius = 1;		// unit globe.
	height = 1;
	calSurface();
	calVolume();
}

CCylinder::CCylinder(double r, double high) :CSolid()
{
	// unprotected. 2001292319
	radius = r;
	height = high;
	calSurface();
	calVolume();
}

void CCylinder::calSurface()
{
	this->surfaceArea = 2 * PI * radius * (radius + height);
}

void CCylinder::calVolume()
{
	this->volume = PI * radius * radius * height;
}

void CCylinder::scaling(double factor)
{
	if (factor <= 0) return;
	radius = radius * factor;
	height = height * factor;
	this->surfaceArea = this->surfaceArea * factor * factor;
	this->volume = this->volume * factor * factor * factor;
}

void CCylinder::print()
{
	cout << "    Type: Solid Shape - Cylinder";
	cout << "    Radius = " << radius << endl;
	cout << "    Height = " << height << endl;
	cout << "    Area of Surface = " << this->surfaceArea << endl;
	cout << "    Volume = " << this->volume << endl;
	cout << endl;
}

/* Public functions of class CFreeSolid */
// unfinished. 2001292341