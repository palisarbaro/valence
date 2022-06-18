
#include "h/ball.h"
Ball::Ball(Model* model):model(model)
{
    coords.x = model->rand()%model->f.w;
    coords.y = model->rand()%model->f.h;
    // speed = vec2(0.5,0.5);
    // rotspeed = 0.1;
    //moment = 1;
    //force = vec2(1,1);
    radius = model->rand()%10+10;
    for(int i=0;i<std::extent<decltype(vals)>::value;i++){
        vals[i].type = model->rand()%model->f.typeNum;
        vals[i].fi = 359./(model->rand()%360)*M_PI*2;
    }
}

void Ball::step(float dt)
{
    for(int i=0;i<std::extent<decltype(vals)>::value;i++){
        force += vals[i].force;
        moment += vals[i].force.dot(vec2(fi+vals[i].fi+M_PI/2)*radius);
    }
    speed += force*dt;
    rotspeed += moment*dt;
    coords += speed*dt;
    fi += rotspeed;

    force = vec2();
    moment = 0;
}

SYCL_EXTERNAL vec2 Ball::getValCoords(int val)
{
    vec2 point = vec2(fi+vals[val].fi)*radius*2./3.;
    point += coords;
    return point;
}

SYCL_EXTERNAL void Ball::calcValForce(int val, Ball& other)
{
    for(int val2=0;val2<std::extent<decltype(other.vals)>::value;val2++){
        vec2 dcoord = other.getValCoords(val2)-getValCoords(val);
        float r = dcoord.len();
        if (r<2) continue;
        vals[val].force += dcoord/r/r/r*(vals[val].type==other.vals[val2].type?-1:+1);

    }
}
