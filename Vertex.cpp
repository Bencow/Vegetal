//
//  Vertex.cpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#include "Vertex.hpp"

Vertex::Vertex()
{}
Vertex::Vertex(float x, float y, float z) :
    m_x(x), m_y(y), m_z(z),
    m_r(1.0f), m_g(1.0f), m_b(1.0f),
    m_nx(0.0f), m_ny(0.0f), m_nz(0.0f),
    m_tx(0.0f), m_ty(0.0f)
{}


Vertex::~Vertex(){

}

double Vertex::getAge(){
  //to code with all libraries ...
  return m_born;
}

std::ostream& operator <<(std::ostream& out, Vertex& myVertex){

  out << "x : " << myVertex.getX() << " y : " << myVertex.getY() << " z : " << myVertex.getZ() << "\n";

  return out;
}
