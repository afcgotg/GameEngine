#include <math.h>

#include "Vector2D.h"

Vector2D::Vector2D(){
    m_x = 0;
    m_y = 0;
}

Vector2D::Vector2D(float x, float y): 
    m_x(x), m_y(y){
}

float Vector2D::getX(){
    return m_x;
}
float Vector2D::getY(){
    return m_y;
}

void Vector2D::setX(float x){
    m_x = x;
}

void Vector2D::setY(float y){
    m_y = y;
}

float Vector2D::length(){
    return sqrt(pow(m_x, 2) + pow(m_y, 2));
}

void Vector2D::normalize(){
    float l = length();
    if(l > 0){
        (*this) /= l;
    }
}

std::ostream& operator<<(std::ostream &o,const Vector2D &v){
    o << "(" << v.m_x << ", " << v.m_y << ")";
    return o;
}

Vector2D Vector2D::operator+(const Vector2D& v2) const{
    return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D& operator+=(Vector2D& v1, const Vector2D& v2){
    v1.m_x += v2.m_x;
    v1.m_y += v2.m_y;
    return v1;
}

Vector2D Vector2D::operator-(const Vector2D& v2) const{
    return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2){
    v1.m_x -= v2.m_x;
    v1.m_y -= v2.m_y;
    return v1;
}

Vector2D Vector2D::operator*(float scalar){
    return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& operator*=(Vector2D& v1, float scalar){
    v1.m_x *= scalar;
    v1.m_y *= scalar;
    return v1;
}

Vector2D Vector2D::operator/(float scalar){
    return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& operator/=(Vector2D& v1, float scalar){
    v1.m_x /= scalar;
    v1.m_y /= scalar;
    return v1;
}
