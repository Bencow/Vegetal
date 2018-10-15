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

Plant::Plant(Vertex* anchor, t_data dataDepart, Vect vecDepart): m_anchor(anchor){

  v_branch.push_back(new Branch(anchor));
  dataStructToCop(v_branch[0]->getData(), dataDepart);
  v_branch[0]->setVecDirection(vecDepart);

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
	for(int i = 0; i < (int)v_branch.size(); i++)
	{
		//update this branch
		newBranch = v_branch[i]->update();
		//And if this branch created a new one
		if(newBranch != NULL)
		{
			//Add this new branch to the tree
		   	v_branch.push_back(newBranch);
		}
	}
	//test
	std::cout << "Update Plant Done\n\n";

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