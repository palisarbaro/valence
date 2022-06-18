#include"h/vec2.h"
vec2::vec2(float x, float y):x(x), y(y)
{
    
}

vec2::vec2():vec2(0,0)
{

}

vec2::vec2(float fi):vec2(sycl::cos(fi),sycl::sin(fi))
{
     
}

vec2 vec2::operator-(vec2 other) const
{
    return vec2(x-other.x,y-other.y);
}

void vec2::operator-=(vec2 other)
{
    (*this)=(*this)-other;
}

void vec2::operator*=(float mult)
{
    (*this)=(*this)*mult;
}
void vec2::operator/=(float div)
{
    (*this)=(*this)/div;
}

vec2 vec2::operator/(float div) const
{
    return vec2(x/div,y/div);
}

float vec2::dot(vec2 other) const
{
    return x*other.x + y*other.y;
}

vec2 vec2::ort() const
{
    return vec2(-y,x);
}

SYCL_EXTERNAL vec2 vec2::norm() const
{
    return (*this)/len();
}

float vec2::len() const
{
    return sycl::sqrt(this->dot(*this));
}



void vec2::operator+=(vec2 other)
{
    (*this)=(*this)+other;
}

vec2 vec2::operator*(float mult) const
{
    return vec2(x*mult,y*mult);
}

vec2 vec2::operator+(vec2 other) const
{
    return vec2(x+other.x,y+other.y);
}


