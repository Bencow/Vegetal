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

/////////////////////here
int Vertex::fillGfloatArray(float* arrayGfloat, int offset){

    arrayGfloat[offset] = m_x;
    offset++;
    arrayGfloat[offset] = m_y;
    offset++;
    arrayGfloat[offset] = m_z;
    offset++;

    arrayGfloat[offset] = m_r;
    offset++;
    arrayGfloat[offset] = m_g;
    offset++;
    arrayGfloat[offset] = m_b;
    offset++;

    arrayGfloat[offset] = m_nx;
    offset++;
    arrayGfloat[offset] = m_ny;
    offset++;
    arrayGfloat[offset] = m_nz;
    offset++;

    arrayGfloat[offset] = m_tx;
    offset++;
    arrayGfloat[offset] = m_ty;
    offset++;

    return offset;

}
