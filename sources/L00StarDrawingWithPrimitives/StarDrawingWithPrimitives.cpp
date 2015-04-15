#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-0.50, 0.0, 0.0);
		glVertex3f( 0.00, 0.8660235, 0.0);
		glVertex3f( 0.50, 0.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-0.50, 0.60, 0.0);		
		glVertex3f( 0.50, 0.60, 0.0);
		glVertex3f( 0.00, -0.2660235, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("나의 멋진 오픈지엘 프로그램");

	init(); // 초기화

	// 콜백 함수 등록 
	glutDisplayFunc(display);
	// keyboard, mouse, idle 등의 콜백 함수도 등록 가능


	glutMainLoop(); // 무한루프
	return 0;
}
