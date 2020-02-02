#ifndef _REFERENCE_H
#define _REFERENCE_H

#include <iostream>
#include <cstring>
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
	dVector<dim> revert(const dVector<dim>&);                       // revert the vector in this to absolute reference
	dVector<dim> project(const dVector<dim>&);                      // project the absolute vector to this
	dVector<dim> project(const dVector<dim>&, const Ref<dim>&);     // project the Ref vector to this
	void movement(const Motion&);
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
void Ref<dim>::movement(const Motion& motion)
{
	origin = motion.deviate(origin);
	base = motion.deflect(base);
}


#endif