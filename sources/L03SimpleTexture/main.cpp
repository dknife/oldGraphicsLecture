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

#include <stdio.h>


#define TEXSIZE 16
GLubyte myTex[TEXSIZE][TEXSIZE][3];


void CreateTexture(void) {
    for(int i=0;i<TEXSIZE;i++) {
        for(int j=0;j<TEXSIZE;j++) {
            for(int k=0;k<3;k++) {
                int c = TEXSIZE>>1;
                float d = sqrt(double((c-i)*(c-i)+(c-j)*(c-j)));
                myTex[i][j][k] =
                (d>c)?(GLubyte) (255*float(rand()%1000)/999.0): 0;
            }
        }
    }
}



void init(void) {
    
    glClearColor(0.8, 0.9, 0.9, 0.0);
    
    glEnable(GL_DEPTH_TEST);
    ///////////////////////////
    CreateTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 TEXSIZE, TEXSIZE, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, &myTex[0][0][0]);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
    
}

void reshape(int w, int h) {
    float asp = float(w)/float(h);
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1*asp,1*asp, -0.5, 1.5, 0, 2);
}



void DrawTriangle(void) {
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glBegin(GL_TRIANGLES);
    glTexCoord2f(1,2);
    glVertex3f(-0.5,1,0);
    
    glTexCoord2f(2,0);
    glVertex3f(0,0,0);
    
    glTexCoord2f(0,0);
    glVertex3f(-1,0,0);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    gluLookAt(0,0,1, 0,0,0, 0,1,0);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(0,0,0);
    glTexCoord2f(0,1);
    glVertex3f(0,1,0);
    glTexCoord2f(1,1);
    glVertex3f(1,1,0);
    glTexCoord2f(1,0);
    glVertex3f(1,0,0);
    glEnd();
    DrawTriangle();
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
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