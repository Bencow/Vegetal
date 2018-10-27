//
//  Vect.cpp
//
//  Author :
//  Quentin Mulliez
//  Benoit Coville
//
//

#include "Vect.hpp"
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

int codeZero(const Vect& v)
{
	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();

	if(x == 0)
	{
		if(y==0)
		{
			if(z==0)
				return 8;//xyz==0
			else
				return 5;//xy==0
		}
		else
		{
			if(z==0)
				return 6;//xz==0
			else
				return 2;//x==0
		}
	}
	//x!=0
	if(y==0)
	{
		if(z==0)
			return 7;//yz=0
		else
			return 3;//y==0
	}
	//xy!=0
	if(z==0)
	{
		return 4;//z==0
	}
	else
		return 1;//all diferent from 0
}

void turfu(const Vect& v)
{
	int code = codeZero(v);

	switch(code)
	{
		case 1://all diferent from 0

		break;
		case 2://x==0

		break;
		case 3://y==0

		break;
		case 4://z==0

		break;
		case 5://xy==0

		break;
		case 6://xz==0

		break;
		case 7://yz=0

		break;
		case 8://xyz==0

		break;

		
	}
}

Vect findRandOrthogonal(const Vect& v)
{
	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();

	int r = rand()%2;
	float val = rand()%11;
	Vect u(1,1,1);
	val++;
	val /= 10.0f;

	//std::cout << "r=" << r << " val=" << val << std::endl;

	if(z != 0)// z != 0
	{	
		if(r == 0)
		{
			u.setX(val);
			u.setY(0);
			u.setZ(-(val * x) / z);
		}
		else
		{
			u.setX(0);
			u.setY(val);
			u.setZ(-(val *y )/ z);
		}
	}
	else if(y != 0)
	{
		if(r == 0)
		{
			u.setX(val);
			u.setY(-(val * x) / y);
			u.setZ(0);
		}
		else
		{
			u.setX(0);
			u.setY(-(val * z) / y);
			u.setZ(val);
		}
	}
	else if(x != 0)
	{
		if(r == 0)
		{
			u.setX(-(-val * y) / x);
			u.setY(val);
			u.setZ(0);
		}
		else
		{
			u.setX(-(z * val) / x);
			u.setY(0);
			u.setZ(val);
		}
	}
	else
	{
		std::cout << "Error, try to find orthogonal vector of a null vector";
		if (x==0 && y==0 && z==0 )
		{
			std::cout << " je confirme " << std::endl;
			u.setX(val);
			u.setY(1);
			u.setZ(1);			
		}	
	}
	return u;
}

Vect mixVect(const Vect& v)
{
	Vect u(v.getZ(), v.getY(), v.getX());
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
/*
glm::vec4 convertVect_glm(Vect u)
{
	glm::vec4 v(u.getX(), u.getY(), u.getZ(), 0);

	return v;
}
*/
