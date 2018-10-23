//
//  Vect.cpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#include "Vect.hpp"
#include<iomanip>//setw
#include <cmath>



Vect::Vect()
{}

Vect::Vect(float _x, float _y, float _z):
m_x(_x), m_y(_y), m_z(_z)
{}

Vect::~Vect()
{}

void Vect::modifX(float valueToAdd){
  m_x += valueToAdd;
}

void Vect::modifY(float valueToAdd){
  m_y += valueToAdd;
}

void Vect::modifZ(float valueToAdd){
  m_z += valueToAdd;
}


bool Vect::putNormalInside(Vect& vectNormal){

  //To check

  vectNormal.setX(0.0f);
  vectNormal.setY(- m_z);
  vectNormal.setZ(m_y);

  return true;
}

std::ostream& operator <<(std::ostream& out, Vect& myVect)
{
	//setw is just a function which print the value always on the same number of "space" on the screen
	//because otherwise if x = 6 (1space) and y = -1234.5 (7 spaces) all the other data are shifted during displaying
	out << " x: " << std::setw(4) << myVect.getX() 
		<< " y: " << std::setw(4) << myVect.getY() 
		<< " z: " << std::setw(4) << myVect.getZ() << "\n";
	return out;
}

void Vect::operator =(const Vect vectToCop){
  m_x = vectToCop.getX();
  m_y = vectToCop.getY();
  m_z = vectToCop.getZ();
}

//Pre condition : the input vector must not be null
//Post condition : return the value of the componant not equal to zero
int twoComponantEqualZero(const Vect& v)
{
	if(v.getX() == 0 && v.getY() == 0)
		return 3;
	else if(v.getY() == 0 && v.getZ() == 0)
		return 2;
	else if(v.getZ() == 0 && v.getX() == 0)
		return 3;
	else
		return 0;//at least two componants are different from 0
}

//This function is not 100% fiable because, if v(1, 0, 0), this function choose to put the first coordonate to 0
// and then the orthogonal vector is the null vector...
Vect findRandOrthogonal_1(const Vect& v)
{
	Vect u;
	//better implementation would be setting a random coord and then find a null dot product
	int coord_to_reset = (rand() % 3);

	if(coord_to_reset == 0)
	{
		u.setX(0);
		u.setY( - v.getZ() );
		u.setZ( v.getY() );
	}
	else if(coord_to_reset == 1)
	{
		u.setX( -v.getZ());
		u.setY(0);
		u.setZ( v.getX() );
	}
	else if(coord_to_reset == 2)
	{
		u.setX( - v.getY());
		u.setY( v.getX() );
		u.setZ(0);
	}
	return u;
}
Vect findRandOrthogonal(const Vect& v)
{
	Vect u;
	int r;
	if(v.getZ() != 0)// z != 0
	{	
		r = rand()%2;
		if(r == 0)
		{
			u.setX(1);
			u.setY(0);
			u.setZ(-v.getX() / v.getZ());
		}
		else
		{
			u.setX(0);
			u.setY(1);
			u.setZ(-v.getY() / v.getZ());
		}
	}
	else if(v.getY() != 0)
	{
		r = rand()%2;
		if(r == 0)
		{
			u.setX(1);
			u.setY(-v.getX() / v.getY());
			u.setZ(0);
		}
		else
		{
			u.setX(0);
			u.setY(-v.getZ() / v.getY());
			u.setZ(1);
		}
	}
	else if(v.getX() != 0)
	{
		r = rand()%2;
		if(r == 0)
		{
			u.setX(-v.getY() / v.getX());
			u.setY(1);
			u.setZ(0);
		}
		else
		{
			u.setX(-v.getZ() / v.getX());
			u.setY(0);
			u.setZ(1);
		}
	}
	else
		std::cout << "Error, try to find orthogonal vector of a null vector"
	return u;
}

Vect crossProduct(Vect v, Vect u)
{
	Vect w;
	w.setX( v.getY()*u.getZ() - v.getZ()*u.getY() );
	w.setY( v.getZ()*u.getX() - v.getX()*u.getZ() );
	w.setZ( v.getX()*u.getY() - v.getY()*u.getX() );
	return w;
}

