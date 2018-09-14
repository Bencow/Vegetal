//
//  Vec.cpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#include "Vec.hpp"

Vec::Vec(){

}

Vec(float _x, float _y, float _z): m_x(_x), m_y(_y), m_z(_z){

}

Vec::~Vec(){

}

void Vec::modifX(float valueToAdd){
  m_x += valueToAdd;
}

void Vec::modifY(float valueToAdd){
  m_y += valueToAdd;
}

void Vec::modifZ(float valueToAdd){
  m_z += valueToAdd;
}


bool Vec::putNormalInside(Vec& vecNormal){

  //To check

  vecNormal.setX(0.0f);
  vecNormal.setY(- m_z);
  vecNormal.setZ(m_y);
  
  return true;
}
