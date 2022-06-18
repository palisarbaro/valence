#include "h/model.h"
#include <algorithm>
const int view_radius = 3;
const int visible_cells_count = (view_radius*2+1)*(view_radius*2+1);
const int actions_count = 10;
Model::Model(int h, int w, int typeNum, int ballNum)
{
    rand.seed(std::time(nullptr));
    f.h = h;
    f.w = w;
    f.typeNum = typeNum;
    f.ballNum = ballNum;
    auto device = sycl::platform::get_platforms()[0].get_devices()[0];
    std::cout<< device.get_info<sycl::info::device::name>()<<std::endl;
    queue = sycl::queue(device);
    f.balls = sycl::malloc_shared<Ball>(ballNum,queue);
    for(int i=0;i<f.ballNum;i++){
        f.balls[i] = Ball(this);
    }
}

Model::~Model()
{
    sycl::free(f.balls,queue);
}

void Model::step()
{
    Fields& f = this->f;
    sycl::event e = queue.parallel_for(sycl::range<1>(f.ballNum), [=](sycl::item<1> item) {
        int indx = item.get_linear_id();
        Ball& ball = f.balls[indx];
        ball.moment -= ball.rotspeed*f.rotFriction;
        ball.force -= ball.speed*f.friction;
        for(int val=0;val<std::extent<decltype(ball.vals)>::value;val++){
            ball.vals[val].force = vec2();
        }
        for(int i=0;i<f.ballNum;i++){
            if(i==indx) continue;
            Ball& ball2 = f.balls[i];
            for(int val=0;val<std::extent<decltype(ball.vals)>::value;val++){
               ball.calcValForce(val,ball2);
            }
            vec2 dcoord = ball2.coords-ball.coords;
            float r = dcoord.len() - ball.radius-ball2.radius;
            if(r<0){
                //ball.force -= dcoord.norm()*sycl::fabs(r)/100.;
                ball.coords -=dcoord.norm();
                ball2.coords +=dcoord.norm();
            }
        }
        ball.step(0.5);
    });
    e.wait_and_throw();
    f.time++;
}

