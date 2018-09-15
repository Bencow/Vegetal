//
//  Vect.cpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#include "Vect.hpp"

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

std::ostream& operator <<(std::ostream& out, Vect& myVect){

  out << " x: " << myVect.getX() << " y: " << myVect.getY() << " z: " << myVect.getZ() << "\n";

  return out;
}
