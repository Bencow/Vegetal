#include "Data.hpp"


std::ostream& operator <<(std::ostream& out, t_data& myData){

  out << "Size New vertices : " << myData.sizeNewVertices << "\n";
  out << "Variation : x: " << myData.varX << " y: " << myData.varY << " z: " << myData.varZ << "\n";
  out << "Size Max Branch : " << myData.sizeMaxBranch << "\n";

  out << "Frenquency new Branch : " << myData.frequencyNewBranch << "\n";
  out << "Number Branch Creat : " << myData.numberBranchCreat << "\n";

  return out;
}

void dataStructToCop(t_data& dataCop, t_data& dataToCop){

  dataCop.sizeNewVertices = dataToCop.sizeNewVertices;

  dataCop.varX = dataToCop.varX;
  dataCop.varY = dataToCop.varY;
  dataCop.varZ = dataToCop.varZ;

  dataCop.sizeMaxBranch = dataToCop.sizeMaxBranch;

  dataCop.frequencyNewBranch = dataToCop.frequencyNewBranch;
  dataCop.numberBranchCreat = dataToCop.numberBranchCreat;
}

std::istream& operator >>(std::istream& in, t_data& myData){
  std::string valueGet;
  int valueInt;
  float valueFloat;

  do{
    in >> valueGet;
  }while(valueGet != "begin");

  do{
    in >> valueGet;

    if(valueGet == "sizeNewVertices="){
      in >> valueFloat;
      myData.sizeNewVertices = valueFloat;
    }
    else if(valueGet == "varX="){
      in >> valueFloat;
      myData.varX = valueFloat;
    }
    else if(valueGet == "varY="){
      in >> valueFloat;
      myData.varY = valueFloat;
    }
    else if(valueGet == "varZ="){
      in >> valueFloat;
      myData.varZ = valueFloat;
    }
    else if(valueGet == "sizeMaxBranch="){
      in >> valueInt;
      myData.sizeMaxBranch = valueInt;
    }
    else if(valueGet == "frequencyNewBranch="){
      in >> valueInt;
      myData.frequencyNewBranch = valueInt;
    }
    else if(valueGet == "numberBranchCreat="){
      in >> valueInt;
      myData.numberBranchCreat = valueInt;
    }

  }while(valueGet != "end");

  std::cout << myData << "\n";

  return in;
}

void readParameter(t_data& myData) {

	std::string nameFile;
	
	std::cout << "Name of file please : ";

	std::cin >> nameFile;

	std::ifstream fichierData(nameFile.c_str(), std::ios::in);  // on ouvre le fichier en lecture

	while (!fichierData) {
		std::cout << "ERROR NAME DATA\n";
	}

	fichierData >> myData;

	fichierData.close();
}
