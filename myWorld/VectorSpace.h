
#ifndef _VECTORSPACE_H
#define _VECTORSPACE_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "settings.h"
#include "Matrix.h"
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              VectorSpace.h
	Date of Creation:       20200102
	Latest Revise:          20200129

	Description:
		This file claims and defines template class Vector and tVector for any type of statistic data and any dimension.

	Abbreviations:
		dVector<dim>	=	Vector<double, dim>
		dVector2d		=	Vector<double, 2>
		dVector3d		=	Vector<double, 3>

	///////////////////////////////////////////////////////////////

*/

template<typename T, int dim>
class _VectorAccessory
{
protected:
	T length;
	T direction[dim];
protected:
	void default_init();
public:
	_VectorAccessory() { default_init(); };
	~_VectorAccessory() {};
	T getLen() { return length; };
	T* getDir() { return direction; };
};

template<typename T, int dim>
void _VectorAccessory<T, dim>::default_init()
{
	length = -1;
	for (int i = 0; i < dim; ++i)
		direction[i] = 0;
}



template<typename T, int dim>
class Vector;
template<typename T, int dim>
class tVector;

template<int dim> using dVector = Vector<double, dim>;
using dVector2d = Vector<double, 2>;
using dVector3d = Vector<double, 3>;

template<typename T, int dim>
class Vector :public _Vector<T, dim>, public _VectorAccessory<T, dim>
{
protected:
	template<typename T, int dim> friend class Vector;
	template<typename T, int dim> friend class tVector;
	template<typename T, int mRows, int nCols> friend class uMatrix;

	void zero();								// zero the vector.
	void ones(int = 1);
	void update();

	template<int colDim>
	uMatrix<T, dim, colDim + 1> stitch(const uMatrix<T, dim, colDim>&, bool = 0)const;    // stitch with mat from the right.
	uMatrix<T, dim, 2> stitch(const Vector<T, dim>&)const;                                // stitch with vec from the right.
	template<int newDim>
	Vector<T, dim + newDim> graft(const Vector<T, newDim>&)const;                         // graft mat from buttom.

	Vector<T, dim> add(const Vector<T, dim>&)const;                                 // + vec.
	Vector<T, dim> add(const T&)const;                                              // + k.
	Vector<T, dim> minus(const Vector<T, dim>&)const;                               // - vec.
	Vector<T, dim> minusf(const T&)const;                                           // k - my.
	Vector<T, dim> _multiple(const T&)const;                                        // .* k.
	Vector<T, dim> _multiple(const Vector<T, dim>&)const;                           // .* vec.
	Vector<T, dim> cross(const Vector<T, dim>& vec)const;                           // cross vec.

	template<int colDim>
	uMatrix<T, dim, colDim> multiple(const tVector<T, colDim>&)const;               // * tvec.
	template<int colDim>
	uMatrix<T, dim, colDim> _multiple(const uMatrix<T, dim, colDim>&)const;         // .* mat.
	template<int rowDim>
	Vector<T, rowDim> multipleb(const uMatrix<T, rowDim, dim>&)const;               // mat * vec.

public:
	Vector(int = 0, int = 0);                        // default constructor.
	Vector(T&);                                      // constructor.
	Vector(T*);                                      // constructor.
	Vector(const Vector<T, dim>&);                   // copy constructor.
	Vector(const Vector<T, dim>*);                   // copy constructor.
	~Vector() {                                      // destructor.
		// unfinished. inform needed.
		//cout << "- Destructor Vector." << endl;
	};
	T& toVal();                                      // convert to T if dimension == 1.
	int getDim() { return dim; };                    // get dimension.
	T& getVal(int);                                  // get the ith value of the vector.
	T& getLen() { return this->calLen(); };          // get length of the vector.
	T* getDir() { return this->calDir(); };          // get the direction of the vector.
	T& dot(Vector<T, dim>&);                         // * target vec.
	T& project(Vector<T, dim>&);                     // get the projection on the target vec.
	Vector<T, dim> projectVec(Vector<T, dim>&);      // get the component parallel with the target vec.
	Vector<T, dim> extract(Vector<T, dim>&);         // get the component orthogonal to the target vec.
	void normalize(T& = 1);                          // normalize the vector under specific scale.
	tVector<T, dim> transpose();                     // transpose.
	void operator=(const Vector<T, dim>);            // = overload.
	//friend ostream& operator<<<T, dim>(ostream& s, Vector<T, dim>&);    // << overload.
	// unfinished. 2001301525