//return false if it's the vector null
bool normalize(Vect& v)
{
	//calculate the norm of v
	double norm = sqrt( pow(v.getX(), 2) + pow(v.getY(), 2) + pow(v.getZ(), 2) );
	if(norm == 0)
	{
		std::cout << "Caution this vector is null !!!" << std::endl;
		return false;
	}
	else
	{	
		//Divide all the components of v by the norm
		v.setX(v.getX() / norm);
		v.setY(v.getY() / norm);
		v.setZ(v.getZ() / norm);
		return true;
	}
}

//return a matrix 3*3
void rotateX(double alpha, Vect rotateMatrix[3])
{
	Vect u(1, 0, 0);
	Vect v(0, cos(alpha), -sin(alpha));
	Vect w(0, sin(alpha),  cos(alpha));

	rotateMatrix[0] = u;
	rotateMatrix[1] = v;
	rotateMatrix[2] = w;
}


void getTransposeMatrix(Vect M[3], Vect M_T[3])
{
	int i = 0;
	M_T[i].setX(M[0].getX());
	M_T[i].setZ(M[1].getX());
	M_T[i].setZ(M[2].getX());
	i++;
	M_T[i].setX(M[0].getY());
	M_T[i].setZ(M[1].getY());
	M_T[i].setZ(M[2].getY());
	i++;
	M_T[i].setX(M[0].getZ());
	M_T[i].setZ(M[1].getZ());
	M_T[i].setZ(M[2].getZ());
}

glm::vec4 convertVect_glm(Vect u)
{
	glm::vec4 v(u.getX(), u.getY(), u.getZ(), 0);

	return v;
}

/*
void matrixProduct(Vect A[3], Vect B[3], Vect R[3])
{
	R[0].setX( A[0].getX()*B[0].getX() + A[0].getY()*B[1].getgetX() + A[0].getZ()*B[2].getgetX() );
	R[0].setY( A[0].getX()*B[0].getX() + A[0].getY()*B[1].getgetX() + A[0].getZ()*B[2].getgetX() );
	R[0].setZ( A[0].getX()*B[0].getX() + A[0].getY()*B[1].getgetX() + A[0].getZ()*B[2].getgetX() );
	R[1].setX( A[1].getX()*B[0].getY() + A[1].getY()*B[1].getgetY() + A[1].getZ()*B[2].getgetY() );
	R[1].setY( A[1].getX()*B[0].getY() + A[1].getY()*B[1].getgetY() + A[1].getZ()*B[2].getgetY() );
	R[1].setZ( A[1].getX()*B[0].getY() + A[1].getY()*B[1].getgetY() + A[1].getZ()*B[2].getgetY() );
	R[2].setX( A[2].getX()*B[0].getZ() + A[2].getY()*B[1].getgetZ() + A[2].getZ()*B[2].getgetZ() );
	R[2].setY( A[2].getX()*B[0].getZ() + A[2].getY()*B[1].getgetZ() + A[2].getZ()*B[2].getgetZ() );
	R[2].setZ( A[2].getX()*B[0].getZ() + A[2].getY()*B[1].getgetZ() + A[2].getZ()*B[2].getgetZ() );
}
*/


//v is an orthogonal vector to the plane we want to rotate in
//alpha is the angle of a rotation
/*
Vect rotateVectorArbitraryAxis(Vect u, double alpha )
{
	//conversion from degree to radians
	alpha = apha * 0.01745329;


	//find an ONB :
	Vect v = findRandOrthogonal(u);
	normalize(u);
	normalize(v);

	Vect w = crossProduct(u, v);
	//initialize the change-of-basis-matrix (from F to E)
	Vect M[3] = {u , v , w};
	
	//rotation matrix of 120° around X
	Vect Rx[3];
	rotateX(120, Rx);

	//transpose of M
	Vect M_T[3];
	getTransposeMatrix(M, M_T);

	Vect tranform[3];
	//Do the the first product
	matrixProduct(M, Rx, tranform);
	//Do the second one
	matrixProduct(tranform, M_T, tranform);


}
*/



/* Rotation around an arbitrary axis
 * Param :
 * u , v 
 *
 */
/*
Vect rotation2D(Vect u, Vect v, float alpha)
{

}
*/