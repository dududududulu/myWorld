#include <iostream>
#include "settings.h"
//#include "Segment.h"
//#include "VectorSpace.h"
//#include "Matrix.h"
#include "Concept.h"
#include "Effect.h"
#include "Entity.h"
#include "VectorSpace.h"
#include "Matrix.h"
using namespace std;

int main()
{
	all_test();


	dVector3d vec(2, 0);
	vec = vec * (PI / 3);
	LnBase<Dimension> base;
	base.printBase();
	base.rotate(vec);
	cout << "vec = " << vec << endl;
	base.printBase();
	dVector3d axis(3, 0);
	uMatrix<double, Dimension, Dimension> R = rotator<double, Dimension>(axis);
	uMatrix<double, Dimension, Dimension> RTR = R.transpose() * R;
	cout << "axis = " << axis << endl;
	cout << "R = " << R << endl;
	cout << "RTR = " << RTR << endl;

	

	return 0;
}
