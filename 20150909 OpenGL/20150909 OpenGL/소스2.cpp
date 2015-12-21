#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void init(void);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

static int mx, my, px[10], py[10];
static float g_fAngle = 0;
static bool leftCheck = false;
int pts[10][100][2]; // pts[]개체수 []총알한계 []x ,y값
int num_pts = 40; //총알수
int clickCount = 0; //클릭카운터
float fullladian[10]; //퍼지는값

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//초기화 함수들 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example4"); // 윈도우 생성 (윈도우 이름)
	init();

	glutTimerFunc(100, TimerFunction, 1);
	//glutSpecialFunc(SKeyboard);
	glutMouseFunc(Mouse); //마우스
	glutDisplayFunc(drawScene); // 출력 함수의 지정

	glutReshapeFunc(Reshape); glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	float radius = 2.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기 

	//  clear all pixels
	for (int z = 0; z < 10; z++)
	{
		if (leftCheck)
			for (int i = 0; i < num_pts; i++)
			{
				pts[z][i][0] = px[z] + cos((i + 1)*(360 / 40.f)) * fullladian[z];
				pts[z][i][1] = py[z] + sin((i + 1)*(360 / 40.f)) * fullladian[z];
			}

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1.0f, 0.0f, 0.0f);
		for (int i = 0; i < num_pts; i++)
		{
			glPushMatrix();//행렬
			glTranslatef(pts[z][i][0], pts[z][i][1], 0.0f); //이동
			glBegin(GL_POLYGON);  //다각형(원)
			for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f)
			{
				glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);
			}
			glEnd();
			glPopMatrix();
		}
	}
	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, 800.0f, 600.0f, 0, -1.0, 1.0);
}


void init(void)
{
	for (int i = 0; i < 10; i++)
	{
		px[i] = -300;
		py[i] = -300;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		leftCheck = true;

		clickCount++;
		if (clickCount >= 10)
			clickCount = 0;

		px[clickCount] = x;
		py[clickCount] = y;
		fullladian[clickCount] = 10;
	}
}


void TimerFunction(int value)
{
	for (int i = 0; i < 10; i++)
		fullladian[i] += 5;
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}