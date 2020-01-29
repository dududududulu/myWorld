
#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;

/*

	///////////////////////////////////////////////////////////////

	File Name:              Matrix.h
	Date of Creation:       20200103
	Latest Revise:          20200109

	Description:
		This file claims and defines template class Matrix and Vector for any type of statistic data and any dimension.

	Classes:
		_Matrix<mRows, nCols>
		uMatrix<T, mRows, nCols> : _Matrix<mRows, nCols>
		_Vector<T, dim>			= uMatrix<T, dim, 1>
		_tVector<T, dim>		= uMatrix<T, 1, dim>
		sMatrix<T, dim>	: uMatrix<T, dim, dim>
		diagMatrix<T, dim> : uMatrix<T, dim, 1>


	///////////////////////////////////////////////////////////////

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define transversal				0
#define vertical				1
#define bothsides				2

///////////////////////////////////////////////////////////////////////////////////////////////////////		//	_Matrix class.

template<typename U, U num1, U num2>
class _bGroup					// _bGroup class.
{
public:
	_bGroup() {};
	~_bGroup() {};
};

template<int mRows, int nCols>
class _Matrix : public _bGroup<int, mRows, nCols>
{
public:
	_Matrix() {};
	~_Matrix() {};
	int getRows() { return mRows; };
	int getCols() { return nCols; };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Initialization Functions.		/////////////
template<typename T, int mRows, int nCols>
void all(T vectorSet[mRows][nCols], T num)
{
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			vectorSet[i][j] = num;
}

template<typename T, int mRows, int nCols>
void diag(T vectorSet[mRows][nCols], T num)
{
	int i = 0;
	all<T, mRows, nCols>(vectorSet, 0);
	while (i < mRows && i < nCols)
	{
		vectorSet[i][i] = num;
		++i;
	}
}

template<typename T, int mRows, int nCols>
void upper(T vectorSet[mRows][nCols], T num)
{
	int i = 0, j;
	all<T, mRows, nCols>(vectorSet, 0);
	while (i < mRows && i < nCols)
	{
		for (j = i; j < nCols; ++j)
			vectorSet[i][j] = num;
		++i;
	}
}

template<typename T, int mRows, int nCols>
void increment(T vectorSet[mRows][nCols])
{
	int i, j;
	for (j = 0; j < nCols; ++j)
		for (i = 0; i < mRows; ++i)
			vectorSet[i][j] = i + mRows * j;
}

template<typename T, int mRows, int nCols>
void random(T vectorSet[mRows][nCols], T num)
{
	// unfinished. 2001090139
	int i, j;
	for (j = 0; j < nCols; ++j)
		for (i = 0; i < mRows; ++i)
			vectorSet[i][j] = rand() % 1000;
}

int minDim(int mRows, int nCols)
{
	if (mRows > nCols) return nCols;
	return mRows;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Expection Reporting.		/////////////////

// unfinished. 2001051909


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, int mRows, int nCols>
class uMatrix;

template<int mRows, int nCols>	using dMatrix = uMatrix<double, mRows, nCols>;
template<typename T, int dim>	using _Vector = uMatrix<T, dim, 1>;
template<typename T, int dim>	using _tVector = uMatrix<T, 1, dim>;

template<typename T, int mRow, int nCols>	class eMatrix;
template<typename T, int dim>	class eVector;
template<typename T, int dim>	class etVector;
template<typename T, int dim>	class sMatrix;
template<typename T, int dim>	class diagMatrix;
template<typename VT, int dim>	class rMatrix;

#define identity(dim)		uMatrix<double, dim, dim>(1, 1)
//#define uppertriangal(dim)		
const int all_init = 0;
const int diag_init = 1;
const int upper_init = 2;
const int increment_init = 3;
const int rand_init = 4;

const int only_rank = 0;
const int with_trans = 1;

///////////////////////////////////////////////////////////////////////////////////////////////////////		//	uMatrix class.
template<typename T, int mRows, int nCols>
class uMatrix :public _Matrix<mRows, nCols>
{
protected:
	T vectorSet[mRows][nCols];
	int rank = -1;				// ~rank: change the rank of the matrix if used.
	T det_sM = 1;				// det of the matrix when it is a square matrix.
protected:
	template<typename T, int mRows, int nCols> friend class uMatrix;
	template<typename T, int mRows, int nCols> friend class eMatrix;
	template<typename T, int dim> friend class Vector;
	template<typename T, int dim> friend class tVector;

	T& meanElements(int = 0);                               // give the mean of elements to some power.
	void mergeZero();                                       // used only in GaussianElimination. no change to rank.
	void equalize();                                        // equalize the elements.
	void calRank();                                         // calculate the rank of the matrix. no change to matrix.
	void setElement(T&, int, int);                          // never used.								~rank
	void setRow(_tVector<T, nCols>, int = 0);               //											~rank
	void setColumn(_Vector<T, mRows>, int = 0);             //											~rank
	void normRow(int);                                      // Normalize the row to the first element.
	void normCol(int);                                      // Normalize the column to the first element.

	void magnifyRow(int, T);                                // Elementary Transformation: Magnify specific row.
	void magnifyCol(int, T);                                // Elementary Transformation: Magnify specific column.
	void switchRows(int, int);                              // Elementary Transformation: Switch specific rows.
	void switchCols(int, int);                              // Elementary Transformation: Switch specific columns.
	void superposRow(int, int, T);                          // Elementary Transformation: Superpose one row to another.
	void superposCol(int, int, T);                          // Elementary Transformation: Superpose one column to another.

	uMatrix<T, mRows, mRows> rowElimination(int);           // Gaussian Elimination in rows. update the rank. return the left operation matrix.
	uMatrix<T, nCols, nCols> colElimination(int);           // Gaussian Elimination in columns. update the rank. return the right operation matrix,
	template<int pCols>
	uMatrix<T, mRows, nCols + pCols> stitch(const uMatrix<T, mRows, pCols>&)const;          // stitch mat from the right.
	template<int kRows>
	uMatrix<T, mRows + kRows, nCols> graft(const uMatrix<T, kRows, nCols>&)const;           // graft mat from buttom.

	uMatrix<T, mRows, nCols> add(const uMatrix<T, mRows, nCols>&)const;                     // + mat.
	uMatrix<T, mRows, nCols> add(const T&)const;                                            // + k.
	uMatrix<T, mRows, nCols> minus(const uMatrix<T, mRows, nCols>&)const;                   // - mat.
	uMatrix<T, mRows, nCols> minusf(const T&)const;                                         // k - my.
	uMatrix<T, mRows, nCols> _multiple(const T&)const;                                      // .* k.
	_Vector<T, mRows> multiple(const _Vector<T, nCols>&)const;                              // * vec.
	uMatrix<T, mRows, nCols> _multiple(const uMatrix<T, mRows, nCols>&)const;               // .* mat.

	template<int pCols>
	uMatrix<T, mRows, pCols> multiple(const uMatrix<T, nCols, pCols>&)const;                // * mat.

public:
	uMatrix(int = 0, T = 0);                                                                // default constructor.
	//uMatrix(_Index&);                                                                     // construxctor.
	uMatrix(const uMatrix<T, mRows, nCols>&);                                               // copy construxctor.
	uMatrix(const uMatrix<T, mRows, nCols>*);                                               // copy construxctor.
	~uMatrix() {};                                                                          // destructor.
	T& getElement(int = 0, int = 0);                                                        // get the element of the matrix.
	int getRank();                                                                          // get the rank of the matrix. no change to rank.
	_tVector<T, nCols> getRow(int = 0);                                                     // get ith row.
	_Vector<T, mRows> getColumn(int = 0);                                                   // get jth column.
	uMatrix<T, nCols, mRows> transpose();                                                   // get the transpose of the matrix.
	uMatrix<T, mRows + nCols, mRows + nCols> diagnolization();                              // diagonalize the . update the rank.
	void operator=(const uMatrix<T, mRows, nCols>&);                                        // =  overload. rank already set.
	friend ostream& operator<<<T, mRows, nCols>(ostream& s, uMatrix<T, mRows, nCols>&);     // << overload.

	template<typename U> operator uMatrix<U, mRows, nCols>();                               // convert to uMatrix<U>.
	template<typename U> operator eVector<U, mRows>();                                      // convert to uMatrix<U>.
	template<typename U> operator etVector<U, nCols>();                                     // convert to uMatrix<U>.
	operator eMatrix<T, mRows, nCols>();                                                    // convert to eMatrix.
	operator sMatrix<T, mRows>();                                                           // convert to sMatrix.
	operator diagMatrix<T, mRows>();                                                        // convert to diagMatrix.

	template<int kRows> uMatrix<T, kRows, nCols> operator[](_Vector<int, kRows>&);          // select specific rows out of the matrix.
	template<int pCols> uMatrix<T, mRows, pCols> operator[](_tVector<int, pCols>&);         // select specific columns out of the matrix.
	template<int kRows, int pCols>
	uMatrix<T, kRows, pCols> operator()(_Vector<int, kRows>&, _tVector<int, pCols>&);       // select specific components out of the matrix.
	template<int kRows, int pCols>
	uMatrix<T, kRows, pCols> reshape(const _Matrix<kRows, pCols>&);                         // rshape the matrix.

	template<int pCols>
	friend uMatrix<T, mRows, nCols + pCols> operator|(const uMatrix<T, mRows, nCols>& my, const uMatrix<T, mRows, pCols>& mat) { return my.stitch(mat); };
	template<int kRows>
	friend uMatrix<T, mRows + kRows, nCols> operator/(const uMatrix<T, mRows, nCols>& my, const uMatrix<T, kRows, nCols>& mat) { return my.graft(mat); };

	friend uMatrix<T, mRows, nCols> operator+(const uMatrix<T, mRows, nCols>& my, const uMatrix<T, mRows, nCols>& mat) { return my.add(mat); };
	friend uMatrix<T, mRows, nCols> operator+(const uMatrix<T, mRows, nCols>& my, const T& k) { return my.add(k); };
	friend uMatrix<T, mRows, nCols> operator+(const T& k, const uMatrix<T, mRows, nCols>& my) { return my.add(k); };
	friend uMatrix<T, mRows, nCols> operator-(const uMatrix<T, mRows, nCols>& my, const uMatrix<T, mRows, nCols>& mat) { return my.minus(mat); };
	friend uMatrix<T, mRows, nCols> operator-(const uMatrix<T, mRows, nCols>& my, const T& k) { return my.add(-k); };
	friend uMatrix<T, mRows, nCols> operator-(const T& k, const uMatrix<T, mRows, nCols>& my) { return my.minusf(k); };

	friend uMatrix<T, mRows, nCols> operator*(const uMatrix<T, mRows, nCols>& my, const T& k) { return my._multiple(k); };
	friend uMatrix<T, mRows, nCols> operator*(const T& k, const uMatrix<T, mRows, nCols>& my) { return my._multiple(k); };
	friend _Vector<T, mRows> operator*(const uMatrix<T, mRows, nCols>& my, const _Vector<T, nCols>& vec) { return my.multiple(vec); };
	friend uMatrix<T, mRows, nCols> operator^(const uMatrix<T, mRows, nCols>& my, const uMatrix<T, mRows, nCols>& mat) { return my._multiple(mat); };

	template<int pCols>
	friend uMatrix<T, mRows, pCols> operator*(const uMatrix<T, mRows, nCols>& my, const uMatrix<T, nCols, pCols>& mat) { return my.multiple(mat); };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Constructors.		/////////////////////////	protected.
template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols>::uMatrix(int type, T num)
{
	switch (type)
	{
	case all_init:			all<T, mRows, nCols>(vectorSet, num); rank = 1; break;
	case diag_init:			diag<T, mRows, nCols>(vectorSet, num); rank = minDim(mRows, nCols); break;
	case upper_init:		upper<T, mRows, nCols>(vectorSet, num); rank = minDim(mRows, nCols); break;
	case increment_init:	increment<T, mRows, nCols>(vectorSet); rank = -1; break;
	case rand_init:			random<T, mRows, nCols>(vectorSet, num); rank = -1; break;
	default:				all<T, mRows, nCols>(vectorSet, 0); rank = 1; break;
	}
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols>::uMatrix(const uMatrix<T, mRows, nCols>& mat)
{
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			vectorSet[i][j] = mat.vectorSet[i][j];
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols>::uMatrix(const uMatrix<T, mRows, nCols>* mat)
{
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			vectorSet[i][j] = mat->vectorSet[i][j];
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Modifications to the matrix.	/////////////	protected.
template<typename T, int mRows, int nCols>
T& uMatrix<T, mRows, nCols>::meanElements(int power)
{
	int i, j;
	T ans = 0, all_num = 0;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
		{
			if (vectorSet[i][j] != 0) ++all_num;
			if (power == -1) ans = ans + abs(vectorSet[i][j]);						// -1 for abs.
			else if (power > 0) ans = ans + pow(vectorSet[i][j], power);			// to the pth power.
		}
	if (power == 0) return all_num;
	ans = ans / all_num;
	return ans;
	// no change to the matrix or the rank.
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::mergeZero()
{
	int i, j;
	T meanVal = meanElements(-1);
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
		{
			if (abs(vectorSet[i][j] / meanVal) < error)
				vectorSet[i][j] = 0;
		}
	// only used in Gaussian Elimination. no change to the rank.
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::equalize()
{
	int i, j;
	T& deviation = meanElements(-1);
	if (deviation == 0) return;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			vectorSet[i][j] = vectorSet[i][j] / deviation;
	// no change to rank(M).
	if (mRows == nCols) det_sM = det_sM / pow(deviation, mRows);
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::calRank()
{
	if (rank == -1)
	{
		if (mRows <= nCols)
			rowElimination(only_rank);
		else
			colElimination(only_rank);
	}
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::setElement(T& val, int rindex, int cindex)
{
	vectorSet[rindex][cindex] = val;
	// never used. 
	// not necessarily change the rank. 
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::setRow(_tVector<T, nCols> vec, int rindex)
{
	for (int j = 0; j < nCols; ++j)
		vectorSet[rindex][j] = vec.vectorSet[0][j];
	// not necessarily change the rank. 
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::setColumn(_Vector<T, mRows> vec, int cindex)
{
	for (int i = 0; i < mRows; ++i)
		vectorSet[i][cindex] = vec.vectorSet[i][0];
	// not necessarily change the rank. 
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::normRow(int rindex)					// magnify specific column.
{
	//exception needed.
	T factor = vectorSet[rindex][0];
	if (factor != 0) magnifyRow(rindex, 1 / factor);
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::normCol(int cindex)					// magnify specific column.
{
	//exception needed.
	T factor = vectorSet[cindex][0];
	if (factor != 0) magnifyCol(cindex, 1 / factor);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Elementary Transformations.		/////////////	protected.
template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::magnifyRow(int rindex, T factor)					// magnify specific column.
{
	//exception needed.
	if (factor == 1) return;
	for (int j = 0; j < nCols; ++j)
		vectorSet[rindex][j] = vectorSet[rindex][j] * factor;
	det_sM = det_sM * factor;
	// no change to rank.
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::magnifyCol(int cindex, T factor)					// magnify specific column.
{
	//exception needed.
	if (factor == 1) return;
	for (int i = 0; i < mRows; ++i)
		vectorSet[i][cindex] = vectorSet[i][cindex] * factor;
	det_sM = det_sM * factor;
	// no change to rank.
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::switchRows(int rindex1, int rindex2)					// switch specific rows.
{
	//exception needed.
	if (rindex1 == rindex2) return;
	_tVector<T, nCols> bufferRow = getRow(rindex1);
	setRow(getRow(rindex2), rindex1);
	setRow(bufferRow, rindex2);
	det_sM = -det_sM;
	// no change to rank.
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::switchCols(int cindex1, int cindex2)					// switch specific columns.
{
	//exception needed.
	if (cindex1 == cindex2) return;
	_Vector<T, mRows> bufferCol = getRow(cindex1);
	setColumn(getColumn(cindex2), cindex1);
	setColumn(bufferCol, cindex2);
	det_sM = -det_sM;
	// no change to rank.
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::superposRow(int trindex, int srindex, T factor)		// superpose one row to another.
{
	//exception needed.
	for (int j = 0; j < nCols; ++j)
		vectorSet[trindex][j] = vectorSet[trindex][j] + vectorSet[srindex][j] * factor;
	// no change to rank.
}

template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::superposCol(int tcindex, int scindex, T factor)		// superpose one column to another.
{
	//exception needed.
	for (int i = 0; i < mRows; ++i)
		vectorSet[i][tcindex] = vectorSet[i][tcindex] + vectorSet[i][scindex] * factor;
	// no change to rank.
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, mRows> uMatrix<T, mRows, nCols>::rowElimination(int task)			// Gaussian Elimination in rows.
{
	int i, j, max_index = -1;
	int dim = minDim(mRows, nCols);
	bool already_valid = 0, cur_valid = 0, cur_better = 0;
	T cur_max = 0, factor;
	uMatrix<T, mRows, mRows> left_trans = identity(mRows);
	bool empty[mRows];
	rank = 0;
	det_sM = 1;

	for (i = 0; i < mRows; ++i) empty[i] = 0;
	for (j = 0; j < nCols; ++j)
	{
		//cout << "current result = " << endl << *this << endl;
		max_index = -1;
		for (i = 0; i < mRows; ++i)
		{
			already_valid = (max_index >= 0);
			cur_valid = (vectorSet[i][j] != 0 && empty[i] == 0);
			cur_better = (abs(vectorSet[i][j]) >= abs(cur_max));
			//cout << "i = "<<i<<",   already_valid = " << already_valid << ",   cur_valid = " << cur_valid << ",   cur_better = " << cur_better;
			//cout << ",   condition = " << (cur_valid && ((already_valid && cur_better) || !already_valid)) << endl;
			if (cur_valid && ((already_valid && cur_better) || !already_valid))
			{
				cur_max = vectorSet[i][j];
				max_index = i;
			}
		}
		if (abs(cur_max) < error) cur_max = 0;
		if (max_index >= 0 && cur_max != 0 && empty[max_index] == 0)
		{
			//cout << "col = " << j << ",    max = " << cur_max << ",    index = " << max_index << endl;
			for (i = 0; i < mRows; ++i)
			{
				if (i != max_index)
				{
					factor = vectorSet[i][j] / vectorSet[max_index][j];
					superposRow(i, max_index, -factor);
					if (task == with_trans) left_trans.superposRow(i, max_index, -factor);
				}
			}
			if (task == with_trans)
			{
				factor = 1 / cur_max;
				magnifyRow(max_index, factor);
				switchRows(rank, max_index);
				left_trans.magnifyRow(max_index, factor);
				left_trans.switchRows(rank, max_index);
				empty[rank] = 1;
			}
			else
				empty[max_index] = 1;
			++rank;
		}
		mergeZero();
		if (rank == dim) break;
	}
	// update the rank.
	left_trans.mergeZero();
	return left_trans;
}

template<typename T, int mRows, int nCols>
uMatrix<T, nCols, nCols> uMatrix<T, mRows, nCols>::colElimination(int task)			// Gaussian Elimination in columns.
{
	int i, j, max_index = -1;
	int dim = minDim(mRows, nCols);
	bool already_valid = 0, cur_valid = 0, cur_better = 0;
	T cur_max = 0, factor;
	uMatrix<T, nCols, nCols> right_trans = identity(nCols);
	bool empty[nCols];
	rank = 0;
	det_sM = 1;
	
	for (j = 0; j < nCols; ++j) empty[j] = 0;
	for (i = 0; i < mRows; ++i)
	{
		max_index = -1;
		for (j = 0; j < nCols; ++j)
		{
			already_valid = (max_index >= 0);
			cur_valid = (vectorSet[i][j] != 0 && empty[j] == 0);
			cur_better = (abs(vectorSet[i][j]) > abs(cur_max));
			if (cur_valid && ((already_valid && cur_better) || !already_valid))
			{
				cur_max = vectorSet[i][j];
				max_index = j;
			}
		}
		if (abs(cur_max) < error) cur_max = 0;
		if (max_index >= 0 && cur_max != 0 && empty[max_index] == 0)
		{
			//cout << "row = " << i << ",    max = " << cur_max << ",    index = " << max_index << endl;
			for (j = 0; j < nCols; ++j)
			{
				if (j != max_index)
				{
					factor = vectorSet[i][j] / vectorSet[i][max_index];
					superposCol(j, max_index, -factor);
					if (task == with_trans) right_trans.superposCol(j, max_index, -factor);
				}
			}
			if (task == with_trans)
			{
				factor = 1 / cur_max;
				magnifyRow(max_index, factor);
				switchRows(rank, max_index);
				right_trans.magnifyRow(max_index, factor);
				right_trans.switchRows(rank, max_index);
				empty[rank] = 1;
			}
			else
				empty[max_index] = 1;
			++rank;
		}
		mergeZero();
		if (rank == dim) break;
	}
	// update the rank;
	return right_trans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Extensions and Mergences.		/////////////	protected.
template<typename T, int mRows, int nCols>
template<int pCols>
uMatrix<T, mRows, nCols + pCols> uMatrix<T, mRows, nCols>::stitch(const uMatrix<T, mRows, pCols>& mat)const
{
	uMatrix<T, mRows, nCols + pCols> result;
	int i, j;
	for (i = 0; i < mRows; ++i)
	{
		for (j = 0; j < nCols; ++j) result.vectorSet[i][j] = vectorSet[i][j];
		for (j = nCols; j < nCols + pCols; ++j) result.vectorSet[i][j] = mat.vectorSet[i][j - nCols];
	}
	return result;
}

template<typename T, int mRows, int nCols>
template<int kRows>
uMatrix<T, mRows + kRows, nCols> uMatrix<T, mRows, nCols>::graft(const uMatrix<T, kRows, nCols>& mat)const
{
	uMatrix<T, mRows + kRows, nCols> result;
	int i, j;
	for (j = 0; j < nCols; ++j)
	{
		for (i = 0; i < mRows; ++i) result.vectorSet[i][j] = vectorSet[i][j];
		for (i = mRows; i < mRows + kRows; ++i) result.vectorSet[i][j] = mat.vectorSet[i - mRows][j];
	}
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols> uMatrix<T, mRows, nCols>::add(const uMatrix<T, mRows, nCols>& mat)const
{
	uMatrix<T, mRows, nCols> result(this);
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][j] = result.vectorSet[i][j] + mat.vectorSet[i][j];
	result.mergeZero();
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols> uMatrix<T, mRows, nCols>::add(const T& k)const
{
	uMatrix<T, mRows, nCols> result(this);
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][j] = result.vectorSet[i][j] + k;
	result.mergeZero();
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols> uMatrix<T, mRows, nCols>::minus(const uMatrix<T, mRows, nCols>& mat)const
{
	uMatrix<T, mRows, nCols> result(this);
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][j] = result.vectorSet[i][j] - mat.vectorSet[i][j];
	result.mergeZero();
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols> uMatrix<T, mRows, nCols>::minusf(const T& k)const
{
	uMatrix<T, mRows, nCols> result(this);
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][j] = k - result.vectorSet[i][j];
	result.mergeZero();
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols> uMatrix<T, mRows, nCols>::_multiple(const T& k)const
{
	uMatrix<T, mRows, nCols> result(this);
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][j] = result.vectorSet[i][j] * k;
	result.mergeZero();
	return result;
}

template<typename T, int mRows, int nCols>
_Vector<T, mRows> uMatrix<T, mRows, nCols>::multiple(const _Vector<T, nCols>& vec)const
{
	_Vector<T, mRows> result;
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][0] = result.vectorSet[i] + vectorSet[i][j] * vec.vectorSet[j];
	result.mergeZero();
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols> uMatrix<T, mRows, nCols>::_multiple(const uMatrix<T, mRows, nCols>& mat)const
{
	uMatrix<T, mRows, nCols> result(this);
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][j] = result.vectorSet[i][j] * mat.vectorSet[i][j];
	result.mergeZero();
	return result;
}

template<typename T, int mRows, int nCols>
template<int pCols>
uMatrix<T, mRows, pCols> uMatrix<T, mRows, nCols>::multiple(const uMatrix<T, nCols, pCols>& mat)const
{
	uMatrix<T, mRows, pCols> result;
	int i, j, k;
	for (i = 0; i < mRows; ++i)
		for (k = 0; k < pCols; ++k)
			for (j = 0; j < nCols; ++j)
				result.vectorSet[i][k] = result.vectorSet[i][k] + vectorSet[i][j] * mat.vectorSet[j][k];
	result.mergeZero();
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Public Operations.		/////////////////////	public.
template<typename T, int mRows, int nCols>
T& uMatrix<T, mRows, nCols>::getElement(int rindex, int cindex)							// get element.
{
	return vectorSet[rindex][cindex];
}

template<typename T, int mRows, int nCols>
int uMatrix<T, mRows, nCols>::getRank()													// get rank.
{
	calRank();
	return rank;
}

template<typename T, int mRows, int nCols>
_tVector<T, nCols> uMatrix<T, mRows, nCols>::getRow(int rindex)							// get row.
{
	_tVector<T, nCols> result;
	for (int j = 0; j < nCols; ++j)
		result.vectorSet[0][j] = vectorSet[rindex][j];
	return result;
}

template<typename T, int mRows, int nCols>
_Vector<T, mRows> uMatrix<T, mRows, nCols>::getColumn(int cindex)						// get column.
{
	_Vector<T, mRows> result;
	for (int i = 0; i < mRows; ++i)
		result.vectorSet[i][0] = vectorSet[i][cindex];
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, nCols, mRows> uMatrix<T, mRows, nCols>::transpose()							// get transpose.
{
	uMatrix<T, nCols, mRows> result;
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[j][i] = vectorSet[i][j];
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows + nCols, mRows + nCols> uMatrix<T, mRows, nCols>::diagnolization()		// Gaussian Elimination.
{
	// unfinished. 2001040157
	// updated. 2001050039
	// updated. unfinished. 2001060134
	// updated. not confirmed. 2001090041.
	int dim = minDim(mRows, nCols);
	uMatrix<T, mRows, nCols> my(this);
	uMatrix<T, mRows, mRows> left_trans = my.rowElimination();
	uMatrix<T, nCols, nCols> right_trans = my.colElimination();
	rank = my.rank;

	uMatrix<T, nCols, mRows> allzero;
	uMatrix<T, mRows + nCols, mRows + nCols> result = (my | left_trans) / (right_trans | allzero);
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Operator Overload.		/////////////////////	public.
template<typename T, int mRows, int nCols>
void uMatrix<T, mRows, nCols>::operator=(const uMatrix<T, mRows, nCols>& mat)			// = overload.
{
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			vectorSet[i][j] = mat.vectorSet[i][j];
	rank = mat.rank;
}

template<typename T, int mRows, int nCols>
ostream& operator<<(ostream& s, uMatrix<T, mRows, nCols>& mat)							// << overload.
{
	int i, j;
	cout << endl;
	for (i = 0; i < mRows; ++i)
	{
		for (j = 0; j < nCols; ++j)
			s << setw(numberSpace) << mat.vectorSet[i][j];
		s << endl;
	}
	return s;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Format Conversion.		/////////////////////	public/

template<typename T, int mRows, int nCols>
template<typename U>
uMatrix<T, mRows, nCols>::operator uMatrix<U, mRows, nCols>()
{
	uMatrix<U, mRows, nCols> result;
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][j] = vectorSet[i][j];
	result.rank = rank;
	return result;
}

template<typename T, int mRows, int nCols>
template<typename U>
uMatrix<T, mRows, nCols>::operator eVector<U, mRows>()
{
	eVector<U, mRows> result;
	int i, j;
	for (i = 0; i < mRows; ++i)
		result.vectorSet[i][0] = vectorSet[i][0];
	result.update();
	return result;
}

template<typename T, int mRows, int nCols>
template<typename U>
uMatrix<T, mRows, nCols>::operator etVector<U, nCols>()
{
	etVector<U, nCols> result;
	int i, j;
	for (j = 0; j < nCols; ++j)
		result.vectorSet[0][j] = vectorSet[0][j];
	result.update();
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols>::operator eMatrix<T, mRows, nCols>()
{
	eMatrix<T, mRows, nCols> result;
	int i, j;
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < nCols; ++j)
			result.vectorSet[i][j] = vectorSet[i][j];
	result.rank = rank;
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols>::operator sMatrix<T, mRows>()
{
	sMatrix<T, mRows> result;
	int i, j, dim = minDim(mRows, nCols);
	for (i = 0; i < mRows; ++i)
		for (j = 0; j < dim; ++j)
			result.vectorSet[i][j] = vectorSet[i][j];
	result.rank = rank;
	return result;
}

template<typename T, int mRows, int nCols>
uMatrix<T, mRows, nCols>::operator diagMatrix<T, mRows>()
{
	diagMatrix<T, mRows> result;
	int i, j, dim = minDim(mRows, nCols);
	for (i = 0; i < dim; ++i)
		result.vectorSet[i][0] = vectorSet[i][i];
	result.rank = rank;
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////	Content Extraction & Rearrangement.		/////	public.
template<typename T, int mRows, int nCols>
template<int kRows>
uMatrix<T, kRows, nCols> uMatrix<T, mRows, nCols>::operator[](_Vector<int, kRows>& rIndex)
{
	int i, rindex;
	uMatrix<T, kRows, nCols> result;
	for (i = 0; i < kRows; ++i)
	{
		rindex = rIndex.vectorSet[i][0];
		if (rindex < 0 || rindex >= mRows) continue;
		result.setRow(getRow(rindex), i);
	}
	return result;
}

template<typename T, int mRows, int nCols>
template<int pCols>
uMatrix<T, mRows, pCols> uMatrix<T, mRows, nCols>::operator[](_tVector<int, pCols>& cIndex)
{
	int j, cindex;
	uMatrix<T, mRows, pCols> result;
	for (j = 0; j < pCols; ++j)
	{
		cindex = cIndex.vectorSet[0][j];
		if (cindex < 0 || cindex >= nCols) continue;
		result.setColumn(getColumn(cindex), j);
	}
	return result;
}

template<typename T, int mRows, int nCols>
template<int kRows, int pCols>
uMatrix<T, kRows, pCols> uMatrix<T, mRows, nCols>::operator()(_Vector<int, kRows>& rIndex, _tVector<int, pCols>& cIndex)
{
	uMatrix<T, mRows, nCols> my(this);
	uMatrix<T, kRows, nCols> rResult = my[rIndex];
	uMatrix<T, kRows, pCols> result = rResult[cIndex];
	return result;
}

template<typename T, int mRows, int nCols>
template<int kRows, int pCols>
uMatrix<T, kRows, pCols> uMatrix<T, mRows, nCols>::reshape(const _Matrix<kRows, pCols>& matSize)
{
	if (kRows * pCols != mRows * nCols) cout << "- Error: " << endl;	// warning needed. unfinished.
	int i, j;
	uMatrix<T, kRows, pCols> result;
	_Vector<T, mRows * nCols> longVector;
	for (j = 0; j < nCols; ++j)
		for (i = 0; i < mRows; ++i)
			longVector.vectorSet[i + mRows * j][0] = vectorSet[i][j];
	for (j = 0; j < pCols; ++j)
		for (i = 0; i < kRows; ++i)
		{
			if (i + kRows * j < mRows * nCols)
				result.vectorSet[i][j] = longVector.vectorSet[i + kRows * j][0];
		}
	return result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////		//	ELABORATED MATRIX CLASS.
template<typename T, int mRows, int nCols>
class eMatrix :public uMatrix<T, mRows, nCols>
{
protected:
	int inv_type = -1;			// type of inv_matrix: -1 -> unclear. 
								// for square matrices:	0 -> inverse; 1 -> singular.
								// for rectangle matrices: 2 -> pseudo. 3 -> singular.
	uMatrix<T, nCols, mRows> inv_matrix;
protected:
	T squareInv();
	void calInv();
public:
	eMatrix(int type = 0, int num = 0) :uMatrix<T, mRows, nCols>(type, num) {};
	eMatrix(const uMatrix<T, mRows, nCols>& umat) :uMatrix<T, mRows, nCols>(umat) {};
	eMatrix(const uMatrix<T, mRows, nCols>* umat) :uMatrix<T, mRows, nCols>(umat) {};
	eMatrix(const eMatrix<T, mRows, nCols>& emat) :uMatrix<T, mRows, nCols>(emat) {};
	eMatrix(const eMatrix<T, mRows, nCols>* emat) :uMatrix<T, mRows, nCols>(emat) {};
	~eMatrix() {};
	//void operator=(eMatrix<T, mRows, nCols>&);
	int getRank();																			// get the rank. -overload. no change to rank.
	T& getDet();
	uMatrix<T, nCols, mRows> getInv();
};

//template<typename T, int mRows, int nCols>
//void eMatrix<T, mRows, nCols>::elementary(int type, int index1, T& factor, int index2);

template<typename T, int mRows, int nCols>
T eMatrix<T, mRows, nCols>::squareInv()		// only used in calInv() when mRows = nCols. return det(sM).
{
	// unfinished. 2001050042
	// updated. 2001051953
	// updated. easy tests completed. 2001090214
	if (inv_type >= 0) return 0;
	if (this->rank >= 0 && this->rank < mRows)
	{
		inv_type = 1;	// singular matrix.
		return 0;
	}
	//cout << "Calculating Inverse!" << endl;
	int i, j, dim = mRows;
	eMatrix<T, mRows, nCols> my(this);
	eMatrix<T, mRows, mRows> myinv = my.rowElimination(with_trans);
	this->rank = my.getRank();
	for (i = 0; i < nCols; ++i)
	{
		for (j = 0; j < mRows; ++j)
			inv_matrix.vectorSet[i][j] = myinv.vectorSet[i][j];
	}
	inv_matrix.rank = this->rank;

	//cout << "inv = " << endl << inv_matrix << endl;

	//eMatrix<T, mRows, nCols> newmy(this);
	//eMatrix<T, mRows, mRows> product = newmy * inv_matrix;
	//cout << "product = " << endl << product << endl;
	//cout << "rank = " << this->rank << endl;
	if (this->rank < mRows)
	{
		this->det_sM = 0;
		inv_type = 1;		// singular.
	}
	else
	{
		for (i = 0; i < dim; ++i)
			this->det_sM = this->det_sM * my.getElement(i, i);
		inv_type = 1;
	}

	return this->det_sM;
}

template<typename T, int mRows, int nCols>
void eMatrix<T, mRows, nCols>::calInv()
{
	if (inv_type >= 0) return;
	cout << "mRows, nCols = " << mRows << "    " << nCols << endl;
	if (mRows == nCols) squareInv();
	else
	{
		eMatrix<T, mRows, nCols> my(this);
		uMatrix<T, nCols, mRows> my_trans = my.transpose();
		if (mRows > nCols)
		{
			//cout << "1" << endl;
			eMatrix<T, nCols, nCols> mTm = my_trans * my;
			inv_matrix = mTm.getInv() * my_trans;
			this->rank = mTm.getRank();
			if (this->rank == nCols) inv_type = 2;
			else inv_type = 3;
		}
		if (mRows < nCols)
		{
			eMatrix<T, mRows, mRows> mTm = my * my_trans;
			inv_matrix = my_trans * mTm.getInv();
			this->rank = mTm.getRank();
			if (this->rank == mRows) inv_type = 2;
			else inv_type = 3;
		}
	}
}

template<typename T, int mRows, int nCols>
int eMatrix<T, mRows, nCols>::getRank()
{
	if (this->rank == -1) calInv();
	return this->rank;
}

template<typename T, int mRows, int nCols>
uMatrix<T, nCols, mRows> eMatrix<T, mRows, nCols>::getInv()
{
	if (inv_type == -1) calInv();
	return inv_matrix;
}

template<typename T, int mRows, int nCols>
T& eMatrix<T, mRows, nCols>::getDet()
{
	if (inv_type == -1) calInv();
	return this->det_sM;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////		//	square matrix class.
template<typename T, int dim>
class sMatrix;
template<typename T>		using sMatrix2d = sMatrix<T, 2>;
template<typename T>		using sMatrix3d = sMatrix<T, 3>;
using dMatrix3d = sMatrix<double, 3>;
using dMatrix4d = sMatrix<double, 4>;

template<typename T, int dim>
class sMatrix :public eMatrix<T, dim, dim>
{
protected:
	T detM;

public:
	sMatrix(int type = 0, int num = 0) :eMatrix<T, dim, dim>(type, num) {};
	sMatrix(const sMatrix<T, dim>& smat) :eMatrix<T, dim, dim>(smat) {};
	sMatrix(const sMatrix<T, dim>* smat) :eMatrix<T, dim, dim>(smat) {};
	~sMatrix() {};
	//operator rMatrix<T, dim>();				// converted to rMatrix.
	//void operator=(sMatrix<T, dim>&);
	sMatrix<T, dim> getInv();

};

template<typename T, int dim>
sMatrix<T, dim> sMatrix<T, dim>::getInv()
{
	detM = this->squareInv();
	return this->inv_matrix;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////		//	diagonal matrix class.
template<typename T, int dim>
class diagMatrix :public uMatrix<T, dim, 1>
{
protected:
	void calRank();
public:
	diagMatrix(int type = 0, int num = 0) :uMatrix<T, dim, 1>(type, num) { calRank(); };
	diagMatrix(const diagMatrix<T, dim>& mat) :uMatrix<T, dim, 1>(mat) { calRank(); };
	diagMatrix(const diagMatrix<T, dim>* mat) :uMatrix<T, dim, 1>(mat) { calRank(); };
	~diagMatrix() {};
	operator uMatrix<T, dim, dim>();
	int getRank() { return rank; };
	diagMatrix<T, dim> getInv();

	//friend diagMatrix<T, dim> operator+(const diagMatrix<T, dim>& my, const diagMatrix<T, dim>& mat) { return ; };
	friend _Vector<T, dim> operator*(const diagMatrix<T, dim>& my, const _Vector<T, dim>& vec) { return my * vec; };
	friend diagMatrix<T, dim> operator*(const diagMatrix<T, dim>& my, const diagMatrix<T, dim>& mat) { return my * mat; };
	friend uMatrix<T, dim, dim> operator*(const diagMatrix<T, dim>& my, const uMatrix<T, dim, dim>& mat);		// unfinished. 2001051638
};

template<typename T, int dim>
void diagMatrix<T, dim>::calRank()
{
	int i = 0, ans = 0;
	for (i = 0; i < dim; ++i)
		if (this->vectorSet[i] != 0) ++ans;
	this->rank = ans;
}

template<typename T, int dim>
diagMatrix<T, dim>::operator uMatrix<T, dim, dim>()
{
	uMatrix<T, dim, dim> result;	// all zero initialized.
	int i = 0;
	for (i = 0; i < dim; ++i)
		result.vectorSet[i][i] = this->vectorSet[i];
	result.rank = this->rank;
	return result;
}


template<typename T, int dim>
diagMatrix<T, dim> diagMatrix<T, dim>::getInv()
{
	diagMatrix<T, dim> result(this);
	for (int i = 0; i < dim; ++i)
		if (this->vectorSet[i] != 0) result->vectorSet[i] = 1 / this->vectorSet[i];
	return this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////		//	rotation matrix class.
template<typename VT, int dim>
class rMatrix :public sMatrix<VT, dim>
{

protected:
	void normalize();
public:
	rMatrix() :sMatrix<VT, dim>() {};
	rMatrix(const rMatrix<VT, dim>& mat) :sMatrix<VT, dim>(mat) {};
	rMatrix(const rMatrix<VT, dim>* mat) :sMatrix<VT, dim>(mat) {};
	~rMatrix() {
	};

};


#endif