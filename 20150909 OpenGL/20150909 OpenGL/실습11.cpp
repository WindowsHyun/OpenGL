#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void isDrawline();
void isDrawCircle();
void isDrawTriangles();

float isX = 0.0, isX2 = 0.5, isY = 8.0, isY2=1.0;
float isWhat = 0.0;

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct isCircleData{
	float isDataX, isDataY;
}isCircleData;

isCircleData isDataCircle[360];
isCircleData isDataTriangles[3];


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


	isDrawline();
	isDrawCircle();
	
	glPushMatrix();// 행렬을 저장한다.
	glRotatef(isWhat, 0.0f, 0.0f, 1.0);
	isDrawTriangles();
	glPopMatrix();// 행렬을 불러온다.

	glFlush(); // 화면에 출력하기

}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	isWhat += 1.5;
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == 'u' || key == 'U'){
		isY2 += 0.1;
		isX2 += 0.1;
		isY += 0.1;
	}
	else if (key == 'd' || key == 'D'){
		isY2 -= 0.1;
		isX2 -= 0.1;
		isY -= 0.1;
	}
	else if (key == 'r' || key == 'R'){
		isX = isX * cos(3.141592 / 180) - isY * sin(3.141592 / 180);
		isY = isX * sin(3.141592 / 180) + isY * cos(3.141592 / 180);
	}
	else if (key == 'z' || key == 'Z'){

	}
	printf("(%f, %f) (%f, %f)\n", isX, isY, isX2, isY2);
}

void Mouse(int button, int state, int x, int y){
	//---------------------------------------------------------------------
	// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
	y = isRect.right - y;
	// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
	if (y >= 0){
		-(y);
	}
	//---------------------------------------------------------------------
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Left = (%d, %d)\n", x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(-10, 10, -10, 10, -1.0, 1.0);
	isRect.bottom = -10, isRect.top = 10, isRect.left = -10, isRect.right = 10;
}


void isDrawline(){
	//Y 축
	glBegin(GL_LINE_STRIP); // 선
	glPointSize(1.0f);//점의 크기
	glColor3f(1.0f, 1.0f, 0.0f); // 그리기 색을 'Yellow' 으로 지정
	glVertex3f(0.0f, -10, 1.0f);//점의 좌표
	glVertex3f(0.0f, 10, 1.0f);//점의 좌표
	glEnd();
	//X 축
	glBegin(GL_LINE_STRIP); // 선
	glPointSize(1.0f);//점의 크기
	glColor3f(1.0f, 1.0f, 0.0f); // 그리기 색을 'Yellow' 으로 지정
	glVertex3f(-10.0f, 0.0f, 1.0f);//점의 좌표
	glVertex3f(10.0f, 0.0f, 1.0f);//점의 좌표
	glEnd();
}

void isDrawCircle(){
	float isSize = 7.0;
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f); // 그리기 색을 'Red' 으로 지정
	for (int i = 0; i < 360; ++i){
		float isX = isSize * cos(i*(3.141592 / 180)), isY = isSize * sin(i*(3.141592 / 180));

		isX += 0.0;
		isY += 0.0;

		isDataCircle[i].isDataX = isX;
		isDataCircle[i].isDataY = isY;

		glVertex3f(isX, isY, 0);
	}
	glEnd();

}


void isDrawTriangles(){
	//---------------------------------------------------------------------
	glBegin(GL_TRIANGLES); //삼각형
	glColor3f(1.0f, 1.0f, 1.0f); // 그리기 색을 'White' 으로 지정
	glVertex2f(isX, isY); //삼각형의 첫번째 꼭지점의 좌표를 지정한다.
	glVertex2f(isX-isX2, isY-isY2); //삼각형의 두번째 꼭지점의 좌표를 지정한다.
	glVertex2f(isX+isX2, isY-isY2); //삼각형의 세번째 꼭지점의 좌표를 지정한다.
	glEnd(); //그리기를 종료한다.
	//---------------------------------------------------------------------
}
