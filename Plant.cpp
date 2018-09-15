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

  for(int i = 0; i < (int)v_branch.size(); i++){
    std::cout << "Update ...\n";
    newBranch = v_branch[i]->update();
    if(newBranch != NULL){
      v_branch.push_back(newBranch);
    }
  }

  std::cout << "Update Plant Done\n\n";

}
