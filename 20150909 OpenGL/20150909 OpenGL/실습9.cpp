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
void isC();

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

isClick isClickRect;
isCircle isTC[216];
int isSize = 0;
int isDraw = 0;

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
	for (int i = 0; i < isDraw; ++i){
		isDrawCircle(isTC[i].isSX, isTC[i].isSY, 7);
	}
	glFlush(); // 화면에 출력하기

}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력

	if (isDraw >= 216){
		//isDraw = 0;
	}
	else{
		isDraw++;
	}
	glutTimerFunc(5, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
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
		isClickRect.isX = x, isClickRect.isY = y;
		isC();
		isDraw = 0;
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

void isDrawCircle(int isMX, int isMY, int isSize){
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f); // 그리기 색을 'Red' 으로 지정
	for (int i = 0; i < 360; ++i){
		int isX = isSize * cos(i*(3.141592 / 180)), isY = isSize * sin(i*(3.141592 / 180));

		isX += isMX;
		isY += isMY;

		glVertex3f(isX, isY, 0);
	}
	glEnd();
}

void isC(){
	isSize = 0;
	int isRkreh = 0;
	for (int i = 0; i < 108; ++i){

		isTC[i].isSX = isSize * cos(i*(3.141592 / 18));
		isTC[i].isSX += isClickRect.isX;

		isTC[i].isSY = isSize * sin(i*(3.141592 / 18));
		isTC[i].isSY += isClickRect.isY;
		isRkreh += 10;
		isSize++;
		printf("%d, %d = (%d, %d)\n", isRkreh, isSize, isTC[i].isSX, isTC[i].isSY);
	}


	printf("--------------------------\n");

	int temp = (isTC[107].isSX - isTC[0].isSX) * 2;

	isClickRect.isX = isTC[0].isSX + temp;
	isClickRect.isY = isTC[107].isSY;


	for (int i = 108; i < 216; ++i){
		isTC[i].isSX = isSize * sin(i*(3.141592 / 14.3));
		isTC[i].isSX += isClickRect.isX;

		isTC[i].isSY = isSize * cos(i*(3.141592 / 14.3));
		isTC[i].isSY += isClickRect.isY;
		isRkreh -= 10;
		isSize--;
		printf("%d, %d = (%d, %d)\n", isRkreh, isSize, isTC[i].isSX, isTC[i].isSY);

	}
}