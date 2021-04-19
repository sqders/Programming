#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <math.h>
#include <string>
using namespace std;
class Point
{
public:

double x=0,y=0;
enum Coord_system{
        Cartesian,
        Polar
    };
Coord_system coord_system=Coord_system::Cartesian;

Point(double a1=0 ,double a2=0,Coord_system coord_system=Coord_system::Cartesian)
{
    x=a1;   // or r
    y=a2;   // or phi
    this->coord_system=coord_system;
};

friend bool operator==(const Point& p1 , const Point& p2)
{
    if(abs(p1.x-p2.x)<0.0000000001&&abs(p1.y-p2.y)<0.0000000001)
{
    return 1;
}
    else return 0;
}
friend bool operator!=(const Point& p1 , const Point& p2)
{
    if(abs(p1.x-p2.x)<0.0000000001&&abs(p1.y-p2.y)<0.0000000001)
{
    return 0;
}
    else return 1;
}

friend std::ostream& operator<<(std::ostream& out,Point p)
{
    return out<<"("<<p.x<<","<<p.y<<")";
}
friend istream &operator>>( istream  &input, Point &p ) {
        string input_string;
        input>>input_string;
        p.x=stod( input_string.substr(1,input_string.find(',')-1));
        p.y=stod(input_string.substr(input_string.find(',')+1,input_string.size()-input_string.find(',')-1));
        return input;
      }

double get_x()
   {
       if(coord_system==Coord_system::Cartesian)
       {
           return x;
       }
       else
       {
           return x*cos(y);
       }
   }
double get_y()
   {
       if(coord_system==Coord_system::Cartesian)
       {
           return y;
       }
       else
       {
           return x*sin(y);
       }
   }
double get_r()
{
    if(coord_system==Coord_system::Cartesian)
    {
        return pow(y*y+x*x,0.5);
    }
    else
        return x;
}
double get_phi()
{
    if(coord_system==Coord_system::Cartesian)
    {
        return atan(y/x);
    }
    else
        return y;
}
};

#endif // POINT_H
