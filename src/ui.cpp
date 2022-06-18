#include <GL/glut.h>
#include "h/ui.h"
#include<chrono>
#include<iostream>
#include<cctype>
Model* UI::model = nullptr;
bool UI::showFPS = false;
bool UI::stopped = false;
int UI::targetMS = 0;

std::chrono::steady_clock::time_point timeFPS = std::chrono::steady_clock::now();
void STEP(int v){
    if(UI::stopped){
        return;
    }

    auto t = timeFPS;
    timeFPS = std::chrono::steady_clock::now();
    if(UI::showFPS){
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timeFPS - t).count();
        std::cout<< ms << " ms; "<<1000./ms<<" FPS" << std::endl;
    }
    UI::model->step();
    display();
    glutTimerFunc(UI::targetMS, STEP,1);
}
void init(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(UI::model->f.w, UI::model->f.h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    gluOrtho2D(0,UI::model->f.w,0,UI::model->f.h);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1, STEP,1);
}

void loop()
{
    glutMainLoop();
}
void setColor(int val){
    switch (val)
    {
    case 0:
        glColor3f(0,0,1);
        break;
    case 1:
        glColor3f(0,1,0);
        break; 
    case 2:
        glColor3f(0,1,1);
        break;
    case 3:
        glColor3f(1,1,0);
        break;
    case 4:
        glColor3f(1,0,1);
        break;
    case 5:
        glColor3f(1,0,0);
        break;
    default:
        throw -111;
    }
}
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 20; 
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); 
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
void display()
{
    float d = 1;
	glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<UI::model->f.ballNum;i++){
        Ball ball = UI::model->f.balls[i];
        glColor3f(1,0.7,0.7);
        drawFilledCircle(ball.coords.x,ball.coords.y,ball.radius);
        for(int i=0;i<std::extent<decltype(ball.vals)>::value;i++) {
            vec2 point = ball.getValCoords(i);
            setColor(ball.vals[i].type);
            drawFilledCircle(point.x,point.y,3);  
        }

    }
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
    key = tolower(key);
    if(key=='f'){
        UI::showFPS = !UI::showFPS;
    }

    if(key==' '){
        UI::stopped=!UI::stopped;
        if(!UI::stopped){
            glutTimerFunc(UI::targetMS, STEP,1);
        }
    }
    if(key>='0' && key<='9'){ //fps
        int mss[10] = {0,20,50,100,200,300,500,1000,2000,3000};
        int d = key-'0';
        UI::targetMS = mss[d];
        std::cout<<"target fps: "<< mss[d] << " ms; "<<1000./mss[d]<<" FPS" << std::endl;

    }
    display();
}
