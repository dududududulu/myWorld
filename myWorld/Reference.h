#ifndef _REFERENCE_H
#define _REFERENCE_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Effect.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Reference.h
	Date of Creation:       20200130
	Latest Revise:          20200202

	Description:
		This file claims and defines linear space Base and Ref classes.

	Structure of Classes:
		Base
		1	Ref: sRef / dRef


	///////////////////////////////////////////////////////////////

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<int dim> class Ref;
template<int dim> class sRef;
template<int dim> class dRef;

template<int dim>
class Ref
{
	dVector<dim> origin;        // default: all zeros
	LnBase<dim> base;           // default: identity
public:
	Ref() {};
	Ref(const dVector<dim>&);
	Ref(const dVector<dim>&, const dMatrix<dim, dim>&);
	~Ref() {};
	bool isBalanced();
	bool isAbsolute();
	void setOrigin(const dVector<dim>&);
	void setBase(const dMatrix<dim, dim>&);
	dVector<dim> getOrigin();
	dVector<dim> revert(const dVector<dim>&);                       // revert the vector in this to absolute reference
	dVector<dim> project(const dVector<dim>&);                      // project the absolute vector to this
	dVector<dim> project(const dVector<dim>&, const Ref<dim>&);     // project the Ref vector to this

	template<int num>
	dMatrix<dim, num> revert(const dMatrix<dim, num>&);                       // revert the vector in this to absolute reference
	template<int num>
	dMatrix<dim, num> project(const dMatrix<dim, num>&);                      // project the absolute vector to this
	template<int num>
	dMatrix<dim, num> project(const dMatrix<dim, num>&, const Ref<dim>&);     // project the Ref vector to this

	void deviate(const dVector<dim>&);
	void rotate(const dVector<dim>&);
	void rotate(const dMatrix<dim, dim>&);
	void movement(const Motion&);
	void operator=(const Ref<dim>&);
};

template<int dim>
Ref<dim>::Ref(const dVector<dim>& orig)
{
	setOrigin(orig);
}

template<int dim>
Ref<dim>::Ref(const dVector<dim>& orig, const dMatrix<dim, dim>& mat)
{
	setOrigin(orig);
	setBase(mat);
}

template<int dim>
bool Ref<dim>::isBalanced()
{
	return base.isIdentity();
}

template<int dim>
bool Ref<dim>::isAbsolute()
{
	return (base.isIdentity() & origin.isOrigin());
}

template<int dim>
void Ref<dim>::setOrigin(const dVector<dim>& orig)
{
	origin = orig;
}

template<int dim>
void Ref<dim>::setBase(const dMatrix<dim, dim>& mat)
{
	base.setMatrix(mat);
}

template<int dim>
dVector<dim> Ref<dim>::getOrigin()
{
	return origin;
}

template<int dim>
dVector<dim> Ref<dim>::revert(const dVector<dim>& rvec)                       // revert the vector in this to absolute reference
{
	dVector<dim> result;
	result = base.revert(rvec) + origin;
	return result;
}

template<int dim>
dVector<dim> Ref<dim>::project(const dVector<dim>& avec)                      // project the absolute vector to this
{
	dVector<dim> result;
	result = base.project(avec - origin);
	return result;
}

template<int dim>
dVector<dim> Ref<dim>::project(const dVector<dim>& rvec, const Ref<dim>& ref)           // project the Ref vector to this
{
	dVector<dim> result;
	result = project(ref.revert(rvec));
	return result;
}

template<int dim>
template<int num>
dMatrix<dim, num> Ref<dim>::revert(const dMatrix<dim, num>& rmat)                       // revert the vector in this to absolute reference
{
	dMatrix<dim, num> result;
	result = base.revert(rmat) + origin;
	return result;
}

template<int dim>
template<int num>
dMatrix<dim, num> Ref<dim>::project(const dMatrix<dim, num>& amat)                      // project the absolute vector to this
{
	dMatrix<dim, num> result;
	result = base.project(amat - origin);
	return result;
}

