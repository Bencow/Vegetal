#include "Data.hpp"


std::ostream& operator <<(std::ostream& out, t_data& myData){

  out << "Direction New vertices : " << myData.directionNewVertices;
  out << "Size New vertices : " << myData.sizeNewVertices << "\n";

  return out;
}
