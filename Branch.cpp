//
//  Branch.cpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//


#include <iostream>
#include "Branch.hpp"
#include "Vect.hpp"

Branch::Branch(){

}

Branch::Branch(Vertex* anchor): m_anchor(anchor)
{
  m_data.sizeMaxBranch = 100;//Should not be hardcoded
  m_data.sizeNewVertices = 0.2f;//idem

  v_vertices.push_back(*anchor);
  m_finished = false;
}

Branch::Branch(Vertex* anchor, t_data dataDepart, Vect vecDepart, int* count) : m_anchor(anchor), m_count(count)
{
  copyData(m_data, dataDepart);
  m_vecDirection = vecDepart;
  m_finished = false;
  v_vertices.push_back(*anchor);//v_vertices<Vertex> so dereference anchor !
}

Branch::~Branch(){

}

std::ostream& operator <<(std::ostream& out, Branch& myBranch){

  for(unsigned int i = 0 ; i < myBranch.getSize() ; i++)
  {
    out << "vertex : " << i << " -> " << myBranch.getVertices()[i];
  }

  return out;
}

Branch* Branch::update()
{

  if((int)v_vertices.size() > m_data.sizeMaxBranch)
  {
    std::cout << "size max of the branch is reached" << std::endl;
    return NULL;
  }

  //diminish the size of the new edges
  m_data.sizeNewVertices = m_data.sizeNewVertices / 1.5f;

  //Variation of next vec direction
  if(*m_count > 0)
  {
    m_vecDirection.setX(( ((rand() % 100) - 50)/40) );
    m_vecDirection.setY(( ((rand() % 100) - 50)/40) );
    //Doesn't change in Z for now
  }
  
  normalize(m_vecDirection);

  //if we decide to create a new branch
  //find a realistic condition !
  //Warning, in x % y, if y < 0 => crash !
  if(rand()%(5 - *m_count) == 0 && *m_count > 0)
  //if(true)
  {
    //Find a vector orthogonal to the previous direction vector
    Vect orthogonal = findRandOrthogonal(m_vecDirection);
    normalize(orthogonal);
    //Create a new branch with the last node of the previous branch as anchor
    Branch* newBranch = new Branch(&v_vertices.back(), m_data, orthogonal, m_count);
    newBranch->createNewVertex();
    //the current branch create a new vertex
    createNewVertex();
    return newBranch;
  }
  //the current branch create a new vertex
  createNewVertex();

   return NULL;
}

void Branch::createNewVertex()
{
  Vertex lastVertexBranch = v_vertices.back();
  //Pi + (Vi * L)
  //with P previous vertex, V direction vector, L length of the edge
  //note : all the direction vectors have to be normalized, so we use only sizeNewVertices to manage the length
  Vertex newVertex(lastVertexBranch.getX() + (m_vecDirection.getX() * m_data.sizeNewVertices),
             lastVertexBranch.getY() + (m_vecDirection.getY() * m_data.sizeNewVertices),
             lastVertexBranch.getZ() + (m_vecDirection.getZ() * m_data.sizeNewVertices));
  newVertex.setBorn(0.0);
  v_vertices.push_back(newVertex);
}


int Branch::getNumberElementBranch(){
  return v_vertices.size() - 1;
}

int Branch::getNumberVertexBranch(){
  //anchor count in the previous branch
  return v_vertices.size() - 1;
}


int Branch::fillGfloatArray(GLfloat* arrayGfloat, int offset){

  for(int i = 0; i < (int)v_vertices.size() - 1; i++){
    offset = v_vertices[i].fillGfloatArray(arrayGfloat, offset);
    offset = v_vertices[i + 1].fillGfloatArray(arrayGfloat, offset);
  }

  return offset;
}

void Branch::fillVectorVertices(std::vector<GLfloat>& vertices)
{
	for(uint i = 0 ; i < v_vertices.size() - 1 ; ++i)
	{
		//each turn of this loop will add two vertex to the vector -> draw one line
		//all vertex will be stored two times -> better implementation with the element buffer for further version...


    //Now i try to put only once each vertex
		v_vertices[i].fillVectorVertices(vertices);
		//v_vertices[i+1].fillVectorVertices(vertices);
	}
}