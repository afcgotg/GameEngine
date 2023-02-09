#include <iostream>

#ifndef __Vector2D__
#define __Vector2D__

class Vector2D{
    public:
        Vector2D(float x, float y): 
            m_x(x), m_y(y){
        }

        float getX();
        float getY();

        void setX(float x);
        void setY(float y);

        float length();
        void normalize();

        friend std::ostream& operator<<(std::ostream &o,const Vector2D &v);

        Vector2D operator+(const Vector2D& v2) const;
        friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);

        Vector2D operator-(const Vector2D& v2) const;
        friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

        Vector2D operator*(float scalar);
        friend Vector2D& operator*=(Vector2D& v1, float scalar);

        Vector2D operator/(float scalar);
        friend Vector2D& operator/=(Vector2D& v1, float scalar);


    private:
        float m_x;
        float m_y;
};

#endif