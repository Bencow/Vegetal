//
//  Branch.hpp
//
//  Author :
//  Quentin Mulliez
//  Benoit Coville
//
//

#ifndef Branch_hpp
#define Branch_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>


#include "Vertex.hpp"
#include "Vect.hpp"
#include "Data.hpp"

class Branch {
  private:

    std::vector<Vertex> v_vertices;

    //Do we really need an anchor ? the first element of vertices is enough ?
    ///By security, if the anchor move, we have something coherant
    Vertex* m_anchor;

    Vect m_vecDirection;

    t_data m_data;

    int* m_count;

    bool m_finished;

  public:
    Branch();
    Branch(Vertex* anchor);
    Branch(Vertex* anchor, t_data dataDepart, Vect vecDepart,int* count);
    ~Branch();

    Vertex getVertex(int i)const{ return v_vertices[i]; }
    unsigned int getSize()const { return v_vertices.size(); }

    void setVecDirection(Vect value){ m_vecDirection = value; }
    void setDataSizeMax(int val) {m_data.sizeMaxBranch = val; }
    t_data& getData(){return m_data;}

    std::vector<Vertex>& getVertices(){return v_vertices;}

    bool getFinished() const { return m_finished; }
    void setFinished(bool val){ m_finished = val; }

    void addVertex(const Vertex& newOne);

    Branch* update();
    void createNewVertex();


    int getNumberElementBranch();

    int getNumberVertexBranch();

    int fillGfloatArray(GLfloat* arrayGfloat, int offset);

    void fillVectorVertices(std::vector<GLfloat>& vertices);
    std::vector<Vertex*> fillSkeleton();

};

std::ostream& operator <<(std::ostream& out, Branch& myBranch);


#endif /* Branch_hpp */
