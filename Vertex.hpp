//
//  Vertex.hpp
//
//  Author :
//  Quentin Mulliez
//  Benoit Coville
//
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <GL/glew.h>


#include <stdio.h>
#include <iostream>
#include <vector>

#define N_VERTEX_COMP 11


class Vertex {
  private:
    //coordonates
    float m_x;
    float m_y;
    float m_z;
    //Color
    float m_r;
    float m_g;
    float m_b;
    //Normal
    float m_nx;
    float m_ny;
    float m_nz;
    //Texture
    float m_tx;
    float m_ty;

    double m_born;

  public:
    //Constructor
    Vertex();
    Vertex(float x, float y, float z);
    //Destructor
    ~Vertex();

    ///Getter / Setter
    float getX()const {return m_x;}
    void setX(float value){m_x = value;}

    float getY()const {return m_y;}
    void setY(float value){m_y = value;}

    float getZ()const {return m_z;}
    void setZ(float value){m_z = value;}


    float getR()const {return m_r;}
    void setR(float value){m_r = value;}

    float getG()const {return m_g;}
    void setG(float value){m_g = value;}

    float getB()const {return m_b;}
    void setB(float value){m_b = value;}

    float getNX()const {return m_nx;}
    void setNX(float value){m_nx = value;}

    float getNY()const {return m_ny;}
    void setNY(float value){m_ny = value;}

    float getNZ()const {return m_nz;}
    void setNZ(float value){m_nz = value;}

    float getTX()const {return m_tx;}
    void setTX(float value){m_tx = value;}

    float getTY()const {return m_ty;}
    void setTY(float value){m_ty = value;}

    double getBorn()const {return m_born;}
    void setBorn(double value){m_born = value;}

    ///Members
    double getAge();

    int fillGfloatArray(GLfloat* arrayGfloat, int offset);

    void fillVectorVertices(std::vector<GLfloat>& vertices);

};


std::ostream& operator <<(std::ostream& out, Vertex& myVertex);


#endif /* Vertex_hpp */
