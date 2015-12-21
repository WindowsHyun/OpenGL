#include <GL/glut.h>  
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
///////////////////////////
//  콜백 함수 선언  //
///////////////////////////
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);//키보드
GLvoid Mouse(int button, int state, int x, int y);//마우스
//GLvoid Time(int sec);//타이머

//////////////////////////
//  구현 함수 선언 //
//////////////////////////
void line();
void init();
void sin();
void cos();
void spring();
void print();
void rotation();
void move();
void moveSum();
void plusMove();
void minusMove();
void zoomIn();
void zoomOut();
//////////////////////////
//  전역 변수  //
//////////////////////////
GLfloat coordinatePoint[1000][2];//점 정보
GLfloat xPos = 0.0f, yPos = 0.0f;//좌표
GLfloat moveXpos = 0.0f, moveYpos = 0.0f;//각 좌표 이동하는 거리
GLint state = 0;//키보드 상태
GLint scale = 1;//스케일 변화량
GLfloat xposSum = 0, yposSum = 0;//각 좌표 이동거리 총합
/////////////////////////////////////////
//   메인         //
/////////////////////////////////////////
void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);  // 윈도우의 위치지정 
	glutInitWindowSize(800, 800);  // 윈도우의 크기 지정
	glutCreateWindow("Practice12");  // 윈도우 생성 (윈도우 이름)
	//콜백함수 등록
	glutDisplayFunc(drawScene);  // 출력 함수의 지정 
	glutReshapeFunc(Reshape);

	glutMouseFunc(Mouse);//마우스
	//glutTimerFunc(1000,Time,1);//타이머
	glutKeyboardFunc(Keyboard);//키보드
	glutMainLoop();//GLUT 이벤트 프로세싱 루프 실행
}
//////////////////////////////
//  윈도우 출력 함수  //
//////////////////////////////
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 바탕색을 'Magenta' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT);  // 설정된 색으로 전체를 칠하기

	//함수 호출
	line();
	switch (state)
	{
	case  1://COS
		init();
		cos();
		print();
		break;//end c

	case 2://SIN
		init();
		sin();
		print();
		break;//end i

	case 3://SPRING
		init();
		spring();
		print();
		break;// end p

	case 4://ROTATION
		print();
		break;// end r

	case 5://UP
		move();
		print();
		break;//end l

	case 6://DOWN
		move();
		print();
		break;//end .

	case 7://LEFT
		move();
		print();
		break;//end ,

	case 8://RIGHT
		move();
		print();
		break;//end /
	case 9://SCALE-ZOOM IN
		print();
		break;//end s
	case 10://SCALE-ZOOM OUT
		print();
		break;//end a
	}
	glutSwapBuffers(); // 화면에 출력하기
}

////////////////////////////////////
//  COORDINATE      //
////////////////////////////////////
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-10, 10, -10, 10, -1.0, 1.0);
}

