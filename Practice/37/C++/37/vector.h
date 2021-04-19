#ifndef VECTOR_H
#define VECTOR_H
#include <point.h>

class Vector:Point
{

public:

    Point begin,end;

    Vector():begin(0,0),end(1,0){};
    Vector(Point end):begin(0,0),end(end){};
    Vector(Point begin,Point end):begin(begin),end(end){};

    friend bool operator==(const Vector& v1 , const Vector& v2)
    {
        if((v1.end.x-v1.begin.x==v2.end.x-v2.begin.x)&&(v1.end.y-v1.begin.y==v2.end.y-v2.begin.y))
            return 1;
        else
            return 0;
    }
     Vector operator- () const
    {
       Point new_end(-end.x,-end.y);
       return Vector(begin,new_end);

    }
    friend Vector operator+(const Vector& v1, const Vector& v2)
    {
       Vector sum(Point (v1.end.x-v1.begin.x+v2.end.x-v2.begin.x,v1.end.y-v1.begin.y+v2.end.y-v2.begin.y));
       return sum;
    }
    friend Vector operator-(const Vector& v1, const Vector& v2)
    {
       Vector dif(Point (v1.end.x-v1.begin.x-(v2.end.x-v2.begin.x),v1.end.y-v1.begin.y-(v2.end.y-v2.begin.y)));
       return dif;
    }
    friend Vector operator*(const Vector& v1, const double& a)
    {
       Vector mult(Point ((v1.end.x-v1.begin.x)*a,(v1.end.y-v1.begin.y)*a));
       return mult;
    }
    double length()
    {
        return pow((pow((end.x-begin.x),2)+pow((end.y-begin.y),2)),0.5);
    }
    friend double operator*(const Vector& v1, const Vector& v2)
    {
        return (((v1.end.x-v1.begin.x)*(v2.end.x-v2.begin.x))+((v1.end.y-v1.begin.y)*(v2.end.y-v2.begin.y)));
    }
};

#endif // VECTOR_H
