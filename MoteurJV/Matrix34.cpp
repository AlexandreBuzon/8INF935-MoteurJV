#include "Matrix34.h"



Matrix34::Matrix34() {

	for (int i=0; i < 12; i++)values[i] = 0;

}

Matrix34::Matrix34(float indice1, float indice2, float indice3, float indice4, float indice5, float indice6, float indice7, float indice8, float indice9, float indice10, float indice11, float indice12)
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
	values[9] = indice10;
	values[10] = indice11;
	values[11] = indice12;
}

Vecteur3D Matrix34::operator*(const Vecteur3D& vector) const
{
	return Vecteur3D(vector.x * values[0] + vector.y * values[1] + vector.z * values[2] + values[3],
					vector.x * values[4] + vector.y * values[5] + vector.z * values[6] + values[7],
					vector.x * values[8] + vector.y * values[9] + vector.z * values[10] + values[11]);
}

Matrix34 Matrix34::operator*(const Matrix34& other) const
{
	return Matrix34(other.values[0] * values[0] + other.values[4] * values[1] + other.values[8] * values[2],
		other.values[1] * values[0] + other.values[5] * values[1] + other.values[9] * values[2], 
		other.values[2] * values[0] + other.values[6] * values[1] + other.values[10] * values[2], 
		//other.values[3] * values[0] + other.values[7] * values[1] + other.values[11] * values[2]+ values[3],
		other.values[3] + values[3],
		other.values[0] * values[4] + other.values[4] * values[5] + other.values[8] * values[6], 
		other.values[1] * values[4] + other.values[5] * values[5] + other.values[9] * values[6], 
		other.values[2] * values[4] + other.values[6] * values[5] + other.values[10] * values[6], 
		//other.values[3] * values[4] + other.values[7] * values[5] + other.values[11] * values[6]+ values[7],
		other.values[7] + values[7],
		other.values[0] * values[8] + other.values[4] * values[9] + other.values[8] * values[10], 
		other.values[1] * values[8] + other.values[5] * values[9] + other.values[9] * values[10], 
		other.values[2] * values[8] + other.values[6] * values[9] + other.values[10] * values[10],
		//other.values[3] * values[8] + other.values[7] * values[9] + other.values[11] * values[10]+ values[11]
		other.values[11] + values[11]
		);

}

Matrix33 Matrix34::getM33() {

	return Matrix33(values[0],values[1],values[2],
					values[4], values[5], values[6], 
					values[8], values[9], values[10]);

}

Matrix34 Matrix34::Inverse() 
{
	float inver[12];

	float determinant33 = - values[2] * values[5] * values[8]
						- values[1] * values[4] * values[10]
						- values[0] * values[6] * values[9]
						+ values[0] * values[5] * values[10]
						+ values[1] * values[6] * values[8]
						+ values[2] * values[4] * values[9];

	if (determinant33 != 0.0f)
	{
		float det33_1 = 1.0f / determinant33;

		inver[0] = (-values[9] * values[6] + values[5] * values[10]) * det33_1;
		inver[1] = (values[9] * values[2] - values[1] * values[10]) * det33_1;
		inver[2] = (-values[5] * values[2] + values[1] * values[6]) * det33_1;

		/*inver[3] = (-values[9] * values[6] * values[3]
			- values[5] * values[10] * values[3]
			- values[9] * values[2] * values[7]
			+ values[1] * values[10] * values[7]
			+ values[5] * values[2] * values[11]
			- values[1] * values[6] * values[11]) * det33_1;*/
		inver[3] = -values[3];

		inver[4] = (values[8] * values[6] + values[5] * values[10]) * det33_1;
		inver[5] = (-values[8] * values[2] + values[0] * values[10]) * det33_1;
		inver[6] = (values[4] * values[2] - values[0] * values[6]) * det33_1;

		/*inver[7] = (-values[8] * values[6] * values[3]
			+ values[4] * values[10] * values[3]
			+ values[8] * values[2] * values[7]
			- values[0] * values[10] * values[7]
			- values[4] * values[2] * values[11]
			+ values[0] * values[6] * values[11]) * det33_1;*/
		inver[7] = -values[7];

		inver[8] = (-values[8] * values[5] + values[4] * values[9]) * det33_1;
		inver[9] = (values[8] * values[1] - values[0] * values[9]) * det33_1;
		inver[10] = (-values[4] * values[1] + values[0] * values[5]) * det33_1;

		/*inver[11] = (values[8] * values[5] * values[3]
			- values[4] * values[9] * values[3]
			- values[8] * values[1] * values[7]
			+ values[0] * values[9] * values[7]
			+ values[4] * values[1] * values[11]
			- values[0] * values[5] * values[11]) * det33_1;*/
		inver[11] = -values[7];

		
	}
	else std::throw_with_nested(std::invalid_argument("Erreur : appel de methode inverse sur matrice34 non inversible.\n"));

	return Matrix34(inver[0], inver[1], inver[2], inver[3],
		inver[4], inver[5], inver[6], inver[7],
		inver[8], inver[9], inver[10], inver[11]);

}

Vecteur3D Matrix34::TransformDirection(const Vecteur3D& vector)
{
	return Vecteur3D(
		vector.x * values[0] + vector.y * values[1] + vector.z * values[2],

		vector.x * values[4] + vector.y * values[5] + vector.z * values[6],
		
		vector.x * values[8] + vector.y * values[9] + vector.z * values[10]
	);
}

Vecteur3D Matrix34::TransformPosition(const Vecteur3D& vector)
{
	return Vecteur3D(vector.x + values[3],
					 vector.y + values[7],
					 vector.z + values[11]);
}

void Matrix34::setOrientationAndPosition(const Quaternion& q, const Vecteur3D& p)
{
	values[0] = 1 - (2 * q.value[2] * q.value[2] + 2 * q.value[3] * q.value[3]);
	values[1] = 2 * q.value[1] * q.value[2] + 2 * q.value[3] * q.value[0];
	values[2] = 2 * q.value[1] * q.value[3] - 2 * q.value[2] * q.value[0];
	values[3] = p.x;
	values[4] = 2 * q.value[1] * q.value[2] - 2 * q.value[3] * q.value[0];
	values[5] = 1 - (2 * q.value[1] * q.value[1] + 2 * q.value[3] * q.value[3]);
	values[6] = 2 * q.value[2] * q.value[3] + 2 * q.value[1] * q.value[0];
	values[7] = p.y;
	values[8] = 2 * q.value[1] * q.value[3] + 2 * q.value[2] * q.value[0];
	values[9] = 2 * q.value[2] * q.value[3] - 2 * q.value[1] * q.value[0];
	values[10] = 1 - (2 * q.value[1] * q.value[1] + 2 * q.value[2] * q.value[2]);
	values[11] = p.z;
}

void Matrix34::display() {

	for (int i = 0; i < 12; i++) {

		std::cout << values[i] << " ";

		if (i % 4 == 3)std::cout << std::endl;

	}

	std::cout << std::endl;

}