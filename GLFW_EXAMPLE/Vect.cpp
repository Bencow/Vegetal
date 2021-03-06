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

//This function is not 100% fiable because, if v(1, 0, 0), this function choose to put the first coordonate to 0
// and then the orthogonal vector is the null vector...
Vect findRandOrthogonalClass(Vect myVec){
	Vect u;
	//better implementation would be setting a random coord and then find a null dot product
	int coord_to_reset = (rand() % 3);

	if(coord_to_reset == 0)
	{
		u.setX(0);
		u.setY( - myVec.getZ() );
		u.setZ( myVec.getY() );
	}
	else if(coord_to_reset == 1)
	{
		u.setX( -myVec.getZ());
		u.setY(0);
		u.setZ( myVec.getX() );
	}
	else if(coord_to_reset == 2)
	{
		u.setX( - myVec.getY());
		u.setY( myVec.getX() );
		u.setZ(0);
	}
	return u;
}

Vect findRandOrthogonalTwoNull(int code){
  Vect u;


  float val1;
  float val2;

  if (rand() % 2 == 0) {
	  val1 = 1.0f;
	  val2 = rand() % 11;
	  val2-=5;
	  val2 /= 10.0f;
	  val1 += val2;

  }
  else {
	  val2 = 1.0f;
	  val1 = rand() % 11;
	  val1-= 5;
	  val1 /= 10.0f;
	  val2 += val1;
  }

  switch (code) {
    case 5:
      u.setZ(0.0f);
      u.setX(val1);
      u.setY(val2);
      break;
    case 6:
      u.setZ(val1);
      u.setX(val2);
      u.setY(0.0f);
      break;
    case 8:
      u.setZ(val1);
      u.setX(0.0f);
      u.setY(val2);
      break;
  }


  return u;
}

int codeZero(const Vect& v){
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

Vect giveOrthoVec(const Vect& myVec)
{
	int code = codeZero(myVec);
	Vect err(0,0,0);//return this Vect in case of a problem
	switch(code)
	{
		case 1://all diferent from 0
      return findRandOrthogonalClass(myVec);
		  break;
		case 2://x==0
      return findRandOrthogonalClass(myVec);
		  break;
		case 3://y==0
      return findRandOrthogonalClass(myVec);
      break;
		case 4://z==0
      return findRandOrthogonalClass(myVec);
      break;
		case 5://xy==0
      return findRandOrthogonalTwoNull(code);
		  break;
		case 6://xz==0
      return findRandOrthogonalTwoNull(code);
		  break;
		case 7://yz=0
      return findRandOrthogonalTwoNull(code);
		  break;
		case 8://xyz==0
      std::cout << "ERROR : vect null ask a orthogonal\n\n";
		  break;
	}
	std::cout << "ERROR, invalid code received in giveOrthoVec function" << std::endl;
	return err;
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

