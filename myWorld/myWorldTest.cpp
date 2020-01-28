#include <iostream>
#include "settings.h"
#include "Segment.h"
#include "VectorSpace.h"
#include "Matrix.h"
using namespace std;

int main()
{
	/*
	Can you hear me --------
	double data[3] = { 2.0, 4.3, -1.9 }, data2[3] = {1.1, -3.4, 0.4};
	dVector3d vec(data), vec2(data2);
	double k = 3;
	dVector3d newVec1;
	newVec1 = (vec + vec2);
	dVector3d newVec2 = vec * k;
	vec.transpose();
	double ans = vec * vec2;
	newVec1.print();
	newVec2.print();
	cout << endl << "answer = " << ans << endl;
	*/
	uMatrix<double, 3, 2> mat(2, 3.3);
	//uMatrix<int, 3, 2> intmat = mat;
	sMatrix<double, 4> imat(2, 1);
	sMatrix<double, 4> dmat(3, 1);
	//cout << mat << imat << endl;
	cout << "dmat = " << dmat << endl;
	//uMatrix<double, 6, 2> shapedMat = dmat.reshape(_Matrix<6,2>());

	//cout <<"shapedMat = "<< shapedMat << endl;
	_Vector<int, 3> indexv(3, 1);
	cout << "indexv = " << indexv << endl;

	//uMatrix<double, 3, 3> _dmat = dmat[indexv];
	//cout << "_dmat = " << _dmat << endl;

	dMatrix<4, 5> newdmat(3, 1);
	dMatrix<4, 5> smat(2, 2);
	eMatrix<double, 4, 5> emat = smat + newdmat;
	eMatrix<double, 5, 4> ematInv = emat.getInv();
	eMatrix<double, 4, 4> prod = emat * ematInv;
	cout << "emat = " << emat << endl;
	cout << "ematInv = " << ematInv << endl;
	cout << "prod = " << prod << endl;
	cout << "Done" << endl;
	cout << "Please" << endl;
	/*dMatrix4d whymat = smat ^ imat;
	cout <<"whymat = "<<endl<< whymat << endl;*/

	//uMatrix<double, 3, 8> newmat;
	//newmat = mat|imat|imat;
	//cout << newmat<<endl;
	//uMatrix<double, 7, 3> newmat2 = imat/dmat;
	//cout << newmat2;

	//dMatrix<3, 3> newm;
	//newm = identity(3);
	//newmat = newm * newmat;
	//cout << "newmat = " << endl;
	//cout << newmat << endl;
	
	//_uIndex<double> index = prior | 0.0 | 9.3;
	//cout << index;

	return 0;
}
