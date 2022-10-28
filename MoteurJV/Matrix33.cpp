#include "Matrix33.h"
#include "Vecteur3D.h"

Matrix33::Matrix33(float indice1, float indice2, float indice3, float indice4, float indice5, float indice6, float indice7, float indice8, float indice9)
{
	values[0] = indice1;
	values[1] = indice2;
	values[2] = indice3;
	values[3] = indice4;
	values[4] = indice5;
	values[5] = indice6;
	values[6] = indice7;
	values[7] = indice8;
	values[8] = indice9;
}
Vecteur3D Matrix33::operator*(const Vecteur3D& vector) const
{
	return Vecteur3D(vector.x * values[0] + vector.y * values[1] + vector.z * values[2],
		vector.x * values[3] + vector.y * values[4] + vector.z * values[5],
		vector.x * values[6] + vector.y * values[7] + vector.z * values[8]);

}

Matrix33 Matrix33::operator*(const Matrix33& other) const 
{
	return Matrix33(
		values[0] * other.values[0] + values[1] * other.values[3] + values[2] * other.values[6],
		values[0] * other.values[1] + values[1] * other.values[4] + values[2] * other.values[7],
		values[0] * other.values[2] + values[1] * other.values[5] + values[2] * other.values[8],
		
		values[3] * other.values[0] + values[4] * other.values[3] + values[5] * other.values[6],
		values[3] * other.values[1] + values[4] * other.values[4] + values[5] * other.values[7],
		values[3] * other.values[2] + values[4] * other.values[5] + values[5] * other.values[8],

		values[6] * other.values[0] + values[7] * other.values[3] + values[8] * other.values[6],
		values[6] * other.values[1] + values[7] * other.values[4] + values[8] * other.values[7],
		values[6] * other.values[2] + values[7] * other.values[5] + values[8] * other.values[8]
		);
}

Matrix33 Matrix33::Inverse() 
{
	//float determinant = values[0] * values[4] * values[8] + values[1] * values[5] * values[6] + values[2] * values[3] * values[7] + values[2] * values[4] * values[6] + values[0] * values[5] * values[7] + values[1] * values[3] * values[8];
	float determinant = values[0] * (values[4] * values[8] - values[7] * values[5])
		- values[1] * (values[3] * values[8] - values[6] * values[5])
		+ values[2] * (values[3] * values[7] - values[6] * values[4]);
	if (determinant != 0.0f) 
	{
		float inver[9];
		inver[0] = values[4] * values[8] - values[5] * values[7] / determinant;
		inver[1] = -(values[1] * values[8] - values[7] * values[2]) / determinant;
		inver[2] = values[1] * values[5] - values[4] * values[2] / determinant;

		inver[3] = -(values[3] * values[8] - values[5] * values[6]) / determinant;
		inver[4] = values[0] * values[8] - values[6] * values[2] / determinant;
		inver[5] = -(values[0] * values[5] - values[3] * values[2]) / determinant;

		inver[6] = values[3] * values[7] - values[6] * values[4] / determinant;
		inver[7] = -(values[0] * values[7] - values[6] * values[1]) / determinant;
		inver[8] = values[0] * values[4] - values[1] * values[3] / determinant;

		return Matrix33(inver[0], inver[1], inver[2], inver[3], inver[4], inver[5], inver[6], inver[7], inver[8]);
	}
}

Matrix33 Matrix33::Transpose() 
{	
	return Matrix33(values[0], values[3], values[6], values[1], values[4], values[7], values[2], values[5], values[8]);
}