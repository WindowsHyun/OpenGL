#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include<time.h>
#include<stdlib.h>
GLvoid drawScene(GLvoid);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Reshape(int w, int h);
GLvoid Time(int value);

struct setting
{
	float w; //너비
	float h; //높이
	float dir = 1; //방향
	float trance; //이동

};
setting Box, basket, water, move;

struct position
{
	int x = 0; // x좌표
	int y = 0; // y좌표
};
position mouse, top_mouse, bottom_mouse;

void init();

int count = 0;

void main(int argc, char *argv[])
{
	//초기화 함수들 glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGBA ); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Slice and Take it!"); // 윈도우 생성 (윈도우 이름) 
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(100, Time, 1);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 Black 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기 
	glPushMatrix();


	glPushMatrix();
	glTranslatef(Box.trance, 0, 0); // x축으로 이동
	glBegin(GL_QUADS);
	init(); // Box.w, Box.h 의 초기값 -80 , 70
	glColor3f(1, 1, 0);
	glVertex2f(Box.w, Box.h);            // 위의 박스 모형
	glVertex2f(Box.w, Box.h - 20);
	glVertex2f(Box.w + 30, Box.h - 20);
	glVertex2f(Box.w + 30, Box.h);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(basket.trance, 0, 0); // x축으로 이동

	glBegin(GL_LINE_STRIP);
	init(); // basket.w , basket.h 의 초기값 -80, -50;
	glColor3f(1, 1, 1);
	glVertex2f(basket.w, basket.h);
	glVertex2f(basket.w, basket.h - 30);                  // 바구니
	glVertex2f(basket.w + 40.0, basket.h - 30);
	glVertex2f(basket.w + 40.0, basket.h);
	glEnd();
	glBegin(GL_QUADS);
	init(); // water.w, water.h 의 초기값 -80 , -65
	glColor3f(0, 0, 1);
	glVertex2f(water.w, water.h);            // 물
	glVertex2f(water.w, water.h - 15);
	glVertex2f(water.w + 39.5, water.h - 15);
	glVertex2f(water.w + 39.5, water.h);
	glEnd();

	glPopMatrix();


	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(100, 0);
	glEnd();

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2i(top_mouse.x, top_mouse.y);
	glVertex2i(bottom_mouse.x, bottom_mouse.y);
	glEnd();
	glPopMatrix();

	glPopMatrix();


	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	glutPostRedisplay(); // 화면 재 출력
}

GLvoid Mouse(int button, int state, int x, int y)
{
	//---------------------------------------------------------------------
	// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
	y = 600 - y;
	// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
	if (y >= 0){
		-y;
	}
	//---------------------------------------------------------------------

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d, %d\n", x, y);
		top_mouse.x = x;
		top_mouse.y = y;
	}




	count++;




	glutPostRedisplay(); // 화면 재 출력

}
GLvoid Motion(int x, int y)
{
	//---------------------------------------------------------------------
	// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
	y = 600 - y;
	// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
	if (y >= 0){
		-y;
	}
	//---------------------------------------------------------------------
	printf("%d, %d\n", x, y);
	bottom_mouse.x = x;
	bottom_mouse.y = y;


	glutPostRedisplay();
}

GLvoid Time(int sec)
{
	Box.trance += Box.dir * 1;
	if (Box.trance > 150){
		Box.dir = -1;
	}
	if (Box.trance < -20){
		Box.dir = 1;
	}

	basket.trance += basket.dir * 1;
	if (basket.trance > 140){
		basket.dir = -1;
	}
	if (basket.trance < -20){
		basket.dir = 1;
	}





	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(30, Time, 3);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{


	}
}


void init()
{
	Box.w = -80;
	Box.h = 70;

	basket.w = -80;
	basket.h = -50;

	water.w = -80;
	water.h = -65;

}