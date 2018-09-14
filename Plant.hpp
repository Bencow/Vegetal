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

class Plant {
  private:

    Vertex m_anchor;

    std::vector<Branch*> v_branche;


  public:
    Plant();
    ~Plant();


};


#endif /* Plant_hpp */
