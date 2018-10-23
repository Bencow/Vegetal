//
//  Plant.hpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include <stdio.h>
#include "Vertex.hpp"
#include "Branch.hpp"

#include <vector>
#include<iostream>

#define NUMBER_FLOAT_VERTEX 9
#define NUMBER_VERTEX_ELEMENT 2


class Plant {
  private:

    Vertex* m_anchor;

    std::vector<Branch*> v_branch;


  public:
    Plant();
    Plant(Vertex* anchor);
    Plant(Vertex* anchor, t_data dataDepart, Vect vecDepart);

    ~Plant();

    Vertex* getAnchor()const {return m_anchor;}
    void setAnchor(Vertex* value){m_anchor = value;}

    std::vector<Branch*>& getBranchs(){return v_branch;}

    void update();
    void update_2();

    int getNumberBranch()const { return v_branch.size(); }

    int getNumberElementPlant();

    int getNumberFloatPlant();

    int getNumberUniqueVertexPlant();

    void fillGfloatArray(GLfloat* arrayGfloat);

    void fillVectorVertices(std::vector<GLfloat>& vertices);




};

std::ostream& operator <<(std::ostream& out, Plant& myPlant);


#endif /* Plant_hpp */
