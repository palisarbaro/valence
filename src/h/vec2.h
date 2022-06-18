#ifndef __VEC2_H__
#define __VEC2_H__
#include<CL/sycl.hpp>

struct vec2{
    float x,y;
    SYCL_EXTERNAL vec2();
    SYCL_EXTERNAL vec2(float x, float y);
    SYCL_EXTERNAL vec2(float fi);
    SYCL_EXTERNAL vec2 operator+(vec2 other) const;
    SYCL_EXTERNAL void operator+=(vec2 other);
    
    SYCL_EXTERNAL vec2 operator-(vec2 other) const;
    SYCL_EXTERNAL void operator-=(vec2 other);

    SYCL_EXTERNAL vec2 operator*(float mult) const;
    SYCL_EXTERNAL void operator*=(float mult);

    SYCL_EXTERNAL vec2 operator/(float div) const;
    SYCL_EXTERNAL void operator/=(float div);


    SYCL_EXTERNAL float dot(vec2 other) const;
    SYCL_EXTERNAL vec2 ort() const;
    SYCL_EXTERNAL vec2 norm() const;
    SYCL_EXTERNAL float len() const;
};
#endif // __VEC2_H__