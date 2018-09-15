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
    out << "vertix : " << i << "\t-> " << myBranch.getVertices()[i];
  }

  return out;
}

Branch* Branch::update(){

  if((int)v_vertices.size() > m_data.sizeMaxBranch){
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
  m_vecDirection.setX(m_vecDirection.getX() + (rand() % (int)m_data.varX) - (m_data.varX/2));
  m_vecDirection.setY(m_vecDirection.getY() + (rand() % (int)m_data.varY) - (m_data.varY/2));
  m_vecDirection.setZ(m_vecDirection.getZ() + (rand() % (int)m_data.varZ) - (m_data.varZ/2));

  /*
  if(decide to create a new branch){
    return ptr of new branche
  }
  */


    return NULL;

}
