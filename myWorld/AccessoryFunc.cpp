#include <iostream>
#include "settings.h"
using namespace std;

int minDim(int mRows, int nCols)
{
	if (mRows > nCols) return nCols;
	return mRows;
}