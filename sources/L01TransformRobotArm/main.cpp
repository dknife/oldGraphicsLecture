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

void init(void);
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char c, int x, int y);

float angle=0.0;
float angle2=0.0;
float angle3=0.0;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Open GL Transformation example");
    
    init(); // 초기화
    
    // 콜백 함수 등록
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    // keyboard, mouse, idle 등의 콜백 함수도 등록 가능
    
    glutMainLoop(); // 무한루프
    return 0;
}

void reshape(int w, int h)
{
    float asp = float(w)/float(h); // aspect ratio (종횡비)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    gluPerspective(60, asp, 0.1, 100);
    glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y) {
    switch(c) {
        case ',': angle +=1.0; break;
        case '.': angle -=1.0; break;
        case 'k': angle2 +=1.0; break;
        case 'l': angle2 -=1.0; break;
        case '1': angle3 +=1.0; break;
        case '2': angle3 -=1.0; break;
    }
    glutPostRedisplay();
}
void init(void)
{
    glClearColor(0.0, 0.7, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void DrawBox(float w, float h, float d)
{
    glLineWidth(1);
    glPushMatrix();
    glScalef(w,h,d);
    glutWireCube(1.0);
    glPopMatrix();
}

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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(2,1.3,2, // 눈의 위치
              0,0.5,0, // 바라보는 목표점의 위치
              0,1,0); // 카메라의 up 벡터
    
    
    DrawAxes();
    
    glRotatef(angle, 0,0,1);
    glTranslatef(0,0.5,0);
    DrawBox(0.2,1.0,0.2);
    DrawAxes();
    
    glTranslatef(0,0.5,0);
    glRotatef(angle2, 0,0,1);
    glTranslatef(0,0.35,0);
    DrawBox(0.1,0.7,0.1);
    DrawAxes();
    
    glPushMatrix();
    glTranslatef(0,0.35,0);
    glRotatef(angle3, 0,0,1);
    glTranslatef(0,0.2,0);
    DrawBox(0.05,0.4,0.05);
    DrawAxes();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0.35,0);
    glRotatef(-angle3, 0,0,1);
    glTranslatef(0,0.2,0);
    DrawBox(0.05,0.4,0.05);
    DrawAxes();
    glPopMatrix();
    
    glutSwapBuffers();
}