#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

void init(void) {
	glClearColor(0.8, 0.4, 0.5, 0.0);
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

void DrawAxes(void) {
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glColor3f(0,1,0);
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

	glLineWidth(3);
	DrawAxes();

	glTranslatef(0.0,0.2,0.0);
	glRotatef(45, 1,1,1);		
	glLineWidth(2);
	DrawAxes();

	
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Transformation Project");

	init(); // 초기화

	// 콜백 함수 등록 
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);


	glutMainLoop(); // 무한루프
	return 0;
}