///////////////////////////////////////////////////
//     KEYBOARD      //
///////////////////////////////////////////////////
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'c'://COS
		state = 1;
		drawScene();
		break;//end c

	case'i'://SIN
		state = 2;
		drawScene();
		break;//end i

	case 'p'://SPRING
		state = 3;
		drawScene();
		break;// end p

	case 'r'://ROTATION
		//minusMove();
		rotation();
		//plusMove();
		state = 4;
		drawScene();
		break;//end r

	case 'l'://UP
		moveXpos = 0;
		moveYpos = 0.5;
		state = 5;
		drawScene();
		break;//end l

	case '.'://DOWN
		moveXpos = 0;
		moveYpos = -0.5;
		state = 6;
		drawScene();
		break;//end .

	case ','://LEFT
		moveXpos = -0.5;
		moveYpos = 0;
		state = 7;
		drawScene();
		break;//endl ,

	case '/'://RIGHT
		moveXpos = 0.5;
		moveYpos = 0;
		state = 8;
		drawScene();
		break;//end /

	case 's'://SCALE-ZOOM IN
		state = 9;
		zoomIn();
		drawScene();
		break;//end s
	case 'a'://SCALE-ZOOM OUT
		state = 10;
		zoomOut();
		drawScene();
		break;//end a
	}
}
///////////////////////////////////////////////////
//     MOUSE       //
///////////////////////////////////////////////////
GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}
//////////////////////
//  TIMER  //
//////////////////////
//GLvoid Time(int sec)
//{
// glutPostRedisplay();
// glutTimerFunc(1000,Time,1);
//}
/////////////////////////////////////////////////////////////////////
//       FUNCTION          // 
/////////////////////////////////////////////////////////////////////
////////////
// LINE  //
////////////
void line()
{

	//Y 축
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);//점색
	glPointSize(1.0f);//점의 크기
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, -800.0f, 1.0f);//점의 좌표
	glVertex3f(0.0f, 800.0f, 1.0f);//점의 좌표
	glEnd();

	//X 축
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);//점색
	glPointSize(1.0f);//점의 크기
	glBegin(GL_LINE_STRIP);
	glVertex3f(-800.0f, 0.0f, 1.0f);//점의 좌표
	glVertex3f(800.0f, 0.0f, 1.0f);//점의 좌표
	glEnd();
}
//////////
// INIT //
//////////
void init()
{
	//X, Y 초기화
	xPos = -10.0f;
	yPos = 0.0f;
	//이동량 초기화
	moveXpos = 0.0f;
	moveYpos = 0.0f;
	//스케일 초기화
	scale = 1;
	//그래프 점 정보 초기화
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] = 0.0f;
		coordinatePoint[i][1] = 0.0f;
	}
}
////////////
// SIN   //
////////////
void sin()
{
	for (int i = 0; i<1000; ++i)
	{
		xPos += 0.1;
		yPos = sin(xPos);
		coordinatePoint[i][0] = xPos;
		coordinatePoint[i][1] = yPos;
	}
}
////////////
// COS   //
////////////
void cos()
{
	for (int i = 0; i<1000; ++i)
	{
		xPos += 0.1;
		yPos = cos(xPos);
		coordinatePoint[i][0] = xPos;
		coordinatePoint[i][1] = yPos;
	}
}
////////////////
//   PRINT   //
////////////////
void print()
{
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//점색
	glPointSize(1.0f);//점의 크기
	glBegin(GL_LINE_STRIP);

	for (int i = 0; i<1000; ++i)
		glVertex3f(coordinatePoint[i][0], coordinatePoint[i][1], 1.0f);//점의 좌표


	glEnd();
}
//////////////////
// ROTATION //
//////////////////
void rotation()
{
	float DEGINRAD = 3.14159 / 180;
	float degInRad = 10.0f*DEGINRAD;

	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] = coordinatePoint[i][0] * cos(degInRad) - coordinatePoint[i][1] * sin(degInRad);
		coordinatePoint[i][1] = coordinatePoint[i][0] * sin(degInRad) + coordinatePoint[i][1] * cos(degInRad);
	}
}
//////////////
// SPRING //
//////////////
void spring()
{
	float radius = 1;//반지름

	float DEGINRAD = 3.14159 / 180;
	float degInRad = 0.0f;
	float Nums = 0;//x증가분
	float x_left = 5.0;//중심좌표
	float y_left = 0.0;//중심좌표
	for (int i = 0; i<1000; ++i)
	{
		degInRad = i*DEGINRAD;
		coordinatePoint[i][0] = (cos(degInRad)*radius) + x_left + Nums;
		coordinatePoint[i][1] = (sin(degInRad)*radius) + y_left;
		Nums -= 0.01;
	}
}
//////////////
// MOVE //
//////////////
void move()
{
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] += moveXpos;
		coordinatePoint[i][1] += moveYpos;
	}
	moveSum();
}
//////////////
// MOVESUM //
//////////////
void moveSum()
{
	xposSum += moveXpos;
	yposSum += moveYpos;
}
////////////////
// PLUSMOVE  //
////////////////
void plusMove()
{
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] += xposSum;
		coordinatePoint[i][1] += yposSum;
	}
}
/////////////////
// MINUSMOVE  //
/////////////////
void minusMove()
{
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] -= xposSum;
		coordinatePoint[i][1] -= yposSum;
	}
}
////////////
// SIZE  //
////////////
void size()
{
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] *= scale;
		coordinatePoint[i][1] *= scale;
	}
}
//////////////
//  ZOOMIN  //
//////////////
void zoomIn()
{
	minusMove();
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] *= 1.5f;
		coordinatePoint[i][1] *= 1.5f;
	}
	plusMove();
}
///////////////
//  ZOOMOUT  //
///////////////
void zoomOut()
{
	minusMove();
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] /= 1.5f;
		coordinatePoint[i][1] /= 1.5f;
	}
	plusMove();
}
//////////////
// CIRCLE //
//////////////
/*
void circle()
{
float radius=1;//반지름

float DEGINRAD=3.14159/180;
float x_left = 5.0;//중심좌표
float y_left = 0.0;//중심좌표
glBegin(GL_LINE_STRIP);
for (int i=0; i<1980;i++)
{
float degInRad=i*DEGINRAD;
glVertex2f(cos(degInRad)*radius + x_left, sin(degInRad)*radius + y_left);
}
glEnd();
}
*/