template<int dim>
template<int num>
dMatrix<dim, num> Ref<dim>::project(const dMatrix<dim, num>& rmat, const Ref<dim>& ref)           // project the Ref vector to this
{
	dMatrix<dim, num> result;
	result = project(ref.revert(rmat));
	return result;
}

template<int dim>
void Ref<dim>::deviate(const dVector<dim>& vec)
{
	setOrigin(origin + vec);
}

template<int dim>
void Ref<dim>::rotate(const dVector<dim>& vec)
{
	base.rotate(vec);
}

template<int dim>
void Ref<dim>::rotate(const dMatrix<dim, dim>& mat)
{
	base.rotate(mat);
}

template<int dim>
void Ref<dim>::movement(const Motion& motion)
{
	origin = motion.deviate(origin);
	base = motion.deflect(base);
}

template<int dim>
void Ref<dim>::operator=(const Ref<dim>& ref)
{
	setOrigin(ref.origin);
	setBase(ref.base);
}

//////////////////////////////////////////////////////////////////////    Observer

class Observer
{
	Ref<Dimension> ref;
	double depth;
	int view;
	dVectordim focus;
	int graph[GLength][GWidth];
	double distance[GLength][GWidth];
protected:
	void graph_init();
	void view_graph(int, int, int = 0);
public:
	Observer(double = 1, int = UpView);
	~Observer() {};
	void setView(int);
	int getView();
	void setDepth(double);
	double getDepth();
	void deviate(const dVectordim&);
	void rotate(const dVectordim&);
	void rotate(const dMatrix<Dimension, Dimension>&);
	void movement(const Motion&);
	int packing_step(dVectordim*);

	void plot(const dVectordim&, const double, int);
	template<int num>
	void plot(const dMatrix<Dimension, num>&, const dtVector<num>&, int);
	template<int num>
	void mapping(const dMatrix<Dimension, num>&, int, int = point_packing);

	void line_mapping(const dVectordim&, const dVectordim&, double, double, int);
	template<int num>
	void frame_mapping(const dMatrix<Dimension, num>&, int);
	template<int num>
	void connect_mapping(const dMatrix<Dimension, num>&, int);
	template<int num>
	void shape_mapping(const dMatrix<Dimension, num>&, int);
};

template<int num>
void Observer::plot(const dMatrix<Dimension, num>& local_grapher, const dtVector<num>& dist, int color)
{
	for (int i = 0; i < num; ++i)
		plot(local_grapher.getColumn(i), dist.getElement(i), color);
}

template<int num>
void Observer::mapping(const dMatrix<Dimension, num>& amat, int color, int type)
{
	int i, xindex, yindex;
	dMatrix<Dimension, num> mat = ref.project(amat);
	dtVector<num> dist = mat.getColLen();
	dtVector<num> scaling = (depth * depth) / (mat.transpose() * focus);
	dMatrix<Dimension, num> mirror = mat * scaling.transpose(), local_grapher = mirror - focus;
	plot(local_grapher, dist, color);
	switch (type)
	{    // unfinished. 2002050050
	case point_packing: break;
	case frame_packing: frame_mapping(); break;
	case connect_packing: connect_mapping(); break;
	case shape_packing: shape_mapping();
	default: break;
	}
}

template<int num>
void Observer::frame_mapping(const dMatrix<Dimension, num>& mat, int color)
{
	int j, xindex, yindex;
	dVectordim beg, end, dir, cur_point, step;
	eMatrix<double, Dimension, 2> frame;
	eMatrix<double, 2, Dimension> frameInv;
	for (j = 0; j < num - 1; ++j)
	{
		beg = mat.getColumn(j);
		end = mat.getColumn(j + 1);
		line_mapping(beg, end, scaling);

	}
}

#endif