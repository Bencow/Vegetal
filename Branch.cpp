//
//  Branch.cpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//


#include <iostream>
#include "Branch.hpp"

Branch::Branch()
{}

Branch::Branch(Vertex* anchor): m_anchor(anchor){

  v_vertices.push_back(*anchor);
}

Branch::~Branch()
{}

void Branch::addVertex(const Vertex& newOne)
{
  v_vertices.push_back(newOne);
}

std::ostream& operator <<(std::ostream& out, Branch& myBranch){
  for(unsigned int i = 0 ; i < myBranch.getSize() ; i++)
  {
    out << "vertice : " << i << " ->"
              << " x=" << myBranch.getVertices()[i].getX()
              << " y=" << myBranch.getVertices()[i].getY()
              << " z=" << myBranch.getVertices()[i].getZ() << std::endl;
  }

  return out;
}
