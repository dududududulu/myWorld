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
	// focus should be subtracted from grapher, but it is trival and purely a waste of time. 2002051642
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

double Observer::packing_step(dVectordim* dir)
{
	double xlen = abs(dir->getElement(0)), ylen = abs(dir->getElement(1));
	double minlen = xlen;
	if (ylen < minlen) minlen = ylen;
	double ratio = minlen / PixelWidth;
	dir->normalize(dir->getLen() / ratio);
	return ratio;
}

void Observer::line_mapping(const dVectordim& beg, const dVectordim& end, double scale1, double scale2, int color)
{
	/*
	int i;
	dVectordim step = end - beg;
	double beg_len, end_len, cur_len, line_scale, beta;
	double ash[3], ratio;
	beg_len = beg.getLen();
	end_len = end.getLen();
	ash[0] = beg_len * beg_len;
	ash[1] = 2 * beg_len * (end_len - beg_len);
	ash[2] = (end_len - beg_len) * (end_len - beg_len);
	line_scale = packing_step(&step);
	for (i = 0; i < line_scale; ++i)
	{
		ratio = i / line_scale;
		cur_len = sqrt(ash[2] * ratio * ratio + ash[1] * ratio + ash[0]);
		beta = scale1 * (1 - ratio) + scale2 * ratio;
		plot(beg + i * step, cur_len / beta, color);
	}
	plot(end, end_len / scale2, color);
	*/
	int i;
	dVectordim step = end - beg, cur_point = beg;
	double line_scale, beta, ratio;
	line_scale = packing_step(&step);
	for (i = 0; i < line_scale; ++i)
	{
		ratio = i / line_scale;
		beta = scale1 * (1 - ratio) + scale2 * ratio;
		plot(cur_point, cur_point.getLen() / beta, color);
		cur_point = cur_point + step;
	}
	plot(end, end.getLen() / scale2, color);
}

void Observer::shape_mapping(const dVectordim& beg, const dVectordim& lend, const dVectordim& rend, double scale1, double scale2, double scale3, int color)
{
	int l, r;
	dVectordim lstep = lend - beg, rstep = rend - beg;
	dVectordim cur_beg = beg, cur_point;
	double lscale, rscale, beta;
	double lratio, rratio, rmax;
	lscale = packing_step(&lstep);
	rscale = packing_step(&rstep);
	for (l = 0; l < lscale; ++l)
	{
		lratio = l / lscale;
		rmax = rscale * (1 - lratio);
		cur_point = cur_beg;
		for (r = 0; r < rmax; ++r)
		{
			rratio = r / rscale;
			cur_point = cur_point + rstep;
			beta = scale1 * (1 - lratio - rratio) + scale2 * rratio + scale3 * lratio;
			plot(cur_point, cur_point.getLen() / beta, color);
		}
		rratio = rmax / rscale;
		cur_point = cur_beg + rmax * rstep;
		beta = scale2 * rratio + scale3 * lratio;
		plot(cur_point, cur_point.getLen() / beta, color);

		cur_beg = cur_beg + lstep;
	}
	plot(rend, rend.getLen() / scale3, color);
}