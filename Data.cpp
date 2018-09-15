#include "Data.hpp"


std::ostream& operator <<(std::ostream& out, t_data& myData){

  out << "Size New vertices : " << myData.sizeNewVertices << "\n";
  out << "Variation : x: " << myData.varX << " y: " << myData.varY << " z: " << myData.varZ << "\n";
  out << "Size Max Branch : " << myData.sizeMaxBranch << "\n";

  return out;
}
