#ifndef __MODEL_H__
#define __MODEL_H__
#include<vector>
#include<CL/sycl.hpp>
#include<random>
#include <ctime>

#include "ball.h"
class Ball;
struct Fields
{
    int h, w;
    int typeNum;
    int ballNum;
    int time = 0;
    const float rotFriction = 0.5;
    const float friction = 0.1;
    Ball* balls; 
};

class Model{
   public:
    sycl::queue queue;
    std::mt19937 rand;
    Fields f;
    Model(int h, int w, int typeNum, int ballNum);
    ~Model();
    void step();
};
#endif // __MODEL_H__