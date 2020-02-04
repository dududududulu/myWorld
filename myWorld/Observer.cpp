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
	graph_init();
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

void Observer::graph_init()
{
	int i, j;
	for(i = 0; i < GLength; ++i)
		for (j = 0; j < GWidth; ++j)
		{
			graph[i][j] = -1;
			distance[i][j] = -1;
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

void Observer::deviate(const dVectordim& vec)
{
	ref.deviate(vec);
}

void Observer::rotate(const dVectordim& vec)
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

void Observer::plot(const dVectordim& local_grapher, const double dist, int color)
{
	int xindex, yindex;
	xindex = local_grapher.getElement(0) / PixelWidth + GXCenter;
	yindex = local_grapher.getElement(1) / PixelWidth + GYCenter;
	if (xindex >= 0 && xindex < GLength && yindex >= 0 && yindex < GWidth)
		if (distance[xindex][yindex] == -1 || distance[xindex][yindex] > dist)
		{
			graph[xindex][yindex] = color;
			distance[xindex][yindex] = dist;
			// the only place where distance matrix can be changed. 2002042345
		}
}

int Observer::packing_step(dVectordim* dir)
{
	double xlen = abs(dir->getElement(0)), ylen = abs(dir->getElement(1));
	double minlen = xlen;
	if (ylen < minlen) minlen = ylen;
	int ans = minlen / PixelWidth;
	dir->normalize(PixelWidth * dir->getLen() / minlen);
	return ans;
}

void Observer::line_mapping(const dVectordim& beg, const dVectordim& end, double scale1, double scale2, int color)
{
	dtVector<2> scale(scale1, scale2);
	dVectordim step = end - beg, cur_point = beg;
	int itr_limit = packing_step(&step), i;
	eMatrix<double, Dimension, 2> frame = beg | end;
	dtVectordim factor = scale * frame.getInv();
	double dist, beta = factor * beg, beta_step = factor * step;
	for (i = 0; i < itr_limit; ++i)
	{
		dist = cur_point.getLen() / beta;
		plot(cur_point - focus, dist, color);
		cur_point = cur_point + step;
		beta = beta + beta_step;
	}
	cur_point = end;
	dist = cur_point.getLen() / scale2;
	plot(cur_point - focus, dist, color);
}