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

float angle=0.0;
void init(void) {
	glClearColor(0.8, 0.9, 0.9, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}

void reshape(int w, int h) {    
	float asp = float(w)/float(h);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2*asp,2*asp, -2, 2, -2, 2);
}

void idle(void) {
	angle += 1;
	glutPostRedisplay();
}
void DrawAxes(void) {
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
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glLineWidth(4);
	DrawAxes();


	glLineWidth(2);
	glPushMatrix();
	// 이동된 원점에 고정되어 회전하는 좌표축	
	glTranslatef(0.0,0.2,0.0);	
	glRotatef(angle, 1,1,1);		
	DrawAxes();
	glPopMatrix();


	glPushMatrix();
	// 이동하면서 회전하는 좌표축
	glRotatef(angle, 1,1,1);		
	glTranslatef(0.0,0.5,0.0);	
	float sVal = sin(angle*3.14/180);
	glScalef(sVal, sVal, sVal);
	DrawAxes();
	glLineWidth(1);
	glColor3f(0,0,0);
	glutWireSphere(0.5, 10,10);
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("트랜스포머 프로젝트!");

	init(); // 초기화

	// 콜백 함수 등록 
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);


	glutMainLoop(); // 무한루프
	return 0;
}