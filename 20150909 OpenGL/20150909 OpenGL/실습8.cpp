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

void isDrawCircle(int, int, int);
void isTCircle(int, int, int);


void isInputData(int, int, int);
void isSpreadCircle();

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct  isClick{
	int isX = -300, isY = -300;
	bool isReady = false;
}isClick;

typedef struct  isCircle{
	int isX, isY;
	int isSX, isSY;
	bool isWrite = false;
}isCircle;

#define isLimitClick 10
#define isLimitOne 360

isClick isClickRect[isLimitClick];
int isClickNum = 0;
isCircle isTC[isLimitClick][isLimitOne];

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

	for (int j = 0; j < isLimitClick; ++j){

		if (isClickRect[j].isX >= 0){		// -300 기본값으로 했으니  0보다 작으면 하지말자
			isDrawCircle(isClickRect[j].isX, isClickRect[j].isY, 1);
			for (int i = 0; i < isLimitOne; ++i){
				isTCircle(isTC[j][i].isSX, isTC[j][i].isSY, 3);
			}
		}


	}

	glFlush(); // 화면에 출력하기

}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	isSpreadCircle();
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == 'u'){

	}
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
		isClickRect[isClickNum].isReady = true;
		isClickRect[isClickNum].isX = x, isClickRect[isClickNum].isY = y;

		printf("%d| %d, %d\n", isClickNum, isClickRect[isClickNum].isX, isClickRect[isClickNum].isY);

		isInputData(x, y, 7);

		printf("Left = (%d, %d)\n", x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 800, isRect.left = 0, isRect.right = 600;
}


void isInputData(int isMx, int isMy, int isSize){

	for (int i = 0; i < isLimitOne; ++i){
		isTC[isClickNum][i].isX = isMx, isTC[isClickNum][i].isY = isMy;
		isTC[isClickNum][i].isWrite = true;

		if (isTC[isClickNum][i].isWrite == true){
			int isX = isSize * cos(i*(3.14159 / 180)), isY = isSize * sin(i*(3.14159 / 180));

			isX += isMx;
			isY += isMy;

			isTC[isClickNum][i].isSX = isX, isTC[isClickNum][i].isSY = isY;
			isTC[isClickNum][i].isWrite = false;
		}
	}
	isClickNum += 1;

	if (isClickNum >= isLimitClick){
		isClickNum = 0;
	}

}

void isDrawCircle(int isMX, int isMY, int isSize){
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f); // 그리기 색을 'Red' 으로 지정
	for (int i = 0; i < isLimitOne; ++i){
		int isX = isSize * cos(i*(3.141592 / 180)), isY = isSize * sin(i*(3.141592 / 180));

		isX += isMX;
		isY += isMY;

		glVertex3f(isX, isY, 0);
	}
	glEnd();
}

void isTCircle(int isMX, int isMY, int isSize){
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f); // 그리기 색을 'White' 으로 지정
	for (int i = 0; i < isLimitOne; ++i){

		int isX = isSize * cos(i*(3.141592 / 180)), isY = isSize * sin(i*(3.141592 / 180));
		isX += isMX;
		isY += isMY;

		glVertex3f(isX, isY, 0);
	}
	glEnd();
}

int isCCC = 3;
void isSpreadCircle(){

	for (int j = 0; j < isLimitClick; ++j){
		for (int i = 0; i < isLimitOne; ++i){
			int isN = isClickRect[j].isX - isTC[j][i].isSX;
			int isNd = isClickRect[j].isY - isTC[j][i].isSY;

			//printf("%d. (%d, %d) <= (%d, %d) : %d, %d\n", i, isTC[i].isSX, isTC[i].isSY, isClickRect.isX, isClickRect.isY, isN, isNd);
			

			isTC[j][i].isSX += -(isCCC * cos(i*(3.141592 / 180)));
			isTC[j][i].isSY += -(isCCC * sin(i*(3.141592 / 180)));

		}
	}
	++isCCC;
}