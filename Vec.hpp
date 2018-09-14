//
//  Vec.hpp
//  code generer
//
//  Created by Quentin Mulliez c3316168 on 13/09/2018.
//
//

#ifndef Vec_hpp
#define Vec_hpp

#include <stdio.h>

class Vec {
  private:
    float m_x;
    float m_y;
    float m_z;

  public:
    Vec();
    Vec(float _x, float _y, float _z);

    ~Vec();

    float getX()const {return m_x;}
    void setX(float value){m_x = value;}

    float getY()const {return m_y;}
    void setY(float value){m_y = value;}

    float getZ()const {return m_z;}
    void setZ(float value){m_z = value;}

    void modifX(float valueToAdd);
    void modifY(float valueToAdd);
    void modifZ(float valueToAdd);

    bool putNormalInside(Vec& vecNormal);


};


#endif /* Vec_hpp */
