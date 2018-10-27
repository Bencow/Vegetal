//
//  Vertex.cpp
//
//  Author :
//  Quentin Mulliez
//  Benoit Coville
//
//

#include "Vertex.hpp"

Vertex::Vertex()
{}
Vertex::Vertex(float x, float y, float z) :
    m_x(x), m_y(y), m_z(z),
    m_r(1.0f), m_g(1.0f), m_b(1.0f),
    m_nx(0.0f), m_ny(0.0f), m_nz(1.0f),
    m_tx(0.0f), m_ty(0.0f)
{}


Vertex::~Vertex(){

}

double Vertex::getAge(){
  //to code with all libraries ...
  return m_born;
}

std::ostream& operator <<(std::ostream& out, Vertex& v)
{
  //setw is just a function which print the value always on the same number of "space" on the screen
  //because otherwise if x = 6 (1space) and y = -1234.5 (7 spaces) all the other data are shifted during displaying
  out << " x: " << std::setw(4) << v.getX() 
    << " y: " << std::setw(4) << v.getY() 
    << " z: " << std::setw(4) << v.getZ() << "\n";

  return out;
}

int Vertex::fillGfloatArray(GLfloat* arrayGfloat, int offset){

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

	/*
    arrayGfloat[offset] = m_tx;
    offset++;
    arrayGfloat[offset] = m_ty;
    offset++;
	*/
    return offset;

}

void Vertex::fillVectorVertices(std::vector<GLfloat>& vertices)
{
	vertices.push_back(m_x);
    vertices.push_back(m_y);
    vertices.push_back(m_z);

    vertices.push_back(m_r);
    vertices.push_back(m_g);
    vertices.push_back(m_b);

    vertices.push_back(m_nx);
    vertices.push_back(m_ny);
    vertices.push_back(m_nz);

    vertices.push_back(m_tx);
    vertices.push_back(m_ty);
}
