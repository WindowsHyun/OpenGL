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

struct isRect{
	int top, bottom, right, left;
}isRect;

GLfloat ctrlpoints[20][3] = {
	{ -40.0, -40.0, 0.0 }, { -20.0, 40.0, 0.0 }, { 20.0, 20.0, 0.0 }, { 40.0, 0.0, 0.0 } };

int index = 0;

typedef struct sMouse{
	int x;
	int y;
}sMouse;

sMouse sMous[20];


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

	for (int i = 0; i < 100; ++i){
		if (ctrlpoints[i * 3][0] != 0){
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[i * 3][0]);

			glEnable(GL_MAP1_VERTEX_3);

			glPointSize(5.0);
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POINTS);
			for (int j = 0; j < 100; j++)
				glVertex3fv(&ctrlpoints[j][0]);
			glEnd();

			glMapGrid1f(100.0, 0, 1.0);	       // 매개변수 0~1 사이를 100개로 나눔
			glEvalMesh1(GL_LINE, 0, 100);   // 선분으로 나눈 부분 0~100까지 선으로 그림
		}
	}


	glFlush(); // 화면에 출력하기

}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력

	glutTimerFunc(5, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	printf("%f, %f, %f", ctrlpoints[0][0], ctrlpoints[0][1], ctrlpoints[0][2]);
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

		ctrlpoints[index][0] = x;
		ctrlpoints[index][1] = y;
		sMous[index].x = x;
		sMous[index].y = y;
		index++;
		//index
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
