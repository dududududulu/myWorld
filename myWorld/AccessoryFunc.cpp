#include <iostream>
#include "settings.h"
#include "Reference.h"
#include "Matrix.h"
#include "VectorSpace.h"
using namespace std;

int minDim(int mRows, int nCols)
{
	if (mRows > nCols) return nCols;
	return mRows;
}

bool infinitesimal(double data)
{
	if (data < Numerical_Error && data > -Numerical_Error)
		return 1;
	return 0;
}

