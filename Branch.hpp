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

#include "Vertex.hpp"
#include "Vect.hpp"
#include "Data.hpp"

class Branch {
  private:

    std::vector<Vertex> v_vertices;

    //Do we really need an anchor ? the first element of vertices is enough ?
    Vertex* m_anchor;

    Vect m_vecDirection;

    t_data m_data;

  public:
    Branch();
    Branch(Vertex anchor);
    ~Branch();

    Vertex getVertex(int i)const{ return v_vertices[i]; }
    unsigned int getSize()const { return v_vertices.size(); }

    void addVertex(const Vertex& newOne);
    void displayVerticesCoordonate()const;


};


#endif /* Branch_hpp */
