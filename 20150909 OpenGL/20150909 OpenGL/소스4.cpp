#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void SetupRC();

int Time = 100;

void main()
{
	srand((unsigned)time(NULL));

	//윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //디스플레이 모드 설정
	glutInitWindowPosition(500, 0); // 윈도우 위치 지정
	glutInitWindowSize(800, 600); //윈도우 크기 지정
	glutCreateWindow("CGExample1"); //윈도우 생성(윈도우 이름)

	//상태 변수 초기화 함수
	SetupRC();

	//필요한 콜백 함수 설정
	glutDisplayFunc(DrawScene); //출력 함수의 지정
	//glutTimerFunc(Time, TimerFunction, 1);//타이머 콜백 함수
	glutMouseFunc(Mouse);//마우스입력
	glutKeyboardFunc(Keyboard);//키보드입력
	glutReshapeFunc(Reshape);//다시그리기

	glutMainLoop();//이벤트 루프 실행하기
}

//윈도우 출력 함수
GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//바탕색을'black'로지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기

	//필요한 변환 적용
	//   변환을 적용하기 위해서
	//      glPushMatrix 함수를 호출하여 기존의 좌표 시스템을 저장
	//      필요한 경우 행렬 초기화(glLoadIdentity();)
	//      변환 적용 : 이동, 회전, 신축 등 모델에 적용할 변환 함수를 호출한다.
	//      변환이 끝난 후에는 원래의 좌표시스템을 다시 저장하기 위하여 glPopMatrix 함수 호출



	glPushMatrix();
	glTranslatef(0, 10, 0);
	//glScalef(1.0, 1.0, 1.0);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glutSolidCube(10.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 0, 0);
	//glScalef(1.0, 1.0, 1.0);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glutSolidCube(10.0);
	glPopMatrix();


	glutSwapBuffers(); //화면에 출력하기
}//end of drawScene

GLvoid Reshape(int w, int h)
{
	//뷰포트 변환 설정
	glViewport(0, 0, w, h);

	//투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//클리핑 공간 설정 : 원근투영
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	//모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);

	//관측 변환 : 카메라의 위치 설정
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

}

void Mouse(int button, int state, int x, int y)
{

}//end of Mouse

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':case '2':case '3':case '4':
		break;
	case 27://ESC키로 종료
		exit(0);
		break;
	}
	glutPostRedisplay();
}//end of Keyboard

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(Time, TimerFunction, 1);
}//end of TimerFunction

void SetupRC()//옵션으로 넣을만한 함수, 초기화할 변수가 많으면 쓰는게 좋음
{
	//필요한 변수들, 좌표값 등의 초기화
	//기능 설정 초기화
}