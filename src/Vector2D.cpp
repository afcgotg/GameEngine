#include <math.h>

#include "Vector2D.h"

Vector2D::Vector2D(){
    mX = 0;
    mY = 0;
}

Vector2D::Vector2D(float x, float y): 
    mX(x), mY(y){
}

float Vector2D::getX(){
    return mX;
}
float Vector2D::getY(){
    return mY;
}

void Vector2D::setX(float x){
    mX = x;
}

void Vector2D::setY(float y){
    mY = y;
}

float Vector2D::length(){
    return sqrt(pow(mX, 2) + pow(mY, 2));
}

void Vector2D::normalize(){
    float l = length();
    if(l > 0){
        (*this) /= l;
    }
}

std::ostream& operator<<(std::ostream &o,const Vector2D &v){
    o << "(" << v.mX << ", " << v.mY << ")";
    return o;
}

Vector2D Vector2D::operator+(const Vector2D& v2) const{
    return Vector2D(mX + v2.mX, mY + v2.mY);
}

Vector2D& operator+=(Vector2D& v1, const Vector2D& v2){
    v1.mX += v2.mX;
    v1.mY += v2.mY;
    return v1;
}

Vector2D Vector2D::operator-(const Vector2D& v2) const{
    return Vector2D(mX - v2.mX, mY - v2.mY);
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2){
    v1.mX -= v2.mX;
    v1.mY -= v2.mY;
    return v1;
}

Vector2D Vector2D::operator*(float scalar){
    return Vector2D(mX * scalar, mY * scalar);
}

Vector2D& operator*=(Vector2D& v1, float scalar){
    v1.mX *= scalar;
    v1.mY *= scalar;
    return v1;
}

Vector2D Vector2D::operator/(float scalar){
    return Vector2D(mX / scalar, mY / scalar);
}

Vector2D& operator/=(Vector2D& v1, float scalar){
    v1.mX /= scalar;
    v1.mY /= scalar;
    return v1;
}
