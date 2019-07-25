// t4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <cmath>
#include <iostream>
#include "matrix.h"
#include "Vec3.h"

using namespace std;

int main(int argc, char const* argv[]) {
	matrix m1(
		0.0, 4.0, 2.0, 2.0,
		1.0, 5.0, 3.0, 3.0,
		2.0, 6.0, 1.0, 4.0,
		1.0, 1.0, 1.0, 1.0);

	m1.print();
	cout << "\n";

	matrix m2(
		0.0, 4.0, 8.0, 2.0,
		1.0, 5.0, 4.0, 6.0,
		2.0, 6.0, 3.0, 4.0,
		1.0, 1.0, 1.0, 1.0);
	
	m2.print();
	cout << "\n";

	matrix r = m1.multiply(m2);
	r.print();
	cout << "\n";
	
	r = m1.identity(m2);
	r.print();
	cout << "\n";

	r = m1.translate(Vec3(1, 2, 3));
	r.print();
	cout << "\n";

	r = m1.scale(Vec3(2, 2, 2));
	r.print();
	cout << "\n";

	cout << Vec3(1, 2, 1).angle(Vec3(1, 1, 3)) << endl;
	return 0;
}