	template<int colDim>
	friend uMatrix<T, dim, colDim + 1> operator|(const Vector<T, dim>& my, const uMatrix<T, dim, colDim>& mat) { return my.stitch(mat, 0); };
	template<int colDim>
	friend uMatrix<T, dim, colDim + 1> operator|(const uMatrix<T, dim, colDim>& mat, const Vector<T, dim>& my) { return my.stitch(mat, 1); };
	friend uMatrix<T, dim, 2> operator|(const Vector<T, dim>& my, const Vector<T, dim>& vec) { return my.stitch(vec); };
	template<int newDim>
	friend Vector<T, dim + newDim> operator/(const Vector<T, dim>& my, const Vector<T, newDim>& vec) { return my.graft(vec); };

	friend Vector<T, dim> operator+(const Vector<T, dim>& my, const Vector<T, dim>& vec) { return my.add(vec); };
	friend Vector<T, dim> operator+(const Vector<T, dim >& my, const T& k) { return my.add(k); };
	friend Vector<T, dim> operator+(const T& k, const Vector<T, dim>& my) { return my.add(k); };
	friend Vector<T, dim> operator-(const Vector<T, dim>& my, const Vector<T, dim>& vec) { return my.minus(vec); };
	friend Vector<T, dim> operator-(const Vector<T, dim>& my, const T& k) { return my.add(-k); };
	friend Vector<T, dim> operator-(const T& k, const Vector<T, dim>& my) { return my.minusf(k); };

	friend Vector<T, dim> operator*(const Vector<T, dim>& my, const T& k) { return my._multiple(k); }
	friend Vector<T, dim> operator*(const Vector<T, dim>& my, const Vector<T, dim>& vec) { return my._multiple(vec); }
	friend Vector<T, dim> operator^(const Vector<T, dim>& my, const Vector<T, dim>& vec) {return my.cross(vec); }

	template<int colDim>
	friend uMatrix<T, dim, colDim> operator*(const Vector<T, dim>& my, const tVector<T, colDim>& tvec) { return my.multiple(tvec); }
	template<int colDim>
	friend uMatrix<T, dim, colDim> operator*(const Vector<T, dim>& my, const uMatrix<T, dim, colDim>& mat) { return my._multiple(mat); }
	template<int rowDim>
	friend Vector<T, rowDim> operator*(const uMatrix<T, rowDim, dim>& mat, const Vector<T, dim>& my) { return my.multipleb(mat); }

};

template<typename T, int dim>
Vector<T, dim>::Vector(int type, int num) :_Vector<T, dim>(), _VectorAccessory<T, dim>()
{
	if (type == 0) zero();
	if (type == 1) ones(num);
	if (type == 2)
	{
		zero();
		if (num >= 0 && num < dim)
		{
			this->vectorSet[num][0] = 1;
			this->direction[num] = 1;
			this->length = 1;
		}
	}
	if (type = 3) random<T, dim, 1>(this->vectorSet, num);
}

template<typename T, int dim>
Vector<T, dim>::Vector(T& data)
{
	for (int i = 0; i < dim; i++)
		this->vectorSet[i][0] = data;
	update();
}

template<typename T, int dim>
Vector<T, dim>::Vector(T* data)
{
	int i = 0;
	bool iflag = 0, oflag = 0;		// iflag for insufficient; oflag for overflow.
	while (i < dim && data + i)
	{
		this->vectorSet[i][0] = data[i];
		++i;
	}
	if (i < dim)
	{
		iflag = 1;	// unfinished. warning needed.
		while (i < dim) this->vectorSet[i++][0] = 0;
	}
	if (data + i) oflag = 1;	//unfinished. warning needed.
	update();
}

