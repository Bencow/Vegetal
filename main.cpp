//link statically glew but doesn't work...
//#define GLEW_STATIC

#include <fstream> //fstream
#include <ctime>
#include <chrono>


//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include<iostream> //cout


//Other files of the project
#include "Vect.hpp"
#include "Vertex.hpp"
#include "Branch.hpp"
#include "Plant.hpp"




int main( void )
{
  std::cout << "Hello world\n\n";

  Vect vDepart(1.0f, 0.0f, 0.0f);
  Vertex pointDepart(0.0f, 0.0f, 0.0f);
  t_data dataDepart;
  dataDepart.sizeNewVertices = 1.0f;
  dataDepart.varX = 0.0f;
  dataDepart.varY = 0.0f;
  dataDepart.varZ = 0.0f;

  dataDepart.sizeMaxBranch = 4;


  Plant newPlant(&pointDepart, dataDepart, vDepart);

  std::cout << newPlant;
  newPlant.update();
  std::cout << newPlant;

  return 0;
}
