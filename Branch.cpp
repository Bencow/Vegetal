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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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

/* in this version each branch do :
 * - do not create other vertices on the same branch
 * - create 3 new branches equidistant
 * - length of the new edges are the previous edge's length divided by 2
 */
//Doesn't work -> return only one branch -> solution return a vector of branch
std::vector<Branch*> Branch::update_2()
{
  std::vector<Branch*> newBranches;
	//if the branch has not finished to grow
	if(!m_finished)
	{
		//create 3 new branches
		for(int i = 0 ; i < 3 ; ++i)
		{
			//create the branch and initialize the anchor with the last element of the previous branch
			//				  Branch(last_vertex_of_the_actual_branch)
			Branch* bud = new Branch(&v_vertices[v_vertices.size()-1]);//it can be neater with iterator ?	
			
			//set the direction vector of the new branch

			//Find a vector orthogonal to the previous direction vector
      Vect orth = findRandOrthogonal(m_vecDirection);

      //rotate around direction vector of the branch
      //3 new branches : 0°, 120° and 240°
      //create a vec to create the glm::matrix
      glm::vec3 old_dir;
      old_dir.x = m_vecDirection.getX();
      old_dir.y = m_vecDirection.getY();
      old_dir.z = m_vecDirection.getZ();
      //initialize the matrix
      glm::mat4 transform = glm::mat4(1.0f);
      transform = glm::rotate(transform, glm::radians(i * 120.0f), old_dir);

      //apply the transform to the orthogonal vector to find the two other vectors
      glm::vec4 dir = transform * glm::vec4(convertVect_glm(orth));
      
      //casting it to our own type
      Vect newDirection(dir.x, dir.y, dir.z);

      bud->setVecDirection(newDirection);

      //then create a new point on this branch
      bud->createNewVertex();

      newBranches.push_back(bud);
		}
		//stop this branch to grow
		//to avoid creating three other branches on the next turn
		m_finished = true;
	}
	//Store the new branch in the plant
	//return the vector (which may be empty !)
  return newBranches;
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
	for(uint i = 0 ; i < v_vertices.size() - 1 ; ++i)
	{
		//each turn of this loop will add two vertex to the vector -> draw one line
		//all vertex will be stored two times -> better implementation with the element buffer for further version...


    //Now i try to put only once each vertex
		v_vertices[i].fillVectorVertices(vertices);
		//v_vertices[i+1].fillVectorVertices(vertices);
	}
}
std::vector<GLfloat> Branch::fillSkeleton()
{
  std::vector<GLfloat> vertices;

  for(uint i = 0 ; i < v_vertices.size() ; ++i)
  {
    //Now i try to put only once each vertex
    v_vertices[i].fillVectorVertices(vertices);
  }
  return vertices;
}