//
//  Branch.hpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#ifndef Branch_hpp
#define Branch_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>


#include "Vertex.hpp"
#include "Vect.hpp"
#include "Data.hpp"

class Branch {
  private:

    std::vector<Vertex> v_vertices;

    //Do we really need an anchor ? the first element of vertices is enough ?
    ///By security, if the anchor move, we have something coherant
    Vertex* m_anchor;

    Vect m_vecDirection;

    t_data m_data;

  public:
    Branch();
    Branch(Vertex* anchor);
    ~Branch();

    Vertex getVertex(int i)const{ return v_vertices[i]; }
    unsigned int getSize()const { return v_vertices.size(); }

    void setVecDirection(Vect value){ m_vecDirection = value;}

    t_data& getData(){return m_data;}

    std::vector<Vertex>& getVertices(){return v_vertices;}


    void addVertex(const Vertex& newOne);

    Branch* update();

};

std::ostream& operator <<(std::ostream& out, Branch& myBranch);


#endif /* Branch_hpp */
