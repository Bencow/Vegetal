//
//  Plant.cpp
//  
//	Author :
//  Quentin Mulliez
//	Benoit Coville
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



void Plant::fillVectorVertices(std::vector<GLfloat>& vertices){
	//erase the entire vector
	vertices.clear();
	//And fill it again
	for(uint i = 0; i < v_branch.size(); i++){
		v_branch[i]->fillVectorVertices(vertices);
	}
	std::cout << "End fill vector\n";
}

void Plant::fillSkeleton(std::vector< std::vector<Vertex*> >& skeleton){
	//erase the entire vector
	skeleton.clear();//Now it's useless to earase the skeleton becaus the vertices already created don't change


	std::cout << "number branch " << v_branch.size() << std::endl;
	//And fill it again
	//fill each branch
	for(uint i = 0; i < v_branch.size(); i++)
	{
		skeleton.push_back(v_branch[i]->fillSkeleton());
	}
	std::cout << "End fill skeleton\n";
}

void Plant::add_leaves(std::vector<Vertex*>& leaves_skeleton)
{
	for(uint i = 0 ; i < v_branch.size() ; ++i)
	{
		std::cout << i << std::endl;
		//store the leaves in the plant
		v_leaves.push_back(v_branch[i]->get_leaves_position());
		//and send them to the skeleton for display
		leaves_skeleton.push_back(&v_leaves[i]);
	}
}

uint Plant::getNumberLeaves()
{
	return v_leaves.size();
}