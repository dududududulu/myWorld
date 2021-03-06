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
	Latest Revise:          20200201

	Description:
		This file claims and defines template class Vector and tVector for any type of statistic data and any dimension.

	Structure:
		_VectorAccessory<T, dim>
		1	VectorFrame<T, dim>
		1	2	Vector<T, dim>
		1	2	tVector<T, dim>
		LnBase<dim>

	///////////////////////////////////////////////////////////////

*/

template<typename T, int dim>
class _VectorAccessory
{
protected:
	T length;
	T direction[dim];
protected:
	void revert();
public:
	_VectorAccessory() { revert(); };
	~_VectorAccessory() {};
	T getLen()const { return length; };
	T* getDir()const { return direction; };
};

template<typename T, int dim>
void _VectorAccessory<T, dim>::revert()
{
	length = -1;
	for (int i = 0; i < dim; ++i)
		direction[i] = 0;
}


template<typename T, int dim>
class VectorFrame :public _VectorAccessory<T, dim>
{
protected:
	template<typename T, int mRows, int nCols> friend class uMatrix;

	void default_init(int = 0, int = 0);
	void data_init(T&);
	void data_init(T*);
	void copy_init(const VectorFrame<T, dim>&);
	void copy_init(const VectorFrame<T, dim>*);

	void zero();                                               // zero the vector.
	void ones(int = 1);                                        // every entry is identical
	void calLen();                                             // calculate length
	void calDir();                                             // calculate direction
	void update();                                             // update both length and direction

	void vadd(const VectorFrame<T, dim>&);                     // + vec.
	void vadd(const T&);                                       // + k.
	void vminus(const VectorFrame<T, dim>&);                   // - vec.
	void vminusf(const T&);                                    // k - my.
	void v_multiple(const T&);                                 // .* k.
	void v_multiple(const VectorFrame<T, dim>&);               // .* vec.
	void v_divide(const T&);                                   // ./ k.
	void v_divideb(const T&);                                  // k ./ my.
	void vcross(const VectorFrame<T, dim>&);                   // cross vec.

public:
	VectorFrame() {};                                          // default constructor.
	~VectorFrame() {                                           // destructor.
		// unfinished. inform needed.
		//cout << "- Destructor Vector." << endl;
	};
	virtual T getElement(int)const;                            // get the ith element
	virtual void setElement(const T&, int) {};                 // set the ith element
	bool isOrigin();
	T getLen()const { return this->length; };
	T* getDir()const { return this->direction; };
	int getDim() { return dim; };                              // get dimension.
	void normalize(const T& = 1);                              // normalize the vector under specific scale.
	void setVal(const T[dim]);
	void setVal(T, T, T);
	T& getSum();
	T& dot(VectorFrame<T, dim>&)const;                         // * target vec.
	T& project(VectorFrame<T, dim>&)const;                     // get the projection on the target vec.
	bool operator>(const T&);
	void operator=(const VectorFrame<T, dim>);                 // = overload.
};


template<typename T, int dim>
void VectorFrame<T, dim>::default_init(int type, int num)
{
	if (type == 0) zero();
	if (type == 1) ones(num);
	if (type == 2)
	{
		zero();
		if (num >= 0 && num < dim)
		{
			setElement(1, num);
			this->direction[num] = 1;
			this->length = 1;
		}
	}
}

