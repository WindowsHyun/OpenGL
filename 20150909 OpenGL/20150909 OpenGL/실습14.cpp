#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

float fXNum = 0.0;
float fYNum = 0.0;
float fZNum = 0.0;
float fSNum = 0.0;

float fMainNum = 0.0;
float fOneNum = 0.0;
float fTwoNum = 0.0;
float fThrNum = 0.0;

int iTwoNum = 90;
int iThrNum = 90;

bool bSolidWire = true;

void vSphereM(int, int, int, bool);
void vTorusM(int, int, int, int, bool);

void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
	//-------------------------------------------------------------
	//전체 회전
	glPushMatrix(); //Save
	glRotatef(fXNum, 1.0, 0.0, 0.0);
	glRotatef(fYNum, 0.0, 1.0, 0.0);
	glRotatef(fZNum, 0.0, 0.0, 1.0);
	glTranslated(0, 0, fSNum);
	//-------------------------------------------------------------
	//중심 회전
	glPushMatrix(); //Save
	glRotated(90, 1.0, 0, 0);
	glRotated(fMainNum, 0, 0, 1.0);
	glTranslated(0, 0, fSNum);
	glColor3f(1.0, 0.0, 0.0);
	vSphereM(50, 50, 10, bSolidWire);
	glPopMatrix(); //Load
	//-------------------------------------------------------------
	glPushMatrix();
	glRotated(90, 1.0, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	vTorusM(2, 200, 5, 30, bSolidWire);
	//-------------------------------------------------------------
	glRotated(fOneNum, 0, 0, 1.0);
	glTranslated(200, 0, 0);
	vSphereM(30, 30, 30, bSolidWire);
	//-------------------------------------------------------------
	glColor3f(0.0, 0.0, 1.0);
	vTorusM(2, 50, 5, 30, bSolidWire);
	//-------------------------------------------------------------
	glRotated(fOneNum, 0, 0, 1.0);
	glTranslated(50, 0, 0);
	vSphereM(10, 10, 10, bSolidWire);
	glPopMatrix();
	//-------------------------------------------------------------


	//-------------------------------------------------------------
	glPushMatrix();
	glRotated(iTwoNum, 1.0, 1.0, 0);
	glColor3f(0.0, 1.0, 1.0);
	vTorusM(2, 200, 5, 30, bSolidWire);
	//-------------------------------------------------------------
	glRotated(fTwoNum, 0, 0, 1.0);
	glTranslated(200, 0, 0);
	vSphereM(30, 30, 30, bSolidWire);
	//-------------------------------------------------------------
	glColor3f(0.0, 0.0, 1.0);
	vTorusM(2, 50, 5, 30, bSolidWire);
	//-------------------------------------------------------------
	glRotated(fTwoNum, 0, 0, 1.0);
	glTranslated(50, 0, 0);
	vSphereM(10, 10, 10, bSolidWire);
	glPopMatrix();
	//-------------------------------------------------------------


	//-------------------------------------------------------------
	glPushMatrix();
	glRotated(iThrNum, 1.0, -1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	vTorusM(2, 200, 5, 30, bSolidWire);
	//-------------------------------------------------------------
	glRotated(fThrNum, 0, 0, 1.0);
	glTranslated(200, 0, 0);
	vSphereM(30, 30, 30, bSolidWire);
	//-------------------------------------------------------------
	glColor3f(0.0, 0.0, 1.0);
	vTorusM(2, 50, 5, 30, bSolidWire);
	//-------------------------------------------------------------
	glRotated(fThrNum, 0, 0, 1.0);
	glTranslated(50, 0, 0);
	vSphereM(10, 10, 10, bSolidWire);
	glPopMatrix();
	//-------------------------------------------------------------

	glPopMatrix(); //Load

	glFlush(); // 화면에 출력하기

}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	fMainNum += 5.0;
	fOneNum += 5.0;
	fTwoNum += 3.0;
	fThrNum += 1.0;
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'x')
		fXNum += 5.0;
	if (key == 'X')
		fXNum -= 5.0;

	if (key == 'y')
		fYNum += 5.0;
	if (key == 'Y')
		fYNum -= 5.0;

	if (key == 'z')
		fZNum += 5.0;
	if (key == 'Z')
		fZNum -= 5.0;

	if (key == '1')
		iTwoNum += 10;

	if (key == '2')
		iThrNum += 10;

	if (key == 'c')
		bSolidWire = true;

	if (key == 'C')
		bSolidWire = false;

	/*
	if (key == 's' )
	fSNum += 1.0;
	if (key == 'S')
	fSNum -= 1.0;
	*/
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Left = (%d, %d)\n", x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1500.0);

	glTranslatef(0, 0, -500);

	glMatrixMode(GL_MODELVIEW);
}

void vSphereM(int a, int b, int c, bool d){
	if (d == true)
		glutWireSphere(a, b, c);		//가운데 중심 원
	else
		glutSolidSphere(a, b, c);		//가운데 중심 원
}

void vTorusM(int a, int b, int c, int d, bool e){
	if (e == true)
		glutWireTorus(a, b, c, d);		//2번째 안에 고리
	else
		glutSolidTorus(a, b, c, d);		//2번째 안에 고리
}