//
//  Plant.hpp
//
//  Author :
//  Quentin Mulliez
//  Benoit Coville
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
    std::vector<Vertex> v_leaves;
    int m_count;

	int m_turnUpdate;

  public:
    Plant();
    Plant(Vertex* anchor);
    Plant(Vertex* anchor, t_data dataDepart, Vect vecDepart);

    ~Plant();

    Vertex* getAnchor()const {return m_anchor;}
    void setAnchor(Vertex* value){m_anchor = value;}

    std::vector<Branch*>& getBranchs(){return v_branch;}

    void update();

    int getNumberBranch()const { return v_branch.size(); }

    int getNumberElementPlant();

    int getNumberFloatPlant();

    int getNumberUniqueVertexPlant();
    
    int getNumberLeaves();

	int getTurnUpdate() const { return m_turnUpdate;}


    void fillVectorVertices(std::vector<GLfloat>& vertices);
    void fillSkeleton(std::vector< std::vector<Vertex*> >& skeleton);
    void add_leaves(std::vector<Vertex*>& leaves_skeleton);



};

std::ostream& operator <<(std::ostream& out, Plant& myPlant);


#endif /* Plant_hpp */
