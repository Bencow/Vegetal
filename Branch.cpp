//
//  Branch.cpp
//
//  Author :
//  Quentin Mulliez
//  Benoit Coville
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

Branch* Branch::update(int updateTurn)
{

  if((int)v_vertices.size() > m_data.sizeMaxBranch)
  {
    std::cout << "size max of the branch is reached" << std::endl;
    return NULL;
  }

  Branch* newBranch = NULL;
  //diminish the size of the new edges
  //m_data.sizeNewVertices = m_data.sizeNewVertices / 1.5f;

  //Variation of next vec direction
  if(*m_count > 0)
  {
    m_vecDirection.setX(m_vecDirection.getX() + (((rand() % 100 * m_data.varX) - (100 * (m_data.varX / 2))) / 100));
    m_vecDirection.setY(m_vecDirection.getY() + (((rand() % 100 * m_data.varY) - (100 * (m_data.varY / 2))) / 100));
	m_vecDirection.setZ(m_vecDirection.getZ() + (((rand() % 100 * m_data.varY) - (100 * (m_data.varZ / 2))) / 100));
  }

  normalize(m_vecDirection);


  //if we decide to create a new branch
  //find a realistic condition !
  //Warning, in x % y, if y < 0 => crash !
  if(rand()%100 <= m_data.frequencyNewBranch && (int)v_vertices.size() < m_data.sizeMaxBranch)
  {
		  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		  //Find a vector orthogonal to the previous direction vector
		  Vect orthogonal = giveOrthoVec(m_vecDirection);
		  normalize(orthogonal);

		  //Create new data with variation lenght
		  if (m_data.sizeNewVertices >= 0.5f) {
			  m_data.sizeNewVertices -= 0.1f;
		  }

		  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		  //Create a new branch with the last node of the previous branch as anchor
		  newBranch = new Branch(&v_vertices.back(), m_data , orthogonal, m_count);
		  //newBranch->createNewVertex();
		  //the current branch create a new vertex
  }
  //the current branch create a new vertex

	createNewVertex(updateTurn);


   return newBranch;
}

void Branch::createNewVertex(int updateTurn)
{
  Vertex lastVertexBranch = v_vertices.back();
  //Pi + (Vi * L)
  //with P previous vertex, V direction vector, L length of the edge
  //note : all the direction vectors have to be normalized, so we use only sizeNewVertices to manage the length
  Vertex newVertex(lastVertexBranch.getX() + (m_vecDirection.getX() * m_data.sizeNewVertices),
             lastVertexBranch.getY() + (m_vecDirection.getY() * m_data.sizeNewVertices),
             lastVertexBranch.getZ() + (m_vecDirection.getZ() * m_data.sizeNewVertices));
  newVertex.setBorn(updateTurn);
  v_vertices.push_back(newVertex);
}


int Branch::getNumberElementBranch(){
  return v_vertices.size();
}

int Branch::getNumberVertexBranch(){
  //anchor count in the previous branch
  return v_vertices.size();
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
	for(int i = 0 ; i < (int)v_vertices.size() - 1 ; ++i)
	{
		//each turn of this loop will add two vertex to the vector -> draw one line
		//all vertex will be stored two times -> better implementation with the element buffer for further version...


    //Now i put only once each vertex -> display only the vertices (not the edges!)
		v_vertices[i].fillVectorVertices(vertices);
  }
}

std::vector<Vertex*> Branch::fillSkeleton()
{
  std::vector<Vertex*> vertices;

  for(int i = 0 ; i < (int)v_vertices.size() ; ++i)
  {
    //Now i put only once each vertex
    //v_vertices[i].fillVectorVertices(vertices);
    vertices.push_back(&v_vertices[i]);
  }
  //Note : we return the vector of vertex because, skeleton is a 2D array !
  return vertices;
}


//first option one leave without any direction and located only at the end of a branch
Vertex Branch::get_leaves_position()
{
  Vertex leaf = v_vertices[v_vertices.size() -1];

  //change the color of the vertex to see that it's a leaf and note a simple branch
  leaf.setR(1);
  leaf.setG(0);
  leaf.setB(0);


  return leaf;//return a pointer to the last element of the branch
}

