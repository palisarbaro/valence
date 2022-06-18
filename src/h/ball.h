#ifndef __BALL_H__
#define __BALL_H__
#include<random>

#include"model.h"
#include"vec2.h"
class Model;
struct Valence{
    int type;
    float fi;
    vec2 force;
};

struct Ball{
    vec2 coords;
    vec2 speed;
    vec2 force;

    float fi;
    float rotspeed;
    float moment;

    float radius;
    Valence vals[5];
    Model* model;
    Ball(Model* model);
    
    SYCL_EXTERNAL void step(float dt);
    SYCL_EXTERNAL vec2 getValCoords(int val);
    SYCL_EXTERNAL void calcValForce(int val, Ball& other);
};
#endif // __BALL_H__