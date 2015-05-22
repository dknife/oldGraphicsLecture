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
#include "Camera.h"
CGLCamera myCamera;

float zoom = 1.0;
float aspRatio = 1.0;

void DrawAxis(float a, float b, float c)
{
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(a,b,c);
    glVertex3f(0,0,0);
    glVertex3f(a,b,c);
    glEnd();
}

void DrawAxes(void) {
    DrawAxis(1,0,0); // x 축
    DrawAxis(0,1,0); // y 축
    DrawAxis(0,0,1); // z 축
}


void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    myCamera.SetCamera(-1,0.0,1, 0,0,0, 0,1,0 );
}

void ResetProjection(float aspRatio) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // orthographic camera
    // glOrtho(-aspRatio*zoom, aspRatio*zoom, -1*zoom, 1*zoom, 0.1, 100);
    
    // perspective camera
    gluPerspective(60 /* degree */ , aspRatio, 0.1, 100);
}
// reshape callback
void reshape(int w, int h) {
    aspRatio = float(w)/float(h);
    glViewport(0,0,w,h);
    ResetProjection(aspRatio);
    glutPostRedisplay();
}

void DrawSphereAt(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x,y,z);
    glutWireSphere(0.1, 15, 15);
    glPopMatrix();
}
void DrawScene(void) {
    DrawAxes();
    DrawSphereAt (0,       0,     0);
    DrawSphereAt (0.5,    0,      0);
    DrawSphereAt (-0.5,   0,      0);
    DrawSphereAt (0,      0.5,    0);
    DrawSphereAt (0,     -0.5,     0);
    DrawSphereAt (0,        0,     -0.5);
    DrawSphereAt (0,       0,      0.5);
}
// display callback
void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    myCamera.ApplyCamera();
    
    DrawScene();
    
    
    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
    switch(c) {
        case 27: exit(0);
        case 'z': zoom *= 1.1; ResetProjection(aspRatio); break;
        case 'Z': zoom *= 0.9; ResetProjection(aspRatio); break;
        case 'w': myCamera.MoveForward(0.1); break;
        case 's': myCamera.MoveForward(-0.1); break;
        case 'a': myCamera.MoveRight(-0.1); break;
        case 'd': myCamera.MoveRight(0.1); break;
        case 'q': myCamera.MoveUp(0.1); break;
        case 'e': myCamera.MoveUp(-0.1); break;
        case 'j': myCamera.RotateHead(0.1); break;
        case 'l': myCamera.RotateHead(-0.1); break;
        case 'i': myCamera.RotatePitch(0.1); break;
        case 'k': myCamera.RotatePitch(-0.1); break;
        case 'u': myCamera.RotateRoll(-0.1); break;
        case 'o': myCamera.RotateRoll(0.1); break;
    }
    
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    
    // glut를 이용한 window 생성 ///////////////////
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100,100);
    glutCreateWindow("아! 나는 그래픽스가 싫어요");
    
    
    init(); // 초기화
    
    // 콜백 함수 등록 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    // keyboard, mouse, idle 등의 콜백 함수도 등록 가능
    glutMainLoop(); // 무한루프
    return 0;
}