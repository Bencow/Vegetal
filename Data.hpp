#ifndef Data_hpp
#define Data_hpp



#include <stdio.h>
#include <fstream>
#include "Vect.hpp"

#include <string>

struct t_data{

  float sizeNewVertices;

  float varX;
  float varY;
  float varZ;

  int sizeMaxBranch;
  int frequencyNewBranch;
  int numberBranchCreat;
};


std::ostream& operator <<(std::ostream& out, t_data& myData);

void copyData(t_data& dataCop, t_data& dataToCop);
std::istream& operator >>(std::istream& in, t_data& myData);

void readParameter(t_data& myData);


#endif
