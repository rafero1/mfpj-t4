#include "matrix.h"

#include <iostream>

matrix::matrix(	real m0, real m4, real m8,	real m12,
				real m1, real m5, real m9,	real m13,
				real m2, real m6, real m10, real m14,
				real m3, real m7, real m11, real m15)
{
	data[0]  = m0;
	data[4]  = m4;
	data[8]  = m8;
	data[12] = m12;

	data[1]  = m1;
	data[5]  = m5;
	data[9]  = m9;
	data[13] = m13;

	data[2]  = m2;
	data[6]  = m6;
	data[10] = m10;
	data[14] = m14;

	data[3]  = m3;
	data[7]	 = m7;
	data[11] = m11;
	data[15] = m15;
}

matrix::matrix(real data[16]) 
{ 
	for (int i = 0; i < size(); i++) 
		this->data[i] = data[i];
}

matrix matrix::multiply(const matrix &m) const
{
	return matrix(	
		data[0]*m.data[0]  + data[4]*m.data[1]  + data[8]*m.data[2]  + data[12] * m.data[3],
		data[0]*m.data[4]  + data[4]*m.data[5]  + data[8]*m.data[6]  + data[12] * m.data[7],
		data[0]*m.data[8]  + data[4]*m.data[9]  + data[8]*m.data[10] + data[12] * m.data[11],
		data[0]*m.data[12] + data[4]*m.data[13] + data[8]*m.data[14] + data[12] * m.data[15],

		data[1] * m.data[0] + data[5] * m.data[1] + data[9] * m.data[2] + data[13] * m.data[3],
		data[1] * m.data[4] + data[5] * m.data[5] + data[9] * m.data[6] + data[13] * m.data[7],
		data[1] * m.data[8] + data[5] * m.data[9] + data[9] * m.data[10] + data[13] * m.data[11],
		data[1] * m.data[12] + data[5] * m.data[13] + data[9] * m.data[14] + data[13] * m.data[15],

		data[2] * m.data[0] + data[6] * m.data[1] + data[10] * m.data[2] + data[14] * m.data[3],
		data[2] * m.data[4] + data[6] * m.data[5] + data[10] * m.data[6] + data[14] * m.data[7],
		data[2] * m.data[8] + data[6] * m.data[9] + data[10] * m.data[10] + data[14] * m.data[11],
		data[2] * m.data[12] + data[6] * m.data[13] + data[10] * m.data[14] + data[14] * m.data[15],

		data[3] * m.data[0] + data[7] * m.data[1] + data[11] * m.data[2] + data[15] * m.data[3],
		data[3] * m.data[4] + data[7] * m.data[5] + data[11] * m.data[6] + data[15] * m.data[7],
		data[3] * m.data[8] + data[7] * m.data[9] + data[11] * m.data[10] + data[15] * m.data[11],
		data[3] * m.data[12] + data[7] * m.data[13] + data[11] * m.data[14] + data[15] * m.data[15]
	);
}

matrix matrix::identity()
{
	return matrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

matrix matrix::identity(const matrix& m)
{
	return identity().multiply(m);
}

matrix matrix::translate(const Vec3& v)
{
	matrix m = identity();
	m.data[3] = v.x;
	m.data[7] = v.y;
	m.data[11] = v.z;
	return multiply(m);
}

matrix matrix::scale(const Vec3& v)
{
	matrix m = identity();
	m.data[0] = v.x;
	m.data[5] = v.y;
	m.data[10] = v.z;
	return multiply(m);
}

matrix matrix::rotateX(real angle)
{
	matrix m = identity();
	m.data[5] = std::cos(angle);
	m.data[6] = std::sin(angle);
	m.data[9] = -std::sin(angle);
	m.data[10] = std::cos(angle);
	return multiply(m);
}

matrix matrix::rotateY(real angle)
{
	matrix m = identity();
	m.data[0] = std::cos(angle);
	m.data[2] = -std::sin(angle);
	m.data[8] = std::sin(angle);
	m.data[10] = std::cos(angle);
	return multiply(m);
}

matrix matrix::rotateZ(real angle)
{
	matrix m = identity();
	m.data[0] = std::cos(angle);
	m.data[1] = std::sin(angle);
	m.data[4] = -std::sin(angle);
	m.data[5] = std::cos(angle);
	return multiply(m);
}

matrix matrix::rotateN(const Vec3& u, real angle)
{
	matrix m = identity();
	m.data[0] = ((u.x * u.x) * -std::cos(angle)) + std::cos(angle);
	m.data[1] = ((u.x * u.y) * -std::cos(angle)) + (u.z * std::sin(angle));
	m.data[2] = ((u.x * u.z) * -std::cos(angle)) - (u.y * std::sin(angle));
	
	m.data[4] = ((u.x * u.y) * -std::cos(angle)) - (u.z * std::sin(angle));
	m.data[5] = ((u.y * u.y) * -std::cos(angle)) + std::cos(angle);
	m.data[6] = ((u.y * u.z) * -std::cos(angle)) + (u.x * std::sin(angle));

	m.data[8] = ((u.x * u.z) * -std::cos(angle)) + (u.y * std::sin(angle));
	m.data[9] = ((u.y * u.z) * -std::cos(angle)) - (u.x * std::sin(angle));
	m.data[10] = ((u.z * u.z) * -std::cos(angle)) + std::cos(angle);
	return multiply(m);
}

matrix matrix::transpose()
{
	return matrix(
		data[0], data[1], data[2], data[3],
		data[4], data[5], data[6], data[7],
		data[8], data[9], data[10], data[11],
		data[12], data[13], data[14], data[15]
	);
}

void matrix::transposeOf(const matrix& m)
{
	data[0]  = m.data[0];
	data[4]  = m.data[1];
	data[8]  = m.data[2];
	data[12] = m.data[3];
	
	data[1] = m.data[4];
	data[5] = m.data[5];
	data[9] = m.data[6];
	data[13] = m.data[7];

	data[2] = m.data[8];
	data[6] = m.data[9];
	data[10] = m.data[10];
	data[14] = m.data[11];
	
	data[3] = m.data[12];
	data[7] = m.data[13];
	data[11] = m.data[14];
	data[15] = m.data[15];
}

void matrix::print()
{
	/*int n = 1;
	int max = 0;
	for (int i = 0; i < size(); i++) {
		if (data[i] > max)
			max = data[i];
	}

	max = abs(max);
	n = (max < 10 ? 1 :
		(max < 100 ? 2 :
		(max < 1000 ? 3 :
		(max < 10000 ? 4 :
		(max < 100000 ? 5 :
		(max < 1000000 ? 6 :
		(max < 10000000 ? 7 :
		(max < 100000000 ? 8 :
		(max < 1000000000 ? 9 :
		10)))))))));*/

	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j == 0)
				std::cout << "| ";
			std::cout << data[j *4];
			std::cout << ' ';
			if (j == 4)
				std::cout << "|" << std::endl;
		}
	}*/
	
	std::cout << "| " << data[0] << " " << data[4] << " " << data[8] << " " << data[12] << " |" << std::endl;
	std::cout << "| " << data[1] << " " << data[5] << " " << data[9] << " " << data[13] << " |" << std::endl;
	std::cout << "| " << data[2] << " " << data[6] << " " << data[10] << " " << data[14] << " |" << std::endl;
	std::cout << "| " << data[3] << " " << data[7] << " " << data[11] << " " << data[15] << " |" << std::endl;
}
