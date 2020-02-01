#include <iostream>
#include "settings.h"
#include "Matrix.h"
#include "VectorSpace.h"
#include "Concept.h"
#include "Entity.h"
#include "Effect.h"
using namespace std;


bool all_test()
{
	bool ans = 1;
	ans = ans & matrix_test();
	ans = ans & entity_test();
	return ans;
}

bool matrix_test()
{
	uMatrix<double, 3, 2> mat(2, 3.3);
	sMatrix<double, 4> imat(2, 1);
	sMatrix<double, 4> dmat(3, 1);
	cout << "dmat = " << dmat << endl;
	uMatrix<double, 6, 2> shapedMat = dmat.reshape(_Matrix<6,2>());
	cout <<"shapedMat = "<< shapedMat << endl;

	_Vector<int, 3> indexv(3, 1);
	cout << "indexv = " << indexv << endl;

	uMatrix<double, 3, 3> _dmat = dmat[indexv];
	cout << "_dmat = " << _dmat << endl;

	dMatrix<4, 5> newdmat(3, 1);
	dMatrix<4, 5> smat(2, 2);
	eMatrix<double, 4, 5> emat = smat + newdmat;
	eMatrix<double, 5, 4> ematInv = emat.getInv();
	eMatrix<double, 4, 4> prod = emat * ematInv;
	cout << "emat = " << emat << endl;
	cout << "ematInv = " << ematInv << endl;
	cout << "prod = " << prod << endl;
	cout << "Matrix Done" << endl;

	uMatrix<double, 4, 9> newmat;
	newmat = newdmat|imat;
	cout << newmat<<endl;
	uMatrix<double, 8, 4> newmat2 = imat/dmat;
	cout << newmat2;

	dVector<5> vec(3, 1);
	dtVector<4> tvec(3, 1);
	dVector<4> resvec;
	resvec = emat * vec;
	dtVector<5> restvec = tvec * emat;
	cout << "vec = " << vec << endl;
	cout << "tvec = " << tvec << endl;
	cout << "emat = " << emat << endl;
	cout << "resvec = " << resvec << endl;
	cout << "restvec = " << restvec << endl;
	vec.normalize(5);
	cout << "vec -n5 = " << vec << endl;
	dtVector<5> newvec(1, 6);
	cout << "newvec = " << newvec << endl;

	dVector3d xvec(2, 0);
	dVector3d yvec(1, 1);
	uMatrix<double, 3, 2> xoy = xvec | yvec;
	dVector3d zvec = xvec ^ yvec;
	uMatrix<double, 3, 2> ctest = zvec ^ xoy;
	cout << "xvec = " << xvec << endl;
	cout << "yvec = " << yvec << endl;
	cout << "zvec = " << zvec << endl;
	cout << "ctest = " << ctest << endl;

	return 1;
}

bool geometry_test()
{
	return 1;
}

bool effect_test()
{
	return 1;
}

bool entity_test()
{
	/*cout << endl << "for entity:" << endl;
	cout << "Constructor:   ";
	Entity ent;
	cout << "MyTest:   ";
	ent.mytest(ent);
	cout << endl << "for object:" << endl;
	cout << "Constructor:   ";
	Object obj;
	cout << "MyTest:   ";
	obj.mytest(obj);
	cout << endl << "for enviro:" << endl;
	cout << "Constructor:   ";
	Enviro env;
	cout << "MyTest:   ";
	env.mytest(env);*/
	
	return 1;
}