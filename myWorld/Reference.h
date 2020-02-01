#ifndef _REFERENCE_H
#define _REFERENCE_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Reference.h
	Date of Creation:       20200130
	Latest Revise:          20200130

	Description:
		This file claims and defines linear space Base and Ref classes.

	Structure of Classes:
		Base
		1	Ref: sRef / dRef


	///////////////////////////////////////////////////////////////

*/

template<int dim>
class LnBase
{
	dMatrix<dim, dim> baseMatrix;
protected:
	void SchmitOrth();
public:
	LnBase(int = 0);
	~LnBase() {};
	bool isIdentity();
	dVector<dim> project(dVector<dim>&);
	void rotate(const dVector<dim>&);
	void rotate(const uMatrix<double, dim, dim>&);
	void printBase();
};

template<int dim>
LnBase<dim>::LnBase(int type)
{
	if (type == 0) baseMatrix = identity(dim);     // default: identity
	if (type == 1)
	{
		// random baseMatrix;
		// unfinished. 2001301424
	}
}

template<int dim>
void LnBase<dim>::SchmitOrth()
{
	int i, j;
	double projection;
	dVector<dim> cur_col;
	dVector<dim> remove_col;
	for (i = 0; i < dim; ++i)
	{
		cur_col = baseMatrix.getColumn(i);
		for (j = 0; j < i; ++j)
		{
			remove_col = baseMatrix.getColmn(j);
			cur_col = cur_col.extract(remove_col);
		}
		cur_col.normalize();
		baseMatrix.setColumn(cur_col, i);
	}
}

template<int dim>
bool LnBase<dim>::isIdentity()
{
	return baseMatrix.isIdentity();
}

template<int dim>
dVector<dim> LnBase<dim>::project(dVector<dim>& vec)
{
	return baseMatrix.transpose() * vec;
}

template<int dim>
void LnBase<dim>::rotate(const dVector<dim>& torque)
{
	uMatrix<double, dim, dim> R = rotator<double, dim>(torque);
	baseMatrix = R * baseMatrix;
}

template<int dim>
void LnBase<dim>::rotate(const uMatrix<double, dim, dim>& rotMatrix)
{
	baseMatrix = rotMatrix * baseMatrix;
}

template<int dim>
void LnBase<dim>::printBase()
{
	cout << baseMatrix << endl;
}

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
	Ref(dVector<dim>&);
	Ref(dVector<dim>&, dMatrix<dim, dim>);
	~Ref() {};
	bool isBalanced();
	bool isAbsolute();
	dVector<dim> revert(dVector<dim>&);                       // revert the vector in this to absolute reference
	dVector<dim> project(dVector<dim>&);                      // project the absolute vector to this
	dVector<dim> project(dVector<dim>&, Ref<dim>&);           // project the Ref vector to this

};

template<int dim>
Ref<dim>::Ref(dVector<dim>& orig)
{
	origin = orig;
}





#endif