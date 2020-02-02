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




