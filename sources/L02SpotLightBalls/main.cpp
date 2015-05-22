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
#include <math.h>

float angle = 0.0;
bool bAnimation = true;
bool bPointLight = true;

// 재질에 설정될 값
GLfloat mat_specular[] = {1.0, 1.0f, 1.0f, 1.0f };
GLfloat mat_diffuse[] =  { 1.0, 1.0f, 0.0f, 1.0f };
GLfloat mat_ambient[] =  { 0.1, 0.1f, 0.1f, 1.0f };
GLfloat mat_shininess[] = { 120.0 };

// 광원에 설정될 값
GLfloat lit_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_diffuse[] =  { 1.0, 0.4f, 0.4f, 1.0f };
GLfloat lit_ambient[] =  { 1.0, 1.0f, 1.0f, 1.0f };

GLfloat light_position[] = { 0.0, 0.0f, 1.0f, 1.0f };

void LightSet(void) {
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lit_ambient);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void LightPositioning(bool bPointLight) {
    light_position[3] = (bPointLight)?1.0:0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}


void init(void) {
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.0,0.0,0.0,1.0);
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

void keyboard(unsigned char c, int x, int y) {
    switch(c) {
        case 'a':
        case 'A': bAnimation = 1-bAnimation; break;
        case 'p':
        case 'P': bPointLight = 1-bPointLight; break;
    }
}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    float od = 10.0; // observation distance
    gluLookAt(od*cos(angle),0, od*sin(angle), 0,0,0, 0,1,0);
    if(bAnimation) angle += 0.01;
    
    LightPositioning(bPointLight);
    
    glLineWidth(4);
    DrawAxes();
    
    for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
            float x = -5.0+i;
            float y = -5.0+j;
            glPushMatrix();
            glTranslatef(x,y,0.0);
            glutSolidSphere(0.5,50,50);
            glPopMatrix();
        }
    }
    
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
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    
    
    glutMainLoop(); // 무한루프
    return 0;
}