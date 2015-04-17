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

int W, H;
float asp=1.0;
float aspScale = 1.0;
float fovy = 45;

#define NUMBALLS 100
float pos[NUMBALLS][3];

void init(void) {
    glClearColor(0.8, 0.9, 0.9, 0.0);
    glEnable(GL_DEPTH_TEST);
    
    for(int i=0; i<= NUMBALLS; i++) {
        pos[i][0] = float(rand()%1000)/999.0;
        pos[i][1] = float(rand()%1000)/999.0;
        pos[i][2] = float(rand()%1000)/999.0;
    }
    
    
}

void keyboard(unsigned char k, int x, int y) {
    switch(k) {
        case 'q': case 'Q': case 27: exit(0);
        case 'w': case 'W': fovy *= 1.1; break;
        case 's': case 'S': fovy *= 0.9; break;
        case 'a': case 'A': aspScale *= 1.1; break;
        case 'd': case 'D': aspScale *= 0.9; break;
    }
    glutPostRedisplay();
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
    
    for(int i=0;i<NUMBALLS;i++) {
        glColor3f(float(i%3)/6.0, 0.5-float(i%5)/10.0, float (i%2)/4.0);
        glPushMatrix();
        glTranslatef(pos[i][0], pos[i][1], pos[i][2]);
        glutWireSphere(0.05,20,20);
        glPopMatrix();
    }
}


void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // VIEWPORT 1
    glViewport(0,0,W/2, H/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, asp, 1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2,2,2, 0,0,0, 0,1,0);
    DrawScene();
    
    // VIEWPORT 2
    glViewport(0,H/2,W/2, H/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.1*asp,1.1*asp,-0.1,1.1, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    DrawScene();
    
    // VIEWPORT 3
    glViewport(W/2,H/2,W/2, H/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, asp, 1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.5, 0.5, 2, 0.5,0.5,0, 0,1,0);
    DrawScene();
    
    // VIEWPORT 4
    glViewport(W/2,0,W/2, H/2);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, asp*aspScale, 1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2,2,2, 0,0,0, 0,1,0);
    DrawScene();
    
    glutSwapBuffers();
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
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    
    glutMainLoop(); // 무한루프
    return 0;
}