template<typename T, int dim>
Vector<T, dim>::Vector(const Vector<T, dim>& vec)
{
	for (int i = 0; i < dim; i++)
	{
		this->vectorSet[i][0] = vec.vectorSet[i][0];
		this->direction[i] = vec.direction[i];
	}
	this->length = vec.length;
}

template<typename T, int dim>
Vector<T, dim>::Vector(const Vector<T, dim>* vec)
{
	for (int i = 0; i < dim; i++)
	{
		this->vectorSet[i][0] = vec->vectorSet[i][0];
		this->direction[i] = vec->direction[i];
	}
	this->length = vec->length;
}

template<typename T, int dim>
void Vector<T, dim>::zero()
{
	for (int i = 0; i < dim; i++)
	{
		this->vectorSet[i][0] = 0;
		this->direction[i] = 0;
	}
	this->length = 0;
}

template<typename T, int dim>
void Vector<T, dim>::ones(int num)
{
	this->length = num * sqrt(dim);
	T dirVal = 1 / this->length;
	for (int i = 0; i < dim; i++)
	{
		this->vectorSet[i][0] = num;
		this->direction[i] = dirVal;
	}
}

template<typename T, int dim>
void Vector<T, dim>::update()
{
	int i;
	this->length = 0;
	for (i = 0; i < dim; i++)
		this->length = this->length + this->vectorSet[i][0] * this->vectorSet[i][0];
	this->length = sqrt(this->length);
	
	if (this->length == 0)
		for (i = 0; i < dim; i++)
			this->direction[i] = 0;
	else
		for (i = 0; i < dim; i++)
			this->direction[i] = this->vectorSet[i][0] / this->length;
}

template<typename T, int dim>
template<int colDim>
uMatrix<T, dim, colDim + 1> Vector<T, dim>::stitch(const uMatrix<T, dim, colDim>& mat, bool style)const			// stitch mat from the right.
{
	uMatrix<T, dim, colDim + 1> result;
	int i, j;
	for (i = 0; i < dim; ++i)
	{
		if (style)
		{
			result.vectorSet[i][0] = this->vectorSet[i][0];
			for (j = 0; j < colDim; ++j)
				result.vectorSet[i][j + 1] = mat.vectorSet[i][j];
		}
		else
		{
			for (j = 0; j < colDim; ++j)
				result.vectorSet[i][j] = mat.vectorSet[i][j];
			result.vectorSet[i][colDim] = this->vectorSet[i][0];
		}
	}
	return result;
}

template<typename T, int dim>
uMatrix<T, dim, 2> Vector<T, dim>::stitch(const Vector<T, dim>& vec)const							// stitch mat from the right.
{
	uMatrix<T, dim, 2> result;
	int i;
	for (i = 0; i < dim; ++i)
	{
		result.vectorSet[i][0] = this->vectorSet[i][0];
		result.vectorSet[i][1] = vec.vectorSet[i][0];
	}
	return result;
}

