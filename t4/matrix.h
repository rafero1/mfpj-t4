#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include "Vec3.h"

typedef double real;
class matrix
{
public:
	real data[16] = {0.0};

	matrix() {};

	matrix(real data[16]);

	matrix(	real m0, real m4, real m8,	real m12,
			real m1, real m5, real m9,	real m13,
			real m2, real m6, real m10, real m14,
			real m3, real m7, real m11, real m15);

	int size() { return sizeof(data)/sizeof(data[0]); }

	void print();

	// Multiplicação entre matrizes
	matrix multiply(const matrix &m) const;

	// Identidade
	matrix identity();
	matrix identity(const matrix& m);

	// Translação
	matrix translate(const Vec3& v);

	// Escala
	matrix scale(const Vec3& v);

	// Rotação em X, Y, Z, eixo qualquer
	matrix rotateX(real angle);
	matrix rotateY(real angle);
	matrix rotateZ(real angle);
	matrix rotateN(const Vec3& v, real angle);
	
	// Transposição
	matrix transpose();
	void transposeOf(const matrix& m);

};

#endif // !MATRIX_H