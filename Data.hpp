#ifndef Data_hpp
#define Data_hpp



#include <stdio.h>
#include "Vect.hpp"

struct t_data{

  Vect directionNewVertices;

  int sizeNewVertices;
};


std::ostream& operator <<(std::ostream& out, t_data& myData);



#endif