template<typename T, int dim>
template<int newDim>
Vector<T, dim + newDim> Vector<T, dim>::graft(const Vector<T, newDim>& vec)const					// graft mat from buttom.
{
	Vector<T, dim + newDim> result;
	int i;
	for (i = 0; i < dim; ++i) result.vectorSet[i][0] = this->vectorSet[i][0];
	for (i = 0; i < newDim; ++i) result.vectorSet[i + dim][0] = vec.vectorSet[i][0];
	result.update();
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::add(const Vector<T, dim>& vec)const									// + vec.
{
	Vector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i) result.vectorSet[i][0] = this->vectorSet[i][0] + vec.vectorSet[i][0];
	result.update();
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::add(const T& k)const												// + k.
{
	Vector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i) result.vectorSet[i][0] = this->vectorSet[i][0] + k;
	result.update();
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::minus(const Vector<T, dim>& vec)const								// - vec.
{
	Vector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i) result.vectorSet[i][0] = this->vectorSet[i][0] - vec.vectorSet[i][0];
	result.update();
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::minusf(const T& k)const											// k - my.
{
	Vector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i) result.vectorSet[i][0] = k - this->vectorSet[i][0];
	result.update();
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::_multiple(const T& k)const											// .* k.
{
	Vector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i) result.vectorSet[i][0] = this->vectorSet[i][0] * k;
	if (k >= 0)
		result.length = result.length * k;
	else
	{
		result.length = result.length * (-k);
		for (i = 0; i < dim; ++i)
			result.direction[i] = -result.direction[i];
	}
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::_multiple(const Vector<T, dim>& vec)const							// .* vec.
{
	Vector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i) result.vectorSet[i][0] = this->vectorSet[i][0] * vec.vectorSet[i][0];
	result.update();
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::cross(const Vector<T, dim>& vec)const							// cross vec.
{
	// unfinished,
}

template<typename T, int dim>
template<int colDim>
uMatrix<T, dim, colDim> Vector<T, dim>::multiple(const tVector<T, colDim>& tvec)const				// * tvec.
{
	uMatrix<T, dim, colDim> result;
	int i, j;
	for (i = 0; i < dim; ++i)
		for(j = 0; j < colDim; ++j)
			result.vectorSet[i][j] = this->vectorSet[i][0] * tvec.vectorSet[0][j];
	return result;
}

template<typename T, int dim>
template<int colDim>
uMatrix<T, dim, colDim> Vector<T, dim>::_multiple(const uMatrix<T, dim, colDim>& mat)const			// .* mat.
{
	uMatrix<T, dim, colDim> result;
	int i, j;
	for (i = 0; i < dim; ++i)
		for (j = 0; j < colDim; ++j)
			result.vectorSet[i][j] = this->vectorSet[i][0] * mat.vectorSet[i][j];
	return result;
}

template<typename T, int dim>
template<int rowDim>
Vector<T, rowDim> Vector<T, dim>::multipleb(const uMatrix<T, rowDim, dim>& mat)const				// * mat.
{
	Vector<T, rowDim> result;
	int i, j;
	for (i = 0; i < rowDim; ++i)
	{
		for (j = 0; j < dim; ++j)
			result.vectorSet[i][0] += mat.vectorSet[i][j] * this->vectorSet[j][0];
	}
	result.update();
	return result;
}

template<typename T, int dim>
T& Vector<T, dim>::toVal()
{
	return this->vectorSet[0][0];
}

template<typename T, int dim>
T& Vector<T, dim>::getVal(int index)
{
	return this->vectorSet[index][0];
}

template<typename T, int dim>
T& Vector<T, dim>::dot(Vector<T, dim>& vec)
{
	T ans = 0;
	int i;
	for (i = 0; i < dim; ++i)
		ans = ans + this->vectorSet[i][0] * vec->vectorSet[i][0];
	return ans;
}

template<typename T, int dim>
T& Vector<T, dim>::project(Vector<T, dim>& vec)
{
	T ans = this->dot(vec);
	if (vec->length > 0) ans = ans / vec->length;
	return ans;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::projectVec(Vector<T, dim>& vec)
{
	Vector<T, dim> result(vec);
	result.normalize(this->project(vec));
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::extract(Vector<T, dim>& vec)
{
	Vector<T, dim> result(this);
	result = result - this->projectVec(vec);
	return result;
}

template<typename T, int dim>
void Vector<T, dim>::normalize(T& scale)
{
	int i;
	for (i = 0; i < dim; ++i)
		this->vectorSet[i][0] = this->direction[i] * scale;
	this->length = scale;
}

template<typename T, int dim>
tVector<T, dim> Vector<T, dim>::transpose()
{
	tVector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i)
	{
		result.vectorSet[0][i] = this->vectorSet[i][0];
		result.direction[i] = this->direction[i];
	}
	result.length = this->length;
	return result;
}

template<typename T, int dim>
void Vector<T, dim>::operator=(const Vector<T, dim> vec)
{
	int i;
	for (i = 0; i < dim; ++i)
	{
		this->vectorSet[i][0] = vec.vectorSet[i][0];
		this->direction[i] = vec.direction[i][0];
	}
	this->length = vec.length;
}

/*
template<typename T, int dim>
ofstream& operator<<(ofstream &s, Vector<T, dim>& vec)
{
	int i;
	cout << endl;
	for (i = 0; i < dim; ++i)
		s << setw(numberSpace) << vec.vectorSet[i][0] << endl;
	return s;
}
*/


///////////////////////////////////////////////////////////////////////////////////////////

template<int dim> using dtVector = tVector<double, dim>;
using dtVector2d = tVector<double, 2>;
using dtVector3d = tVector<double, 3>;

template<typename T, int dim>
class tVector :public _tVector<T, dim>, public _VectorAccessory<T, dim>
{
protected:
	template<typename T, int dim> friend class Vector;
	template<typename T, int dim> friend class tVector;
	template<typename T, int mRows, int nCols> friend class uMatrix;

	void zero();								// zero the vector.
	void ones(int = 1);
	void update();

	template<int rowDim>
	uMatrix<T, rowDim + 1, dim> graft(const uMatrix<T, rowDim, dim>&, bool = 0)const;       // graft mat from buttom.
	uMatrix<T, 2, dim> graft(const tVector<T, dim>&)const;                                  // graft tvec from buttom.
	template<int newDim>
	tVector<T, dim + newDim> stitch(const tVector<T, newDim>&)const;                        // stitch mat from right.

	tVector<T, dim> add(const tVector<T, dim>&)const;                               // + tvec.
	tVector<T, dim> add(const T&)const;                                             // + k.
	tVector<T, dim> minus(const tVector<T, dim>&)const;                             // - tvec.
	tVector<T, dim> minusf(const T&)const;                                          // k - my.
	tVector<T, dim> _multiple(const T&)const;                                       // .* k.
	tVector<T, dim> _multiple(const tVector<T, dim>&)const;                         // .* tvec.
	tVector<T, dim> cross(const tVector<T, dim>&)const;                             // cross tvec.
	T multiple(const Vector<T, dim>&)const;                                         // * vec.

	template<int rowDim>
	uMatrix<T, rowDim, dim> _multiple(const uMatrix<T, rowDim, dim>&)const;         // .* mat.
	template<int colDim>
	tVector<T, colDim> multiple(const uMatrix<T, dim, colDim>&)const;               // * mat.

public:
	tVector(int = 0, int = 0);                        // default constructor.
	tVector(T&);                                      // constructor.
	tVector(T*);                                      // constructor.
	tVector(const tVector<T, dim>&);                  // copy constructor.
	tVector(const tVector<T, dim>*);                  // copy constructor.
	~tVector() {                                      // destructor.
		// unfinished. inform needed.
		//cout << "- Destructor Vector." << endl;
	};
	T& toVal();                                       // convert to T if dimension == 1.
	int getDim() { return dim; };                     // get dimension.
	T& getVal(int);                                   // get the ith value of the vector.
	T& getLen() { return this->calLen(); };           // get length of the vector.
	T* getDir() { return this->calDir(); };           // get the direction of the vector.
	T& dot(tVector<T, dim>&);                         // * target vec.
	T& project(tVector<T, dim>&);                     // get the projection on the target vec.
	tVector<T, dim> projectVec(tVector<T, dim>&);     // get the component parallel with the target vec.
	tVector<T, dim> extract(tVector<T, dim>&);        // get the component orthogonal to the target vec.
	void normalize(T& = 1);                           // normalize the vector under specific scale.
	Vector<T, dim> transpose();                       // transpose.
	void operator=(const tVector<T, dim>);            // = overload.
	friend ofstream& operator<<<T, dim>(ofstream&, tVector<T, dim>&);     // << overload.

	template<int rowDim>
	friend uMatrix<T, rowDim + 1, dim> operator/(const tVector<T, dim>& my, const uMatrix<T, rowDim, dim>& mat) { return my.graft(mat, 0); };
	template<int rowDim>
	friend uMatrix<T, rowDim + 1, dim> operator/(const uMatrix<T, rowDim, dim>& mat, const tVector<T, dim>& my) { return my.graft(mat, 1); };
	friend uMatrix<T, 2, dim> operator/(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.graft(tvec); };
	template<int newDim>
	friend tVector<T, dim + newDim> operator|(const tVector<T, dim>& my, const tVector<T, newDim>& tvec) { return my.stitch(tvec); };

	friend tVector<T, dim> operator+(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.add(tvec); };
	friend tVector<T, dim> operator+(const tVector<T, dim >& my, const T& k) { return my.add(k); };
	friend tVector<T, dim> operator+(const T& k, const tVector<T, dim>& my) { return my.add(k); };
	friend tVector<T, dim> operator-(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.minus(tvec); };
	friend tVector<T, dim> operator-(const tVector<T, dim>& my, const T& k) { return my.add(-k); };
	friend tVector<T, dim> operator-(const T& k, const tVector<T, dim>& my) { return my.minusf(k); };

	friend tVector<T, dim> operator*(const tVector<T, dim>& my, const T& k) { return my._multiple(k); }
	friend tVector<T, dim> operator*(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my._multiple(tvec); }

	friend T operator*(const tVector<T, dim>& my, const Vector<T, dim>& vec) { return my.multiple(vec); }
	friend tVector<T, dim> operator^(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.cross(tvec); }

	template<int rowDim>
	friend uMatrix<T, rowDim, dim> operator*(const uMatrix<T, rowDim, dim>& mat, const tVector<T, dim>& my) { return my._multiple(mat); }
	template<int colDim>
	friend tVector<T, colDim> operator*(const tVector<T, dim>& my, const uMatrix<T, dim, colDim>& mat) { return my.multiple(mat); }

};

template<typename T, int dim>
tVector<T, dim>::tVector(int type, int num) : _tVector<T, dim>(), _VectorAccessory<T, dim>()
{
	if (type == 0) zero();
	if (type == 1) ones(num);
	if (type == 2)
	{
		zero();
		if (num >= 0 && num < dim)
		{
			this->vectorSet[0][num] = 1;
			this->direction[num] = 1;
			this->length = 1;
		}
	}
	if (type = 3) random<T, 1, dim>(this->vectorSet, num);
}

template<typename T, int dim>
tVector<T, dim>::tVector(T& data)
{
	for (int i = 0; i < dim; i++)
		this->vectorSet[0][i] = data;
	update();
}

template<typename T, int dim>
tVector<T, dim>::tVector(T* data)
{
	int i = 0;
	bool iflag = 0, oflag = 0;		// iflag for insufficient; oflag for overflow.
	while (i < dim && data + i)
	{
		this->vectorSet[0][i] = data[i];
		++i;
	}
	if (i < dim)
	{
		iflag = 1;	// unfinished. warning needed.
		while (i < dim) this->vectorSet[0][i++] = 0;
	}
	if (data + i) oflag = 1;	//unfinished. warning needed.
	update();
}

template<typename T, int dim>
tVector<T, dim>::tVector(const tVector<T, dim>& tvec)
{
	for (int i = 0; i < dim; i++)
	{
		this->vectorSet[0][i] = tvec.vectorSet[0][i];
		this->direction[i] = tvec.direction[i];
	}
	this->length = tvec.length;
}

template<typename T, int dim>
tVector<T, dim>::tVector(const tVector<T, dim>* tvec)
{
	for (int i = 0; i < dim; i++)
	{
		this->vectorSet[0][i] = tvec->vectorSet[0][i];
		this->direction[i] = tvec->direction[i];
	}
	this->length = tvec->length;
}

template<typename T, int dim>
void tVector<T, dim>::zero()
{
	for (int i = 0; i < dim; i++)
	{
		this->vectorSet[0][i] = 0;
		this->direction[i] = 0;
	}
	this->length = 0;
}

template<typename T, int dim>
void tVector<T, dim>::ones(int num)
{
	this->length = num * sqrt(dim);
	T dirVal = 1 / this->length;
	for (int i = 0; i < dim; i++)
	{
		this->vectorSet[0][i] = num;
		this->direction[i] = dirVal;
	}
}

template<typename T, int dim>
void tVector<T, dim>::update()
{
	int i;
	this->length = 0;
	for (i = 0; i < dim; i++)
		this->length = this->length + this->vectorSet[0][i] * this->vectorSet[0][i];
	this->length = sqrt(this->length);

	if (this->length == 0)
		for (i = 0; i < dim; i++)
			this->direction[i] = 0;
	else
		for (i = 0; i < dim; i++)
			this->direction[i] = this->vectorSet[0][i] / this->length;
}

template<typename T, int dim>
template<int rowDim>
uMatrix<T, rowDim + 1, dim> tVector<T, dim>::graft(const uMatrix<T, rowDim, dim>& mat, bool style)const			// stitch mat from the right.
{
	uMatrix<T, rowDim + 1, dim> result;
	int i, j;
	for (j = 0; j < dim; ++j)
	{
		if (style)
		{
			result.vectorSet[0][j] = this->vectorSet[0][j];
			for (i = 0; i < rowDim; ++i)
				result.vectorSet[i + 1][j] = mat.vectorSet[i][j];
		}
		else
		{
			for (i = 0; i < rowDim; ++i)
				result.vectorSet[i][j] = mat.vectorSet[i][j];
			result.vectorSet[rowDim][j] = this->vectorSet[0][j];
		}
	}
	return result;
}

template<typename T, int dim>
uMatrix<T, 2, dim> tVector<T, dim>::graft(const tVector<T, dim>& tvec)const							// stitch mat from the right.
{
	uMatrix<T, 2, dim> result;
	int j;
	for (j = 0; j < dim; ++j)
	{
		result.vectorSet[0][j] = this->vectorSet[0][j];
		result.vectorSet[1][j] = tvec.vectorSet[0][j];
	}
	return result;
}

template<typename T, int dim>
template<int newDim>
tVector<T, dim + newDim> tVector<T, dim>::stitch(const tVector<T, newDim>& tvec)const					// graft mat from buttom.
{
	tVector<T, dim + newDim> result;
	int j;
	for (j = 0; j < dim; ++j) result.vectorSet[0][j] = this->vectorSet[0][j];
	for (j = 0; j < newDim; ++j) result.vectorSet[0][j + dim] = tvec.vectorSet[0][j];
	result.update();
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::add(const tVector<T, dim>& tvec)const									// + vec.
{
	tVector<T, dim> result;
	int j;
	for (j = 0; j < dim; ++j) result.vectorSet[0][j] = this->vectorSet[0][j] + tvec.vectorSet[0][j];
	result.update();
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::add(const T& k)const												// + k.
{
	tVector<T, dim> result;
	int j;
	for (j = 0; j < dim; ++j) result.vectorSet[0][j] = this->vectorSet[0][j] + k;
	result.update();
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::minus(const tVector<T, dim>& tvec)const								// - vec.
{
	tVector<T, dim> result;
	int j;
	for (j = 0; j < dim; ++j) result.vectorSet[0][j] = this->vectorSet[0][j] - tvec.vectorSet[0][j];
	result.update();
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::minusf(const T& k)const											// k - my.
{
	tVector<T, dim> result;
	int j;
	for (j = 0; j < dim; ++j) result.vectorSet[0][j] = k - this->vectorSet[0][j];
	result.update();
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::_multiple(const T& k)const											// .* k.
{
	tVector<T, dim> result;
	int j;
	for (j = 0; j < dim; ++j) result.vectorSet[0][j] = this->vectorSet[0][j] * k;
	if (k >= 0)
		result.length = result.length * k;
	else
	{
		result.length = result.length * (-k);
		for (j = 0; j < dim; ++j)
			result.direction[j] = -result.direction[j];
	}
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::_multiple(const tVector<T, dim>& tvec)const							// .* vec.
{
	tVector<T, dim> result;
	int j;
	for (j = 0; j < dim; ++j) result.vectorSet[0][j] = this->vectorSet[0][j] * tvec.vectorSet[0][j];
	result.update();
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::cross(const tVector<T, dim>& tvec)const								// cross vec.
{
	// unfinished. 2001202109
}

template<typename T, int dim>
T tVector<T, dim>::multiple(const Vector<T, dim>& vec)const												// tvec * my.
{
	T ans = 0;
	for (int j = 0; j < dim; ++j) ans = ans + this->vectorSet[0][j] * vec.vectorSet[j][0];
	return ans;
}

template<typename T, int dim>
template<int rowDim>
uMatrix<T, rowDim, dim> tVector<T, dim>::_multiple(const uMatrix<T, rowDim, dim>& mat)const			// .* mat.
{
	uMatrix<T, rowDim, dim> result;
	int i, j;
	for (i = 0; i < rowDim; ++i)
		for (j = 0; j < dim; ++j)
			result.vectorSet[i][j] = this->vectorSet[0][j] * mat.vectorSet[i][j];
	return result;
}

template<typename T, int dim>
template<int colDim>
tVector<T, colDim> tVector<T, dim>::multiple(const uMatrix<T, dim, colDim>& mat)const				// * mat.
{
	tVector<T, colDim> result;
	int i, j;
	for (i = 0; i < colDim; ++i)
	{
		for (j = 0; j < dim; ++j)
			result.vectorSet[0][i] += this->vectorSet[0][j] * mat.vectorSet[j][i];
	}
	result.update();
	return result;
}

template<typename T, int dim>
T& tVector<T, dim>::toVal()
{
	return this->vectorSet[0][0];	// not decided. 2001272203
}

template<typename T, int dim>
T& tVector<T, dim>::getVal(int index)
{
	return this->vectorSet[0][index];
}

template<typename T, int dim>
T& tVector<T, dim>::dot(tVector<T, dim>& vec)
{
	T ans = 0;
	int i;
	for (i = 0; i < dim; ++i)
		ans = ans + this->vectorSet[0][i] * vec->vectorSet[0][i];
	return ans;
}

template<typename T, int dim>
T& tVector<T, dim>::project(tVector<T, dim>& vec)
{
	T ans = this->dot(vec);
	if (vec->length > 0) ans = ans / vec->length;
	return ans;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::projectVec(tVector<T, dim>& vec)
{
	tVector<T, dim> result(vec);
	result.normalize(this->project(vec));
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::extract(tVector<T, dim>& vec)
{
	tVector<T, dim> result(this);
	result = result - this->projectVec(vec);
	return result;
}

template<typename T, int dim>
void tVector<T, dim>::normalize(T& scale)
{
	int i;
	for (i = 0; i < dim; ++i)
		this->vectorSet[0][i] = this->direction[i] * scale;
	this->length = scale;
}

template<typename T, int dim>
Vector<T, dim> tVector<T, dim>::transpose()
{
	Vector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i)
	{
		result.vectorSet[i][0] = this->vectorSet[0][i];
		result.direction[i] = this->direction[i];
	}
	result.length = this->length;
	return result;
}

template<typename T, int dim>
void tVector<T, dim>::operator=(const tVector<T, dim> tvec)
{
	int i;
	for (i = 0; i < dim; ++i)
	{
		this->vectorSet[0][i] = tvec.vectorSet[0][i];
		this->direction[i] = tvec.direction[i];
	}
	this->length = tvec.length;
}

template<typename T, int dim>
ofstream& operator<<(ofstream& s, tVector<T, dim>& tvec)
{
	cout << "overload function of tVector" << endl;
	int i;
	cout << endl;
	for (i = 0; i < dim; ++i)
		s << setw(numberSpace) << tvec.vectorSet[0][i];
	s << endl;
	return s;
}


#endif