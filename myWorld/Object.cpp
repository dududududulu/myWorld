#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Reference.h"
#include "Entity.h"
#include "Object.h"
using namespace std;


/*

	///////////////////////////////////////////////////////////////

	File Name:              Object.cpp
	Date of Creation:       20200131
	Latest Revise:          20200131

	Description:
		This file defines Object classes.

	///////////////////////////////////////////////////////////////

*/


Geometry::Geometry(int GType, int GMaterial, double size1, double size2, double size3) :Element()
{
	switch (GType)
	{
	case line_geo: cgeo = new CLine(size1); break;

	case circle_geo: cgeo = new CCircle(size1); break;
	case square_geo: cgeo = new CSquare(size1); break;
	case rectangle_geo: cgeo = new CRectangle(size1, size2); break;
	case triangle_geo: cgeo = new CPolygon<3>(size1); break;
	case rectagon_geo: cgeo = new CPolygon<4>(size1); break;
	case pendagon_geo: cgeo = new CPolygon<5>(size1); break;
	case hexagon_geo: cgeo = new CPolygon<6>(size1); break; 

	case globe_geo: cgeo = new CGlobe(size1); break;
	case cube_geo: cgeo = new CCube(size1); break;
	case triprism_geo: cgeo = new CPrism<3>(size1, size2); break;
	case cuboid_geo: cgeo = new CCuboid(size1, size2, size3); break;
	case cylinder_geo: cgeo = new CCylinder(size1, size2); break;

	default: cgeo = nullptr; break;
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

void Geometry::init()
{
	
}

void Geometry::print()
{
	// Entity print(); unfinished, 2002021700
	cgeo->print();
}



void Line::display(Observer* eye)
{
	eye->mapping(vertex, this->color, frame_packing);
}

void Circle::display(Observer* eye)
{
	//eye->mapping(vertex, this->color, frame_packing);
	// unfinished. 2002051926
}

void Square::display(Observer* eye)
{
	eye->mapping(vertex, this->color, plane_packing);
}

void Rectangle::display(Observer* eye)
{
	eye->mapping(vertex, this->color, plane_packing);
}



bool Solid::checkLineVisible(int i)
{
	if (i < 0 || i >= line_num) return 0;
	// unfinished.
	return 1;
}

bool Solid::checkShapeVisible(int i)
{
	if (i < 0 || i >= shape_num) return 0;
	// unfinished.
	return 1;
}

void Solid::display(Observer* eye)
{
	// unfinished. 2002051951
	int i;
	for (i = 0; i < line_num; ++i)
		if (checkLineVisible(i)) line[i].display(eye);
	for (i = 0; i < shape_num; ++i)
		if (checkShapeVisible(i)) shape[i].display(eye);
}

void Globe::materialize()
{
	// unfinished. 2002051951
}

void Cube::materialize()
{
	double edge = this->cgeo->getVal(), size = edge / 2;
	double base[Dimension][Dimension];
	dVectordim orig = this->ref.getOrigin(), drift;
	this->shape_num = 6;
	this->shape = new Square[shape_num];
	for (int i = 0; i < shape_num; ++i)
		this->shape[i].resize(edge);

	drift.setVal(size, 0, 0);
	base[0][0] = 0; base[1][0] = 1; base[2][0] = 0;
	base[0][1] = 0; base[1][1] = 0; base[2][1] = 1;
	base[0][2] = 1; base[1][2] = 0; base[2][2] = 0;
	this->shape[0].setRef(orig + drift);
	this->shape[0].setRef(base);

	base[0][0] = 0; base[1][0] = 0; base[2][0] = 1;
	base[0][1] = 0; base[1][1] = 1; base[2][1] = 0;
	base[0][2] = -1; base[1][2] = 0; base[2][2] = 0;
	this->shape[1].setRef(orig - drift);
	this->shape[1].setRef(base);
	
	drift.setVal(0, 0, size);
	base[0][0] = 1; base[1][0] = 0; base[2][0] = 0;
	base[0][1] = 0; base[1][1] = 1; base[2][1] = 0;
	base[0][2] = 0; base[1][2] = 0; base[2][2] = 1;
	this->shape[2].setRef(orig + drift);
	this->shape[2].setRef(base);

	base[0][0] = 0; base[1][0] = 1; base[2][0] = 0;
	base[0][1] = 1; base[1][1] = 0; base[2][1] = 0;
	base[0][2] = 0; base[1][2] = 0; base[2][2] = -1;
	this->shape[3].setRef(orig - drift);
	this->shape[3].setRef(base);

	drift.setVal(0, size, 0);
	base[0][0] = 0; base[1][0] = 0; base[2][0] = 1;
	base[0][1] = 1; base[1][1] = 0; base[2][1] = 0;
	base[0][2] = 0; base[1][2] = 1; base[2][2] = 0;
	this->shape[2].setRef(orig + drift);
	this->shape[2].setRef(base);

	base[0][0] = 1; base[1][0] = 0; base[2][0] = 0;
	base[0][1] = 0; base[1][1] = 0; base[2][1] = 1;
	base[0][2] = 0; base[1][2] = -1; base[2][2] = 0;
	this->shape[3].setRef(orig - drift);
	this->shape[3].setRef(base);
}

void Cuboid::materialize()
{
	double xedge = this->cgeo->getVal(0), yedge = this->cgeo->getVal(1), zedge = this->cgeo->getVal(2);
	double xsize = xedge / 2, ysize = yedge / 2, zsize = zedge / 2;
	double base[Dimension][Dimension];
	dVectordim orig = this->ref.getOrigin(), drift;
	this->shape_num = 6;
	this->shape = new Rectangle[shape_num];
	for (int i = 0; i < shape_num; ++i)
		this->shape[i].resize(xedge, yedge, zedge);

	drift.setVal(xsize, 0, 0);
	base[0][0] = 0; base[1][0] = 1; base[2][0] = 0;
	base[0][1] = 0; base[1][1] = 0; base[2][1] = 1;
	base[0][2] = 1; base[1][2] = 0; base[2][2] = 0;
	this->shape[0].setRef(orig + drift);
	this->shape[0].setRef(base);

	base[0][0] = 0; base[1][0] = 0; base[2][0] = 1;
	base[0][1] = 0; base[1][1] = 1; base[2][1] = 0;
	base[0][2] = -1; base[1][2] = 0; base[2][2] = 0;
	this->shape[1].setRef(orig - drift);
	this->shape[1].setRef(base);

	drift.setVal(0, 0, zsize);
	base[0][0] = 1; base[1][0] = 0; base[2][0] = 0;
	base[0][1] = 0; base[1][1] = 1; base[2][1] = 0;
	base[0][2] = 0; base[1][2] = 0; base[2][2] = 1;
	this->shape[2].setRef(orig + drift);
	this->shape[2].setRef(base);

	base[0][0] = 0; base[1][0] = 1; base[2][0] = 0;
	base[0][1] = 1; base[1][1] = 0; base[2][1] = 0;
	base[0][2] = 0; base[1][2] = 0; base[2][2] = -1;
	this->shape[3].setRef(orig - drift);
	this->shape[3].setRef(base);

	drift.setVal(0, ysize, 0);
	base[0][0] = 0; base[1][0] = 0; base[2][0] = 1;
	base[0][1] = 1; base[1][1] = 0; base[2][1] = 0;
	base[0][2] = 0; base[1][2] = 1; base[2][2] = 0;
	this->shape[2].setRef(orig + drift);
	this->shape[2].setRef(base);

	base[0][0] = 1; base[1][0] = 0; base[2][0] = 0;
	base[0][1] = 0; base[1][1] = 0; base[2][1] = 1;
	base[0][2] = 0; base[1][2] = -1; base[2][2] = 0;
	this->shape[3].setRef(orig - drift);
	this->shape[3].setRef(base);
}