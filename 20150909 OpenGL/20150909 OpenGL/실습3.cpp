#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct isRect{
	int top, bottom, right, left;
}isRect;

void isDataRand();
void isDrawTriangles(int, int, int, int);
void isDrawRect(int, int, int, int);
void isDrawPolygon(int, int, int, int);
void isDrawLines(int, int, int, int);

void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
	/*
	//---------------------------------------------------------------------
	isDrawTriangles(400, 200, 600, 400);
	isDrawTriangles(0, 0, 200, 200);
	//---------------------------------------------------------------------
	isDrawRect(200, 200, 400, 400);
	isDrawRect(0, 400, 200, 600);
	//---------------------------------------------------------------------
	isDrawPolygon(200, 400, 400, 600);
	isDrawPolygon(400, 0, 600, 200);
	//---------------------------------------------------------------------
	isDrawLines(200, 0, 400, 200);
	isDrawLines(400, 400, 600, 600);
	isDrawLines(0, 200, 200, 400);
	//---------------------------------------------------------------------
	*/
	isDataRand();
	glFlush(); // 화면에 출력하기
	
}

void isDrawLines(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glBegin(GL_LINES); // 선
	glColor3f(1.0f, 1.0f, 0.0f); // 그리기 색을 'Yellow' 으로 지정
	glVertex2i(isX + 50, isY + 50);
	glVertex2i(isX2 - 50, isY2 - 50);
	glEnd();
	//---------------------------------------------------------------------
}

void isDrawPolygon(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glBegin(GL_POLYGON); // 오각형
	glColor3f(0.0f, 100, 100); // 그리기 색을 'Blue' 으로 지정
	glVertex2i(isX + 20, (isY + isY2) / 2 + 15);
	glColor3f(0.0f, 100, 150); // 그리기 색을 'Blue' 으로 지정
	glVertex2i(isX + 60, isY + 50);
	glColor3f(0.0f, 0, 200); // 그리기 색을 'Blue' 으로 지정
	glVertex2i(isX2 - 50, isY + 50);
	glColor3f(0.0f, 0, 250); // 그리기 색을 'Blue' 으로 지정
	glVertex2i(isX2 - 50, isY2 - 20);
	glColor3f(0.0f, 0.0f, 255); // 그리기 색을 'Blue' 으로 지정
	glVertex2i(isX + 60, isY2 - 20);
	glEnd();
	//---------------------------------------------------------------------
}

void isDrawTriangles(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glBegin(GL_TRIANGLES); //삼각형
	glColor3f(100, 100, 0.0f); // Red
	glVertex2i(isX + 50, isY + 50); //삼각형의 첫번째 꼭지점의 좌표를 지정한다.
	glColor3f(200, 0.0f, 0.0f); // Red
	glVertex2i((isX + isX2) / 2, isY2 - 20); //삼각형의 두번째 꼭지점의 좌표를 지정한다.
	glColor3f(255, 0.0f, 0.0f); // Red
	glVertex2i(isX2 - 50, isY + 50); //삼각형의 세번째 꼭지점의 좌표를 지정한다.
	glEnd(); //그리기를 종료한다.
	//---------------------------------------------------------------------
}

void isDrawRect(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glColor3f(0, 255, 0.0f); // 그리기 색을 'green' 으로 지정
	glRecti(isX + 50, isY + 50, isX2 - 50, isY2 - 20); // 사각형 그리기 (x1, y1, x2, y2)
	//---------------------------------------------------------------------
}

void isDataRand(){
	int isX = 0, isY = 0;
	int isX2 = 200, isY2 = 200;

	for (int j = 0; j < 3; ++j){
		for (int i = 0; i < 3; ++i){
			srand((unsigned)time(NULL)+isY2*isY+isX2*isX);
			int isRandDraw = rand() % 4;

			if (isRandDraw == 0){
				isDrawTriangles(isX, isY, isX2, isY2);
			}
			else if (isRandDraw == 1){
				isDrawLines(isX, isY, isX2, isY2);
			}
			else  if (isRandDraw == 2){
				isDrawPolygon(isX, isY, isX2, isY2);
			}
			else  if (isRandDraw == 3){
				isDrawRect(isX, isY, isX2, isY2);
			}
			isY2 += 200, isY += 200;
		}
		isX += 200, isX2 += 200, isY2 = 200, isY= 0;
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0, 600.0, 0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 600, isRect.left = 0, isRect.right = 600;
}