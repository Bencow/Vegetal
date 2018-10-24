//
//  Plant.cpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#include "Plant.hpp"

Plant::Plant(){

}

Plant::~Plant(){

}

Plant::Plant(Vertex* anchor): m_anchor(anchor)
{
	/*
  v_branch.push_back(new Branch(anchor));
  copyData(v_branch[0]->getData(), dataDepart);
  v_branch[0]->setVecDirection(vecDepart);
	*/
}

Plant::Plant(Vertex* anchor, t_data dataDepart, Vect vecDepart): m_anchor(anchor), m_count(0)
{
	//initaialize the anchor of the tree
	m_anchor = anchor;
	//create a first branch
	v_branch.push_back(new Branch(anchor, dataDepart, vecDepart, &m_count));
}

std::ostream& operator <<(std::ostream& out, Plant& myPlant){

  out << "Anchor : " << *myPlant.getAnchor();
  out << "Number of Branch : " << myPlant.getBranchs().size() << "\n";

  for(int i = 0; i < (int)myPlant.getBranchs().size(); i++){
    out << "\tBranch number : " << i << "\n";
    out << *myPlant.getBranchs()[i];
  }

  out << "\n\n";

  return out;
}

void Plant::update(){

	Branch* newBranch;
	//For all the branches in the tree
	std::cout << v_branch.size() << std::endl;
	
	int size_now = v_branch.size();

	for(int i = 0; i < size_now ; i++)
	{
		//update this branch
		newBranch = v_branch[i]->update();
		//And if this branch create a new one
		if(newBranch != NULL)
		{
			//Add this new branch to the tree
		  v_branch.push_back(newBranch);
		}
	}
	//update the counter
	if(m_count < 4)
	{
		m_count++;
		std::cout << "count=" << m_count << std::endl;
	}
	//test
	std::cout << "Update Plant Done\n\n";

}


/* in this version each branch do :
 * - do not create other vertices on the same branch
 * - create 3 new branches equidistant
 * - length of the new edges are the previous edge's length divided by 2
 */
void Plant::update_2()
{
	//get the number of branches at this moment to avoid update the new ones as well
	uint n_branch_prev =  v_branch.size();
	//for each old branch
	for(uint i = 0 ; i < n_branch_prev ; ++i)
	{
		std::vector<Branch*> buds = v_branch[i]->update_2();
		//if the new branch has creates new elements
		if(!buds.empty())
		{
			//add them to the v_branch vector
			v_branch.insert( v_branch.end(), buds.begin(), buds.end());
		}
	}
}


int Plant::getNumberElementPlant(){
  int somme = 0;

  for(int i = 0; i < (int)v_branch.size(); i++){
    somme += v_branch[i]->getNumberElementBranch();
  }

  return somme;
}

int Plant::getNumberFloatPlant(){

  return getNumberElementPlant() * NUMBER_VERTEX_ELEMENT * NUMBER_FLOAT_VERTEX;

}

int Plant::getNumberUniqueVertexPlant(){
  //to count anchor of main branch
  int somme = 1;

  for(int i = 0; i < (int)v_branch.size(); i++){
    somme += v_branch[i]->getNumberVertexBranch();
  }

  return somme;
}

void Plant::fillGfloatArray(GLfloat* arrayGfloat){
  int offset = 0;

  for(int i = 0; i < (int)v_branch.size(); i++){
    offset = v_branch[i]->fillGfloatArray(arrayGfloat, offset);
  }
}

void Plant::fillVectorVertices(std::vector<GLfloat>& vertices){
	//erase the entire vector
	vertices.clear();
	//And fill it again
	for(uint i = 0; i < v_branch.size(); i++){
		v_branch[i]->fillVectorVertices(vertices);
	}
	std::cout << "End fill vector\n";
}