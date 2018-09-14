//
//  Plante.hpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#ifndef Plante_hpp
#define Plante_hpp

#include <stdio.h>
#include "Vertex.hpp"
#include "Branch.hpp"

#include <vector>

class Plante {
  private:

    Vertex m_anchor;

    std::vector<Branch*> v_branche;


  public:
    Plante();
    ~Plante();


};


#endif /* Plante_hpp */
