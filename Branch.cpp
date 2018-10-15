//
//  Branch.cpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//


#include <iostream>
#include "Branch.hpp"

Branch::Branch(){

}

Branch::Branch(Vertex* anchor): m_anchor(anchor){

  v_vertices.push_back(*anchor);
}

Branch::~Branch(){

}

void Branch::addVertex(const Vertex& newOne){
  v_vertices.push_back(newOne);
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

  Vertex& lastVertexBranch = v_vertices[v_vertices.size() - 1];

  //Creation new vertex
  Vertex newVertex(lastVertexBranch.getX() + (m_vecDirection.getX() * m_data.sizeNewVertices),
    			   lastVertexBranch.getY() + (m_vecDirection.getY() * m_data.sizeNewVertices),
    			   lastVertexBranch.getZ() + (m_vecDirection.getZ() * m_data.sizeNewVertices));

  //To put real time
  newVertex.setBorn(0.0);

  addVertex(newVertex);


  //Variation of next vec direction

  //////////////////////////////////////HEre variation turn into int : to upgrade
  /*
  m_vecDirection.setX(m_vecDirection.getX() + (rand() % (int)m_data.varX) - (m_data.varX/2));
  m_vecDirection.setY(m_vecDirection.getY() + (rand() % (int)m_data.varY) - (m_data.varY/2));
  m_vecDirection.setZ(m_vecDirection.getZ() + (rand() % (int)m_data.varZ) - (m_data.varZ/2));
*/

  /*
  if(decide to create a new branch){
    return ptr of new branche
  }
  */


    return NULL;

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
		//all vertex will be stored to times -> better implementation with the element buffer for further version...
		v_vertices[i].fillVectorVertices(vertices);
		v_vertices[i+1].fillVectorVertices(vertices);
	}
}