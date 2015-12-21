#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void isUDLR();
void isDrawRect(int, int, int, int);
void isDrawCircle(int, int, int);

#define isRealRect 3

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct  isClick{
	int isX, isY;
	bool isReady = false;
}isClick;

typedef struct isReDot{
	bool  isStart = false;
	int isX = 0, isY = 0;
	int isPlusSize = 0;
	int isUDLR = 0; // 4방향 체크
}isReDot;

isClick isClickRect;
isReDot isRectData[isRealRect];

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
	srand((unsigned)time(NULL) + GetTickCount());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기

	for (int i = 0; i < isRealRect; ++i){
		if (isRectData[i].isStart == false){
			int isX = rand() % 700, isY = rand() % 500;
			isRectData[i].isPlusSize = rand() % 100 + 10;
			isRectData[i].isX = isX, isRectData[i].isY = isY;
			isRectData[i].isStart = true;
		}
		isDrawRect(isRectData[i].isX, isRectData[i].isY, isRectData[i].isX + isRectData[i].isPlusSize, isRectData[i].isY + isRectData[i].isPlusSize);
	}
	/*
	점을 이용하여 언티앨리어싱 하여 동그랗게 만들기
	*/
	glPointSize(20.0);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POINTS);
	glColor3f(255, 0, 0); // 그리기 색을 'Red' 으로 지정
	glVertex2i(isClickRect.isX, isClickRect.isY);
	glEnd();
	
	//isDrawCircle(isClickRect.isX, isClickRect.isY, 10);


	glFlush(); // 화면에 출력하기
}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력

	if (isClickRect.isX != 0 && isClickRect.isY != 0){
		isUDLR();
	}

	glutTimerFunc(10, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
}

void Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//---------------------------------------------------------------------
		// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
		y = isRect.right - y;
		// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
		if (y >= 0){
			-(y);
		}
		//---------------------------------------------------------------------
		isClickRect.isReady = true;
		isClickRect.isX = x, isClickRect.isY = y;
		printf("Left = (%d, %d)\n", x, y);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		isClickRect.isReady = false;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		for (int i = 0; i < isRealRect; ++i){
			int isX = rand() % 700, isY = rand() % 500;
			isRectData[i].isPlusSize = rand() % 100 + 10;
			isRectData[i].isX = isX, isRectData[i].isY = isY;
			isRectData[i].isStart = true;
		}
		printf("Right = (%d, %d)\n", x, y);
	}
}

void isUDLR(){
	for (int i = 0; i < isRealRect; ++i){
		if (isRectData[i].isX > isClickRect.isX){
			isRectData[i].isX -= 1;
			printf("%d. (%d, %d) : X-=1\n", i, isRectData[i].isX, isRectData[i].isY);
		}
		if (isRectData[i].isY > isClickRect.isY){
			isRectData[i].isY -= 1;
			printf("%d. (%d, %d) : Y-=1\n", i, isRectData[i].isX, isRectData[i].isY);
		}
		if (isRectData[i].isX < isClickRect.isX){
			isRectData[i].isX += 1;
			printf("%d. (%d, %d) : X+=1\n", i, isRectData[i].isX, isRectData[i].isY);
		}
		if (isRectData[i].isY < isClickRect.isY){
			isRectData[i].isY += 1;
			printf("%d. (%d, %d) : Y+=1\n", i, isRectData[i].isX, isRectData[i].isY);
		}
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 800, isRect.left = 0, isRect.right = 600;
}

void isDrawRect(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glColor3f(1.0f, 1.0f, 1.0f); // 그리기 색을 'White' 으로 지정
	glRecti(isX, isY, isX2, isY2); // 사각형 그리기 (x1, y1, x2, y2)
	//---------------------------------------------------------------------
}

void isDrawCircle(int isMX, int isMY, int isSize){
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f); // 그리기 색을 'Red' 으로 지정
	for (int i = 0; i < 360; ++i){
		int isX = isSize * cos(i*(3.14 / 180)), isY = isSize * sin(i*(3.14 / 180));
		isX += isMX;
		isY += isMY;
		glVertex3f(isX, isY, 0);
	}
	glEnd();
}

