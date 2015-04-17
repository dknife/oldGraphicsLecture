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

void LightSet(void) {
    
    GLfloat mat_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
    GLfloat mat_diffuse[] =  { 0.0, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0f, 1.0f, 0.0f };
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


void init(void) {
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.8, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000);
    
    LightSet();
}

void reshape(int w, int h) {
    float asp = float(w)/float(h);
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, asp, 1, 1000);
}


void DrawAxes(void) {
    
    glDisable(GL_LIGHTING);
    
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glColor3f(0,0.5,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glEnd();
    
    glEnable(GL_LIGHTING);
}

void DrawTriangle(void) {
    
    glBegin(GL_TRIANGLES);
    float s = sqrt(3.0);
    glNormal3f(1/s,1/s,1/s);
    glVertex3f(0,0.9,0);
    glNormal3f(-1/s,1/s,1/s);
    glVertex3f(0.9,0,0);
    glNormal3f(1/s,-1/s,-1/s);
    glVertex3f(-0.9,0,0);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    gluLookAt(0,0,2, 0,0,0, 0,1,0);
    
    glLineWidth(4);
    DrawAxes();
    DrawTriangle();
    glutSolidSphere(0.5,20,20);
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Smooth Shading");
    
    init(); // 초기화
    
    // 콜백 함수 등록 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    
    glutMainLoop(); // 무한루프
    return 0;
}