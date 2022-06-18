#ifndef __UI_H__
#define __UI_H__
#include "model.h"
class UI{
  public:
    static Model* model;
    static bool showFPS;
    static bool stopped;
    static int targetMS;
};
void init(int argc, char* argv[]);
void loop();
void display();
void keyboard(unsigned char key,int x,int y);
#endif // __UI_H__