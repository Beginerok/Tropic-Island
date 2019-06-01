#include "Vector3.h"
Vector3::Vector3()
{
}
Vector3::Vector3(float__ x,float__ y,float__ z)
{
    this->a[0]=x;
    this->a[1]=y;
    this->a[2]=z;
}
int__ Vector3::Size()
{
    return 3;
}
Vector3::~Vector3()
{
}
