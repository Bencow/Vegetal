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
#include "Vec.hpp"
#include "Data.hpp"

class Branch {
  private:

    std::vector<Vertex*> v_vertex;

    Vertex* m_anchor;

    vec m_vecDirection;

    t_data m_data;

  public:
    Branch();
    ~Branch();


};


#endif /* Branch_hpp */
