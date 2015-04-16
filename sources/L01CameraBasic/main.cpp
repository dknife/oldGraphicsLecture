#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

int W, H;
float asp=1.0;


void init(void) {
	glClearColor(0.8, 0.9, 0.9, 0.0);
	glEnable(GL_DEPTH_TEST);

	
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
	glViewport(0,0,W/2, H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, asp/2, 1, 1000);
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1,1,3, 0,0,-10, 0,1,0);
	DrawScene();

	// VIEWPORT 2
	glViewport(W/2,0,W/2, H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, asp/2, 1, 1000);
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,10,-3, 0,0,-3, 0,0,-1);
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


	glutMainLoop(); // 무한루프
	return 0;
}

