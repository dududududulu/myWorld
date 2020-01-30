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
class Base
{
	dMatrix<dim, dim> baseMatrix;
protected:
	void SchmitOrth();
public:
	Base(int = 0);
	~Base() {};
	dVector<dim> project(dVector<dim>&);
	void printBase();
};

template<int dim>
Base<dim>::Base(int type)
{
	if (type == 0) baseMatrix = identity(dim);
	if (type == 1)
	{
		//baseMatrix;
		// unfinished. 2001301424
	}
}

template<int dim>
void Base<dim>::SchmitOrth()
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
dVector<dim> Base<dim>::project(dVector<dim>& vec)
{
	return baseMatrix.transpose() * vec;
}

template<int dim>
void Base<dim>::printBase()
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
	Point<dim> origin;
	Base<dim> base;
public:
	Ref();
	~Ref() {
		delete ref;
	};
	bool isBalanced();
	bool isAbsolute();
	Point<dim> mapping(Point<dim>&);

};



#endif