template<typename T, int dim>
void VectorFrame<T, dim>::data_init(T& data)
{
	for (int i = 0; i < dim; i++)
		setElement(data, i);
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::data_init(T* data)
{
	int i = 0;
	bool iflag = 0, oflag = 0;		// iflag for insufficient; oflag for overflow.
	while (i < dim && data + i)
	{
		setElement(data[i], i);
		++i;
	}
	if (i < dim)
	{
		iflag = 1;	// unfinished. warning needed.
		while (i < dim) setElement(0, i++);
	}
	if (data + i) oflag = 1;	//unfinished. warning needed.
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::copy_init(const VectorFrame<T, dim>& vec)
{
	for (int i = 0; i < dim; i++)
	{
		setElement(vec.getElement(i), i);
		this->direction[i] = vec.direction[i];
	}
	this->length = vec.length;
}

template<typename T, int dim>
void VectorFrame<T, dim>::copy_init(const VectorFrame<T, dim>* vec)
{
	for (int i = 0; i < dim; i++)
	{
		setElement(vec->getElement(i), i);
		this->direction[i] = vec->direction[i];
	}
	this->length = vec->length;
}

template<typename T, int dim>
void VectorFrame<T, dim>::zero()
{
	for (int i = 0; i < dim; i++)
	{
		setElement(0, i);
		this->direction[i] = 0;
	}
	this->length = 0;
}

template<typename T, int dim>
void VectorFrame<T, dim>::ones(int num)
{
	this->length = num * sqrt(dim);
	T dirVal = 1 / this->length;
	for (int i = 0; i < dim; i++)
	{
		setElement(num, i);
		this->direction[i] = dirVal;
	}
}

template<typename T, int dim>
void VectorFrame<T, dim>::calLen()
{
	int i;
	this->length = 0;
	for (i = 0; i < dim; i++)
		this->length = this->length + getElement(i) * getElement(i);
	this->length = sqrt(this->length);
}

template<typename T, int dim>
void VectorFrame<T, dim>::calDir()
{
	int i;
	if (this->length < 0) calLen();
	if (this->length == 0)
		for (i = 0; i < dim; i++)
			this->direction[i] = 0;
	else
		for (i = 0; i < dim; i++)
			this->direction[i] = getElement(i) / this->length;
}

template<typename T, int dim>
void VectorFrame<T, dim>::update()
{
	calLen();
	calDir();
}

template<typename T, int dim>
void VectorFrame<T, dim>::vadd(const VectorFrame<T, dim>& vec)									// + vec.
{
	for (int i = 0; i < dim; ++i) setElement(getElement(i) + vec.getElement(i), i);
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::vadd(const T& k)												// + k.
{
	for (int i = 0; i < dim; ++i) setElement(getElement(i) + k, i);
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::vminus(const VectorFrame<T, dim>& vec)								// - vec.
{
	for (int i = 0; i < dim; ++i) setElement(getElement(i) - vec.getElement(i), i);;
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::vminusf(const T& k)											// k - my.
{
	for (int i = 0; i < dim; ++i) setElement(k - getElement(i), i);;
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::v_multiple(const T& k)											// .* k.
{
	int i;
	for (i = 0; i < dim; ++i) setElement(k * getElement(i), i);;
	if (k >= 0)
		this->length = this->length * k;
	else
	{
		this->length = this->length * (-k);
		for (i = 0; i < dim; ++i)
			this->direction[i] = -this->direction[i];
	}
}

template<typename T, int dim>
void VectorFrame<T, dim>::v_multiple(const VectorFrame<T, dim>& vec)							// .* vec.
{
	for (int i = 0; i < dim; ++i) setElement(getElement(i) - vec.getElement(i), i);
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::v_divide(const T& k)							// .* vec.
{
	if (k == 0) return;
	v_multiple(1 / k);
}

template<typename T, int dim>
void VectorFrame<T, dim>::v_divideb(const T& k)							// .* vec.
{
	for (int i = 0; i < dim; ++i)
		if (getElement(i) != 0) setElement(k / getElement(i), i);
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::vcross(const VectorFrame<T, dim>& vec)							// cross vec.
{
	if (dim != 3) return;
	T cross[3];
	cross[0] = getElement(1) * vec.getElement(2) - getElement(2) * vec.getElement(1);
	cross[1] = getElement(2) * vec.getElement(0) - getElement(0) * vec.getElement(2);
	cross[2] = getElement(0) * vec.getElement(1) - getElement(1) * vec.getElement(0);
	for (int i = 0; i < 3; ++i) setElement(cross[i], i);
}


template<typename T, int dim>
T VectorFrame<T, dim>::getElement(int index)const
{
	return 0;
}

template<typename T, int dim>
bool VectorFrame<T, dim>::isOrigin()
{
	for (int i = 0; i < dim; ++i)
		if (!infinitesimal(getElement(i))) return 0;
	return 1;
}

template<typename T, int dim>
void VectorFrame<T, dim>::normalize(const T& scale)
{
	int i;
	for (i = 0; i < dim; ++i)
		setElement(this->direction[i] * scale, i);
	this->length = scale;
}

template<typename T, int dim>
void VectorFrame<T, dim>::setVal(const T content[dim])
{
	int i;
	for (i = 0; i < dim; ++i)
		setElement(content[i], i);
	update();
}

template<typename T, int dim>
void VectorFrame<T, dim>::setVal(T data1, T data2, T data3)
{
	setElement(data1, 0);
	setElement(data2, 1);
	setElement(data3, 2);
	update();
}

template<typename T, int dim>
T& VectorFrame<T, dim>::getSum()
{
	int i;
	T ans = 0;
	for (i = 0; i < dim; ++i)
		ans = ans + getElement(i);
	return ans;
}

template<typename T, int dim>
T& VectorFrame<T, dim>::dot(VectorFrame<T, dim>& vec)const
{
	T ans = 0;
	int i;
	for (i = 0; i < dim; ++i)
		ans = ans + getElement(i) * getElement(i);
	return ans;
}

template<typename T, int dim>
T& VectorFrame<T, dim>::project(VectorFrame<T, dim>& vec)const
{
	T ans = this->dot(vec);
	if (!infinitesimal(vec.length)) ans = ans / vec.length;
	return ans;
}

template<typename T, int dim>
void VectorFrame<T, dim>::operator=(const VectorFrame<T, dim> vec)
{
	int i;
	for (i = 0; i < dim; ++i)
	{
		setElement(vec.getElement(i), i);
		this->direction[i] = vec.direction[i];
	}
	this->length = vec.length;
}

template<typename T, int dim>
bool VectorFrame<T, dim>::operator>(const T& data)
{
	int i;
	for (i = 0; i < dim; ++i)
		if (getElement(i) <= data) return 0;
	return 1;
}


template<typename T, int dim>
class Vector;
template<typename T, int dim>
class tVector;

template<int dim> using dVector = Vector<double, dim>;
template<typename T> using Vector2d = Vector<T, 2>;
template<typename T> using Vector3d = Vector<T, 3>;
using dVector2d = Vector<double, 2>;
using dVector3d = Vector<double, 3>;
using dVectordim = Vector<double, Dimension>;

template<int dim> using dtVector = tVector<double, dim>;
template<typename T> using tVector2d = tVector<T, 2>;
template<typename T> using tVector3d = tVector<T, 3>;
using dtVector2d = tVector<double, 2>;
using dtVector3d = tVector<double, 3>;
using dtVectordim = tVector<double, Dimension>;

template<typename T, int dim>
class Vector :public _Vector<T, dim>, public VectorFrame<T, dim>
{
protected:
	template<typename T, int dim> friend class Vector;
	template<typename T, int dim> friend class tVector;
	template<typename T, int mRows, int nCols> friend class uMatrix;

	template<int colDim>
	uMatrix<T, dim, colDim + 1> stitch(const uMatrix<T, dim, colDim>&, bool = 0)const;    // stitch with mat from the right.
	uMatrix<T, dim, 2> stitch(const Vector<T, dim>&)const;                                // stitch with vec from the right.
	template<int newDim>
	Vector<T, dim + newDim> graft(const Vector<T, newDim>&)const;                         // graft mat from buttom.

	Vector<T, dim> arithmetic(const Vector<T, dim>&, int)const;                                 // + vec.
	Vector<T, dim> arithmetic(const T&, int)const;                                  // + vec.

	template<int colDim>
	uMatrix<T, dim, colDim> _add(const uMatrix<T, dim, colDim>&)const;
	template<int colDim>
	uMatrix<T, dim, colDim> _minus(const uMatrix<T, dim, colDim>&)const;
	template<int colDim>
	uMatrix<T, dim, colDim> _minusf(const uMatrix<T, dim, colDim>&)const;
	template<int colDim>
	uMatrix<T, dim, colDim> multiple(const tVector<T, colDim>&)const;               // * tvec.
	template<int colDim>
	uMatrix<T, dim, colDim> _multiple(const uMatrix<T, dim, colDim>&)const;         // .* mat.
	template<int rowDim>
	Vector<T, rowDim> multipleb(const uMatrix<T, rowDim, dim>&)const;               // mat * vec.
	template<int colDim>
	uMatrix<T, dim, colDim> cross(const uMatrix<T, dim, colDim>& vec)const;             // cross vec.

public:
	Vector(int type = 0, int num = 0);                                              // default constructor.
	Vector(T&);		                                 // constructor.
	Vector(T*);                                      // constructor.
	Vector(T, T);                                    // constructor.
	Vector(T, T, T);                                 // constructor.
	Vector(const Vector<T, dim>&);                   // copy constructor.
	Vector(const Vector<T, dim>*);                   // copy constructor.
	~Vector() {                                      // destructor.
		// unfinished. inform needed.
		//cout << "- Destructor Vector." << endl;
	};
	T getElement(int)const;
	void setElement(const T&, int);
	tVector<T, dim> transpose()const;                // transpose.
	Vector<T, dim> projectVec(Vector<T, dim>&)const; // get the component in line with the target vec.
	Vector<T, dim> extract(Vector<T, dim>&)const;    // get the component perpendicular with the target vec.
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

	friend Vector<T, dim> operator+(const Vector<T, dim>& my, const Vector<T, dim>& vec) { return my.arithmetic(vec, 0); };
	friend Vector<T, dim> operator+(const Vector<T, dim >& my, const T& k) { return my.arithmetic(k, 0); };
	friend Vector<T, dim> operator+(const T& k, const Vector<T, dim>& my) { return my.arithmetic(k, 0); };
	friend Vector<T, dim> operator-(const Vector<T, dim>& my, const Vector<T, dim>& vec) { return my.arithmetic(vec, 1); };
	friend Vector<T, dim> operator-(const Vector<T, dim>& my, const T& k) { return my.arithmetic(-k, 0); };
	friend Vector<T, dim> operator-(const T& k, const Vector<T, dim>& my) { return my.arithmetic(k, 1); };

	friend Vector<T, dim> operator*(const T& k, const Vector<T, dim>& my) { return my.arithmetic(k, 2); }
	friend Vector<T, dim> operator*(const Vector<T, dim>& my, const T& k) { return my.arithmetic(k, 2); }
	friend Vector<T, dim> operator*(const Vector<T, dim>& my, const Vector<T, dim>& vec) { return my.arithmetic(vec, 2); }
	friend Vector<T, dim> operator^(const Vector<T, dim>& my, const Vector<T, dim>& vec) { return my.arithmetic(vec, 3); }
	friend Vector<T, dim> operator/(const Vector<T, dim>& my, const T& k) { return my.arithmetic(k, 3); }
	friend Vector<T, dim> operator/(const T& k, const Vector<T, dim>& my) { return my.arithmetic(k, 4); }

	template<int colDim>
	friend uMatrix<T, dim, colDim> operator+(const Vector<T, dim>& my, const uMatrix<T, dim, colDim>& mat) { return my._add(mat); }
	template<int colDim>
	friend uMatrix<T, dim, colDim> operator+(const uMatrix<T, dim, colDim>& mat, const Vector<T, dim>& my) { return my._add(mat); }
	template<int colDim>
	friend uMatrix<T, dim, colDim> operator-(const Vector<T, dim>& my, const uMatrix<T, dim, colDim>& mat) { return my._minus(mat); }
	template<int colDim>
	friend uMatrix<T, dim, colDim> operator-(const uMatrix<T, dim, colDim>& mat, const Vector<T, dim>& my) { return my._minusf(mat); }
	template<int colDim>
	friend uMatrix<T, dim, colDim> operator*(const Vector<T, dim>& my, const tVector<T, colDim>& tvec) { return my.multiple(tvec); }
	template<int colDim>
	friend uMatrix<T, dim, colDim> operator*(const Vector<T, dim>& my, const uMatrix<T, dim, colDim>& mat) { return my._multiple(mat); }
	template<int rowDim>
	friend Vector<T, rowDim> operator*(const uMatrix<T, rowDim, dim>& mat, const Vector<T, dim>& my) { return my.multipleb(mat); }
	template<int colDim>
	friend uMatrix<T, dim, colDim> operator^(const Vector<T, dim>& my, const uMatrix<T, dim, colDim>& mat) { return my.cross(mat); }
	template<int colDim>
	friend uMatrix<T, dim, colDim> operator^(const uMatrix<T, dim, colDim>& mat, const Vector<T, dim>& my) { return my.cross(mat); }
};

template<typename T, int dim>
Vector<T, dim>::Vector(int type, int num)
{
	this->default_init(type, num);
	if (type == 3) random<T, dim, 1>(this->vectorSet, num);
	this->update();
};

template<typename T, int dim>
Vector<T, dim>::Vector(T& data)
{
	this->data_init(data);
};

template<typename T, int dim>
Vector<T, dim>::Vector(T data1, T data2)
{
	this->zero();
	setElement(data1, 0);
	setElement(data2, 1);
};

template<typename T, int dim>
Vector<T, dim>::Vector(T data1, T data2, T data3)
{
	this->zero();
	setElement(data1, 0);
	setElement(data2, 1);
	setElement(data3, 2);
};

template<typename T, int dim>
Vector<T, dim>::Vector(T* data)
{
	this->data_init(data);
};

template<typename T, int dim>
Vector<T, dim>::Vector(const Vector<T, dim>& vec)
{
	this->copy_init(vec);
};

template<typename T, int dim>
Vector<T, dim>::Vector(const Vector<T, dim>* vec)
{
	this->copy_init(vec);
};

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
			result.vectorSet[i][0] = getElement(i);
			for (j = 0; j < colDim; ++j)
				result.vectorSet[i][j + 1] = mat.vectorSet[i][j];
		}
		else
		{
			for (j = 0; j < colDim; ++j)
				result.vectorSet[i][j] = mat.vectorSet[i][j];
			result.vectorSet[i][colDim] = getElement(i);
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
		result.vectorSet[i][0] = getElement(i);
		result.vectorSet[i][1] = vec.getElement(i);
	}
	return result;
}

template<typename T, int dim>
template<int newDim>
Vector<T, dim + newDim> Vector<T, dim>::graft(const Vector<T, newDim>& vec)const					// graft mat from buttom.
{
	Vector<T, dim + newDim> result;
	int i;
	for (i = 0; i < dim; ++i) result.setElement(getElement(i), i);
	for (i = 0; i < newDim; ++i) result.setElement(vec.getElement(i), i + dim);
	result.update();
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::arithmetic(const Vector<T, dim>& vec, int type)const
{
	Vector<T, dim> result(this);
	switch (type)
	{
	case 0: result.vadd(vec); break;
	case 1: result.vminus(vec); break;
	case 2: result.v_multiple(vec); break;
	case 3: result.vcross(vec); break;
	default: cout << "Error Occurs: Arithmetic" << endl;
	}
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::arithmetic(const T& k, int type)const
{
	Vector<T, dim> result(this);
	switch (type)
	{
	case 0: result.vadd(k); break;
	case 1: result.vminusf(k); break;
	case 2: result.v_multiple(k); break;
	case 3: result.v_divide(k); break;
	case 4: result.v_divideb(k); break;
	default: cout << "Error Occurs: Arithmetic" << endl;
	}
	return result;
}

template<typename T, int dim>
template<int colDim>
uMatrix<T, dim, colDim> Vector<T, dim>::_add(const uMatrix<T, dim, colDim>& mat)const
{
	uMatrix<T, dim, colDim> result(mat);
	int i, j;
	for (i = 0; i < dim; ++i)
		for (j = 0; j < colDim; ++j)
			result.vectorSet[i][j] = result.vectorSet[i][j] + getElement(i);
	return result;
}

template<typename T, int dim>
template<int colDim>
uMatrix<T, dim, colDim> Vector<T, dim>::_minus(const uMatrix<T, dim, colDim>& mat)const
{
	uMatrix<T, dim, colDim> result(mat);
	int i, j;
	for (i = 0; i < dim; ++i)
		for (j = 0; j < colDim; ++j)
			result.vectorSet[i][j] = getElement(i) - result.vectorSet[i][j];
	return result;
}

template<typename T, int dim>
template<int colDim>
uMatrix<T, dim, colDim> Vector<T, dim>::_minusf(const uMatrix<T, dim, colDim>& mat)const
{
	uMatrix<T, dim, colDim> result(mat);
	int i, j;
	for (i = 0; i < dim; ++i)
		for (j = 0; j < colDim; ++j)
			result.vectorSet[i][j] = result.vectorSet[i][j] - getElement(i);
	return result;
}

template<typename T, int dim>
template<int colDim>
uMatrix<T, dim, colDim> Vector<T, dim>::multiple(const tVector<T, colDim>& tvec)const				// * tvec.
{
	uMatrix<T, dim, colDim> result;
	int i, j;
	for (i = 0; i < dim; ++i)
		for (j = 0; j < colDim; ++j)
			result.vectorSet[i][j] = getElement(i) * tvec.getElement(j);
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
			result.vectorSet[i][j] = getElement(i) * mat.vectorSet[i][j];
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
			result.vectorSet[i][0] += mat.vectorSet[i][j] * getElement(j);
	}
	result.update();
	return result;
}

template<typename T, int dim>
template<int colDim>
uMatrix<T, dim, colDim> Vector<T, dim>::cross(const uMatrix<T, dim, colDim>& mat)const			// .* mat.
{
	if (dim != 3) return mat;
	int j;
	uMatrix<T, dim, colDim> result;
	for (j = 0; j < colDim; ++j)
	{
		result.vectorSet[0][j] = this->vectorSet[1][0] * mat.vectorSet[2][j] - this->vectorSet[2][0] * mat.vectorSet[1][j];
		result.vectorSet[1][j] = this->vectorSet[2][0] * mat.vectorSet[0][j] - this->vectorSet[0][0] * mat.vectorSet[2][j];
		result.vectorSet[2][j] = this->vectorSet[0][0] * mat.vectorSet[1][j] - this->vectorSet[1][0] * mat.vectorSet[0][j];
	}
	return result;
}

template<typename T, int dim>
T Vector<T, dim>::getElement(int index)const
{
	return this->vectorSet[index][0];
}

template<typename T, int dim>
void Vector<T, dim>::setElement(const T& data, int index)
{
	this->vectorSet[index][0] = data;
	this->update();
}

template<typename T, int dim>
tVector<T, dim> Vector<T, dim>::transpose()const
{
	tVector<T, dim> result;
	int i;
	for (i = 0; i < dim; ++i)
	{
		result.setElement(getElement(i), i);
		result.direction[i] = this->direction[i];
	}
	result.length = this->length;
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::projectVec(Vector<T, dim>& vec)const
{
	Vector<T, dim> result(vec);
	result.normalize(this->project(vec));
	return result;
}

template<typename T, int dim>
Vector<T, dim> Vector<T, dim>::extract(Vector<T, dim>& vec)const
{
	Vector<T, dim> result(this);
	result = result - this->projectVec(vec);
	return result;
}

template<typename T, int dim>
void Vector<T, dim>::operator=(const Vector<T, dim> vec)
{
	int i;
	for (i = 0; i < dim; ++i)
	{
		setElement(vec.getElement(i), i);
		this->direction[i] = vec.direction[i];
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

template<typename T, int dim>
class tVector :public _tVector<T, dim>, public VectorFrame<T, dim>
{
protected:
	template<typename T, int dim> friend class Vector;
	template<typename T, int dim> friend class tVector;
	template<typename T, int mRows, int nCols> friend class uMatrix;

	template<int rowDim>
	uMatrix<T, rowDim + 1, dim> graft(const uMatrix<T, rowDim, dim>&, bool = 0)const;       // graft mat from buttom.
	uMatrix<T, 2, dim> graft(const tVector<T, dim>&)const;                                  // graft tvec from buttom.
	template<int newDim>
	tVector<T, dim + newDim> stitch(const tVector<T, newDim>&)const;                        // stitch mat from right.

	tVector<T, dim> arithmetic(const tVector<T, dim>&, int)const;
	tVector<T, dim> arithmetic(const T&, int)const;
	T multiple(const Vector<T, dim>&)const;

	template<int rowDim>
	uMatrix<T, rowDim, dim> _add(const uMatrix<T, rowDim, dim>&)const;
	template<int rowDim>
	uMatrix<T, rowDim, dim> _minus(const uMatrix<T, rowDim, dim>&)const;
	template<int rowDim>
	uMatrix<T, rowDim, dim> _minusf(const uMatrix<T, rowDim, dim>&)const;
	template<int rowDim>
	uMatrix<T, rowDim, dim> _multiple(const uMatrix<T, rowDim, dim>&)const;         // .* mat.
	template<int colDim>
	tVector<T, colDim> multiple(const uMatrix<T, dim, colDim>&)const;               // * mat.
	template<int rowDim>
	uMatrix<T, rowDim, dim> cross(const uMatrix<T, rowDim, dim>&)const;

public:
	tVector(int = 0, int = 0);                        // default constructor.
	tVector(T&);                                      // constructor.
	tVector(T*);                                      // constructor.
	tVector(T, T);                                    // constructor.
	tVector(T, T, T);                                 // constructor.
	tVector(const tVector<T, dim>&);                  // copy constructor.
	tVector(const tVector<T, dim>*);                  // copy constructor.
	~tVector() {                                      // destructor.
		// unfinished. inform needed.
		//cout << "- Destructor Vector." << endl;
	};
	T getElement(int)const;
	void setElement(const T&, int);
	Vector<T, dim> transpose();                        // transpose.
	tVector<T, dim> projectVec(tVector<T, dim>&)const; // get the component in line with the target vec.
	tVector<T, dim> extract(tVector<T, dim>&)const;    // get the component perpendicular with the target vec.
	void operator=(const tVector<T, dim>);             // = overload.
	friend ofstream& operator<<<T, dim>(ofstream&, tVector<T, dim>&);     // << overload.

	template<int rowDim>
	friend uMatrix<T, rowDim + 1, dim> operator/(const tVector<T, dim>& my, const uMatrix<T, rowDim, dim>& mat) { return my.graft(mat, 0); };
	template<int rowDim>
	friend uMatrix<T, rowDim + 1, dim> operator/(const uMatrix<T, rowDim, dim>& mat, const tVector<T, dim>& my) { return my.graft(mat, 1); };
	friend uMatrix<T, 2, dim> operator/(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.graft(tvec); };
	template<int newDim>
	friend tVector<T, dim + newDim> operator|(const tVector<T, dim>& my, const tVector<T, newDim>& tvec) { return my.stitch(tvec); };

	friend tVector<T, dim> operator+(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.arithmetic(tvec, 0); };
	friend tVector<T, dim> operator+(const tVector<T, dim >& my, const T& k) { return my.arithmetic(k, 0); };
	friend tVector<T, dim> operator+(const T& k, const tVector<T, dim>& my) { return my.adarithmeticd(k, 0); };
	friend tVector<T, dim> operator-(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.arithmetic(tvec, 1); };
	friend tVector<T, dim> operator-(const tVector<T, dim>& my, const T& k) { return my.arithmetic(-k, 0); };
	friend tVector<T, dim> operator-(const T& k, const tVector<T, dim>& my) { return my.arithmetic(k, 1); };

	friend tVector<T, dim> operator*(const T& k, const tVector<T, dim>& my) { return my.arithmetic(k, 2); }
	friend tVector<T, dim> operator*(const tVector<T, dim>& my, const T& k) { return my.arithmetic(k, 2); }
	friend tVector<T, dim> operator*(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.arithmetic(tvec, 2); }
	friend tVector<T, dim> operator^(const tVector<T, dim>& my, const tVector<T, dim>& tvec) { return my.arithmetic(tvec, 3); }
	friend tVector<T, dim> operator/(const tVector<T, dim>& my, const T& k) { return my.arithmetic(k, 3); }
	friend tVector<T, dim> operator/(const T& k, const tVector<T, dim>& my) { return my.arithmetic(k, 4); }
	friend T operator*(const tVector<T, dim>& my, const Vector<T, dim>& vec) { return my.multiple(vec); }

	template<int rowDim>
	friend uMatrix<T, rowDim, dim> operator+(const Vector<T, dim>& my, const uMatrix<T, rowDim, dim>& mat) { return my._add(mat); }
	template<int rowDim>
	friend uMatrix<T, rowDim, dim> operator+(const uMatrix<T, rowDim, dim>& mat, const Vector<T, dim>& my) { return my._add(mat); }
	template<int rowDim>
	friend uMatrix<T, rowDim, dim> operator-(const Vector<T, dim>& my, const uMatrix<T, rowDim, dim>& mat) { return my._minus(mat); }
	template<int rowDim>
	friend uMatrix<T, rowDim, dim> operator-(const uMatrix<T, rowDim, dim>& mat, const Vector<T, dim>& my) { return my._minusf(mat); }
	template<int rowDim>
	friend uMatrix<T, rowDim, dim> operator*(const uMatrix<T, rowDim, dim>& mat, const tVector<T, dim>& my) { return my._multiple(mat); }
	template<int colDim>
	friend tVector<T, colDim> operator*(const tVector<T, dim>& my, const uMatrix<T, dim, colDim>& mat) { return my.multiple(mat); }
	template<int rowDim>
	friend uMatrix<T, rowDim, dim> operator^(const tVector<T, dim>& my, const uMatrix<T, rowDim, dim>& mat) { return my.cross(mat); }
	template<int rowDim>
	friend uMatrix<T, rowDim, dim> operator^(const uMatrix<T, rowDim, dim>& mat, const tVector<T, dim>& my) { return my.cross(mat); }
};

template<typename T, int dim>
tVector<T, dim>::tVector(int type, int num)
{
	this->default_init(type, num);
	if (type == 3) random<T, 1, dim>(this->vectorSet, num);
	this->update();
};

template<typename T, int dim>
tVector<T, dim>::tVector(T& data)
{
	this->data_init(data);
};

template<typename T, int dim>
tVector<T, dim>::tVector(T* data)
{
	this->data_init(data);
};

template<typename T, int dim>
tVector<T, dim>::tVector(T data1, T data2)
{
	this->zero();
	setElement(data1, 0);
	setElement(data2, 1);
};

template<typename T, int dim>
tVector<T, dim>::tVector(T data1, T data2, T data3)
{
	this->zero();
	setElement(data1, 0);
	setElement(data2, 1);
	setElement(data3, 2);
};

template<typename T, int dim>
tVector<T, dim>::tVector(const tVector<T, dim>& vec)
{
	this->copy_init(vec);
};

template<typename T, int dim>
tVector<T, dim>::tVector(const tVector<T, dim>* vec)
{
	this->copy_init(vec);
};

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
tVector<T, dim> tVector<T, dim>::arithmetic(const tVector<T, dim>& vec, int type)const
{
	tVector<T, dim> result(this);
	switch (type)
	{
	case 0: result.add(vec); break;
	case 1: result.minus(vec); break;
	case 2: result._multiple(vec); break;
	case 3: result.cross(vec); break;
	default: cout << "Error Occurs: Arithmetic" << endl;
	}
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::arithmetic(const T& k, int type)const
{
	tVector<T, dim> result(this);
	switch (type)
	{
	case 0: result.add(k); break;
	case 1: result.minusf(k); break;
	case 2: result._multiple(k); break;
	case 3: result.v_divide(k); break;
	case 4: result.v_divideb(k); break;
	default: cout << "Error Occurs: Arithmetic" << endl;
	}
	return result;
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
uMatrix<T, rowDim, dim> tVector<T, dim>::_add(const uMatrix<T, rowDim, dim>& mat)const
{
	uMatrix<T, rowDim, dim> result(mat);
	int i, j;
	for (j = 0; j < dim; ++j)
		for (i = 0; i < rowDim; ++i)
			result.vectorSet[i][j] = result.vectorSet[i][j] + getElement(j);
	return result;
}

template<typename T, int dim>
template<int rowDim>
uMatrix<T, rowDim, dim> tVector<T, dim>::_minus(const uMatrix<T, rowDim, dim>& mat)const
{
	uMatrix<T, rowDim, dim> result(mat);
	int i, j;
	for (j = 0; j < dim; ++j)
		for (i = 0; i < rowDim; ++i)
			result.vectorSet[i][j] = getElement(j) - result.vectorSet[i][j];
	return result;
}

template<typename T, int dim>
template<int rowDim>
uMatrix<T, rowDim, dim> tVector<T, dim>::_minusf(const uMatrix<T, rowDim, dim>& mat)const
{
	uMatrix<T, rowDim, dim> result(mat);
	int i, j;
	for (j = 0; j < dim; ++j)
		for (i = 0; i < rowDim; ++i)
			result.vectorSet[i][j] = result.vectorSet[i][j] - getElement(j);
	return result;
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
template<int rowDim>
uMatrix<T, rowDim, dim> tVector<T, dim>::cross(const uMatrix<T, rowDim, dim>& mat)const			// .* mat.
{	// error message needed. unfinished. 2002011756
	if (dim != 3) return mat;
	int i;
	uMatrix<T, rowDim, dim> result;
	for (i = 0; i < rowDim; ++i)
	{
		result.vectorSet[i][0] = this->vectorSet[0][1] * mat.vectorSet[i][2] - this->vectorSet[0][2] * mat.vectorSet[i][1];
		result.vectorSet[i][1] = this->vectorSet[0][2] * mat.vectorSet[i][0] - this->vectorSet[0][0] * mat.vectorSet[i][2];
		result.vectorSet[i][2] = this->vectorSet[0][0] * mat.vectorSet[i][1] - this->vectorSet[0][1] * mat.vectorSet[i][0];
	}
	return result;
}

template<typename T, int dim>
T tVector<T, dim>::getElement(int index)const
{
	return this->vectorSet[0][index];
}

template<typename T, int dim>
void tVector<T, dim>::setElement(const T& data, int index)
{
	this->vectorSet[0][index] = data;
	this->update();
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
tVector<T, dim> tVector<T, dim>::projectVec(tVector<T, dim>& vec)const
{
	tVector<T, dim> result(vec);
	result.normalize(this->project(vec));
	return result;
}

template<typename T, int dim>
tVector<T, dim> tVector<T, dim>::extract(tVector<T, dim>& vec)const
{
	tVector<T, dim> result(this);
	result = result - this->projectVec(vec);
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////    class LnBse

template<int dim>
class LnBase
{
	bool is_identity;
	dMatrix<dim, dim> baseMatrix;
protected:
	bool checkBase();
	void checkIdentity();
	void SchmitOrth();
	void update();
public:
	LnBase(int = 0);
	LnBase(const dMatrix<dim, dim>&);
	LnBase(const LnBase<dim>&);
	~LnBase() {};
	bool isIdentity();
	void setMatrix(const double [][dim]);
	void setMatrix(const dMatrix<dim, dim>&);
	dVector<dim> revert(const dVector<dim>&);
	dVector<dim> project(const dVector<dim>&);
	
	template<int num>
	dMatrix<dim, num> revert(const dMatrix<dim, num>&);
	template<int num>
	dMatrix<dim, num> project(const dMatrix<dim, num>&);
	
	void rotate(const dVector<dim>&);
	void rotate(const dMatrix<dim, dim>&);
	void printBase();
	void operator=(const LnBase<dim>&);
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
	update();
}

template<int dim>
LnBase<dim>::LnBase(const dMatrix<dim, dim>& mat)
{
	setMatrix(mat);
}

template<int dim>
LnBase<dim>::LnBase(const LnBase<dim>& base)
{
	setMatrix(base.baseMatrix);
}

template<int dim>
bool LnBase<dim>::checkBase()
{
	dMatrix<dim, dim> checkMatrix = baseMatrix.transpose() * baseMatrix;
	return checkMatrix.isIdentity();
}

template<int dim>
void LnBase<dim>::checkIdentity()
{
	is_identity = baseMatrix.isIdentity();
}

template<int dim>
void LnBase<dim>::SchmitOrth()
{
	if (checkBase()) return;
	baseMatrix.SchmitOrth();
}

template<int dim>
void LnBase<dim>::update()
{
	SchmitOrth();
	checkIdentity();
}

template<int dim>
bool LnBase<dim>::isIdentity()
{
	return is_identity;
}

template<int dim>
void LnBase<dim>::setMatrix(const double content[][dim])
{
	baseMatrix.setContent(content);
	update();
}

template<int dim>
void LnBase<dim>::setMatrix(const dMatrix<dim, dim>& mat)
{
	baseMatrix = mat;
	update();
}

template<int dim>
dVector<dim> LnBase<dim>::revert(const dVector<dim>& rvec)
{
	if (is_identity) return rvec;
	return baseMatrix * rvec;
}

template<int dim>
dVector<dim> LnBase<dim>::project(const dVector<dim>& vec)
{
	if (is_identity) return vec;
	return baseMatrix.transpose() * vec;
}

template<int dim>
template<int num>
dMatrix<dim, num> LnBase<dim>::revert(const dMatrix<dim, num>& rmat)
{
	if (is_identity) return rmat;
	return baseMatrix * rmat;
}

template<int dim>
template<int num>
dMatrix<dim, num> LnBase<dim>::project(const dMatrix<dim, num>& amat)
{
	if (is_identity) return amat;
	return baseMatrix.transpose() * amat;
}

template<int dim>
void LnBase<dim>::rotate(const dVector<dim>& torque)
{
	uMatrix<double, dim, dim> R = rotator<double, dim>(torque);
	baseMatrix = R * baseMatrix;
	update();
}

template<int dim>
void LnBase<dim>::rotate(const dMatrix<dim, dim>& rotMatrix)
{
	baseMatrix = rotMatrix * baseMatrix;
	update();
}

template<int dim>
void LnBase<dim>::printBase()
{
	cout << baseMatrix << endl;
}

template<int dim>
void LnBase<dim>::operator=(const LnBase<dim>& base)
{
	baseMatrix = base.baseMatrix;
	is_identity = base.is_identity;
}


#endif