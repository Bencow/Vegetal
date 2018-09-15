#ifndef Data_hpp
#define Data_hpp



#include <stdio.h>
#include "Vect.hpp"

struct t_data{

  float sizeNewVertices;

  float varX;
  float varY;
  float varZ;

  int sizeMaxBranch;
};


std::ostream& operator <<(std::ostream& out, t_data& myData);



#endif
