#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <math.h>

#include "Camera.h"
#include <stdio.h>

CGLCamera myCamera;

int W, H;
float asp=1.0;
int px=-1, py=-1;

void init(void) {
    glClearColor(0.8, 0.9, 0.9, 0.0);
    glEnable(GL_DEPTH_TEST);
    myCamera.SetCamera(1,0,1, 0,0,0, 0,1,0);
}

void reshape(int w, int h) {
    asp = float(w)/float(h);
    W = w; H = h;
}


void DrawAxes(void) {
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);	glVertex3f(1,0,0);
    glColor3f(0,0.5,0);
    glVertex3f(0,0,0);	glVertex3f(0,1,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);	glVertex3f(0,0,1);
    glEnd();
}

void DrawScene(void) {
    glLineWidth(4);
    DrawAxes();
    
    
    glLineWidth(1);
    
    for(int i=0;i<10;i++) {
        glColor3f(float(i%3)/6.0, 0.5-float(i%5)/10.0, float (i%2)/4.0);
        glTranslatef(0,0,-1);
        glutWireSphere(0.5,120,120);
    }
    
    
}
void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // VIEWPORT 1
    glViewport(0,0,W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, asp, 1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    myCamera.ApplyCamera();
    
    DrawScene();
    
    
    glutSwapBuffers();
}

void keyboard(unsigned char k, int x, int y) {
    switch(k) {
        case 27: exit(0);
        case 'w': case 'W':
            myCamera.MoveForward(0.1);break;
        case 's': case 'S':
            myCamera.MoveForward(-0.1); break;
        case 'a': case 'A':
            myCamera.MoveRight(-0.1);break;
        case 'd': case 'D':
            myCamera.MoveRight(0.1); break;
    }
    glutPostRedisplay();
    
}

void specialKey(int k, int x, int y) {
    switch(k) {
        case GLUT_KEY_UP:	myCamera.RotatePitch(0.01); break;
        case GLUT_KEY_DOWN:	myCamera.RotatePitch(-0.01); break;
        case GLUT_KEY_LEFT:	myCamera.RotateHead(0.01); break;
        case GLUT_KEY_RIGHT:myCamera.RotateHead(-0.01); break;
    }
    glutPostRedisplay();
    
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100,100);
    glutCreateWindow("신바람 강박사 뷰잉 프로젝트!");
    
    init(); // 초기화
    
    // 콜백 함수 등록 
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutReshapeFunc(reshape);
    
    
    glutMainLoop(); // 무한루프
    return 0;
}