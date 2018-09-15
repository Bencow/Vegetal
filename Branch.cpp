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

Branch::Branch(Vertex anchor)
{
  v_vertices.push_back(anchor);
}

Branch::~Branch()
{}

void Branch::addVertex(const Vertex& newOne)
{
  v_vertices.push_back(newOne);
}

void Branch::displayVerticesCoordonate()const
{
  for(unsigned int i = 0 ; i < v_vertices.size() ; i++)
  {
    std::cout << "vx: " << i
              << " x=" << v_vertices[i].getX()
              << " y=" << v_vertices[i].getY()
              << " z=" << v_vertices[i].getZ() << std::endl;
  }
}
