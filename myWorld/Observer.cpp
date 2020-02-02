#include <iostream>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Reference.h"
#include "Effect.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Observer.cpp
	Date of Creation:       20200202
	Latest Revise:          20200202

	Description:
		This file defines Observer classes.

	Structure of Classes:
		Observer


	///////////////////////////////////////////////////////////////

*/


Observer::Observer(double d, int setview)
{
	setDepth(d);
	setView(setview);
}

void Observer::view_graph(int xindex, int yindex, int color)
{
	switch (view)
	{
	case UpView: xindex = GXCenter + xindex; yindex = GYCenter + yindex; break;
	case DownView: xindex = GXCenter - xindex; yindex = GYCenter - yindex; break;
	case RightView: xindex = GXCenter + yindex; yindex = GYCenter - xindex; break;
	case LeftView: xindex = GXCenter - yindex; yindex = GYCenter + xindex; break;
	default: xindex = GXCenter + xindex; yindex = GYCenter + yindex;
	}

}

void Observer::setView(int setview)
{
	view = setview;
}

int Observer::getView()
{
	return view;
}

void Observer::setDepth(double d)
{
	focus.setElement(d, 2);
	depth = d;
}

double Observer::getDepth()
{
	return depth;
}

void Observer::deviate(const dVector<Dimension>& vec)
{
	ref.deviate(vec);
}

void Observer::rotate(const dVector<Dimension>& vec)
{
	ref.rotate(vec);
}

void Observer::rotate(const dMatrix<Dimension, Dimension>& mat)
{
	ref.rotate(mat);
}

void Observer::movement(const Motion& motion)
{
	ref.movement(motion);
}

double Observer::mapping(const dVector<Dimension>& vec, int color)    // vec is an absolute vector.
{
	int xindex, yindex;
	double step, scale;
	dVector<Dimension> grapher, rvec = ref.project(vec);
	scale = depth * depth / focus.dot(rvec);
	step = PixelWidth / scale / 2;
	grapher = scale * rvec - focus;
	xindex = grapher.getElement(0) / PixelWidth + GXCenter;
	yindex = grapher.getElement(1) / PixelWidth + GYCenter;
	if (xindex >= 0 && xindex < GLength && yindex >= 0 && yindex < GWidth)
	{
		if (distance[xindex][yindex] == -1 || distance[xindex][yindex] > rvec.getLen())
			graph[xindex][yindex] = color;
	}
	return step;
}
