#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define isRectNum   (20)

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void TimerFunction(int);
void Keyboard(unsigned char, int, int);
void isDrawRect(int, int, int, int);
void isChangeRect();
void isChangeRGB();
void isUDLR();
void isUDLRChange();

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct isReDot{
	bool  isStart = false;
	int isX[2], isY[2];
	int isUDLR = 0; // 4방향 체크
}isReDot;

int isRealNum = 0;
int isTimerSpeed = 100;
isReDot isData[isRectNum];
int isRGB[3] = { 255, 255, 255 };


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

	for (int i = 0; i < isRectNum; ++i){
		if (isData[i].isStart == true){
			isDrawRect(isData[i].isX[0], isData[i].isY[0], isData[i].isX[1], isData[i].isY[1]);
		}
	}

	glFlush(); // 화면에 출력하기

}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	isUDLR();
	isChangeRGB();
	glutTimerFunc(isTimerSpeed, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	if (key == 'U' || key == 'u'){
		isTimerSpeed -= 10;
		printf("Speed UP..!\n");
	}
	else 	if (key == 'D' || key == 'd'){
		isTimerSpeed += 10;
		printf("Speed Down..!\n");
	}
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
		if (isRealNum >= isRectNum){			// 임시로 한개만 움직이게 설정
			isRealNum = 0;
		}
		isData[isRealNum].isX[0] = x, isData[isRealNum].isY[0] = y;
		isData[isRealNum].isX[1] = x + 40, isData[isRealNum].isY[1] = y + 20;
		isData[isRealNum].isStart = true;
		isData[isRealNum].isUDLR = rand() % 4;
		isRealNum += 1;
		printf("Left Click = %d. (%d, %d)\n", isRealNum, x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		isChangeRect();
		printf("Right = (%d, %d)\n", x, y);
	}
}

void isUDLR(){
	for (int i = 0; i < isRectNum; ++i){
		if (isData[i].isStart == true){
			if (isData[i].isUDLR == 0){
				isData[i].isY[0] += 10;
				isData[i].isY[1] += 10;
				isData[i].isX[0] += 10;
				isData[i].isX[1] += 10;
				printf("%d.Right UP +=10\n", i);
				printf("%d.(%d, %d, %d, %d)\n", i, isData[i].isX[0], isData[i].isY[0], isData[i].isX[1], isData[i].isY[1]);
			}
			else if (isData[i].isUDLR == 1){
				isData[i].isY[0] += 10;
				isData[i].isY[1] += 10;
				isData[i].isX[0] -= 10;
				isData[i].isX[1] -= 10;
				printf("%d.Left UP +=10\n", i);
				printf("%d.(%d, %d, %d, %d)\n", i, isData[i].isX[0], isData[i].isY[0], isData[i].isX[1], isData[i].isY[1]);
			}
			else if (isData[i].isUDLR == 2){
				isData[i].isY[0] -= 10;
				isData[i].isY[1] -= 10;
				isData[i].isX[0] -= 10;
				isData[i].isX[1] -= 10;
				printf("%d.Left Down +=10\n", i);
				printf("%d.(%d, %d, %d, %d)\n", i, isData[i].isX[0], isData[i].isY[0], isData[i].isX[1], isData[i].isY[1]);
			}
			else if (isData[i].isUDLR == 3){
				isData[i].isY[0] -= 10;
				isData[i].isY[1] -= 10;
				isData[i].isX[0] += 10;
				isData[i].isX[1] += 10;
				printf("%d.Right Down +=10\n", i);
				printf("%d.(%d, %d, %d, %d)\n", i, isData[i].isX[0], isData[i].isY[0], isData[i].isX[1], isData[i].isY[1]);
			}
		}
	}
	isUDLRChange();
}

void isUDLRChange(){
	for (int i = 0; i < isRectNum; ++i){
		if (isData[i].isStart == true){
			srand((unsigned)time(NULL) + GetTickCount());
			if (isData[i].isY[1] <= 600 && isData[i].isX[1] >= 800){
				if (rand() % 2 == 0){
					isData[i].isUDLR = 1;
				}
				else{
					isData[i].isUDLR = 2;
				}
				printf("%d.Change\n", i);
			}

			if (isData[i].isY[1] >= 600 && isData[i].isX[1] <= 800){
				// 2번 또는 3번이 가능함
				if (rand() % 2 == 0){
					isData[i].isUDLR = 2;
				}
				else{
					isData[i].isUDLR = 3;
				}
				printf("%d.Change\n", i);
			}

			if (isData[i].isY[0] <= 600 && isData[i].isX[0] <= 0){
				if (rand() % 2 == 0){
					isData[i].isUDLR = 0;
				}
				else{
					isData[i].isUDLR = 3;
				}
				printf("%d.Change\n", i);
			}

			if (isData[i].isY[0] <= 0 && isData[i].isX[0] <= 800){
				if (rand() % 2 == 0){
					isData[i].isUDLR = 0;
				}
				else{
					isData[i].isUDLR = 1;
				}
				printf("%d.Change\n", i);
			}

		}
	}
}

void isDrawRect(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glColor3f(isRGB[0], isRGB[1], isRGB[2]); // 그리기 색을 'green' 으로 지정
	glRecti(isX, isY, isX2, isY2); // 사각형 그리기 (x1, y1, x2, y2)
	//---------------------------------------------------------------------
}

void isChangeRect(){
	int isTemp[2];
	for (int i = 0; i < isRectNum; ++i){
		if (isData[i].isStart == true){

			isTemp[0] = isData[i].isX[0];
			isTemp[1] = isData[i].isY[0];

			isData[i].isX[0] = isData[i].isY[1];
			isData[i].isY[0] = isData[i].isX[1];

			isData[i].isY[1] = isTemp[0];
			isData[i].isX[1] = isTemp[1];
		}
	}
	printf("isChangeRect()\n");
}

void isChangeRGB(){
	srand((unsigned)time(NULL) + GetTickCount());
	//---------------------------------------------------------------------
	// RGB 색상을 클릭할때마다 랜덤으로 수정.
	if (rand() % 3 == 0){
		isRGB[0] = 255, isRGB[1] = 0, isRGB[2] = 0;
	}
	else if (rand() % 3 == 1){
		isRGB[0] = 0, isRGB[1] = 255, isRGB[2] = 0;
	}
	else if (rand() % 3 == 2){
		isRGB[0] = 0, isRGB[1] = 0, isRGB[2] = 255;
	}
	//---------------------------------------------------------------------
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 800, isRect.left = 0, isRect.right = 600;
}