#include <GL/glut.h> // includes gl.h glu.h
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void SpecialKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void SetupRC();
int draw;

typedef struct _POS{
	float x;
	float y;
	float z;
	float rotate;   //공전
	float revolve;   //공전 궤도 각도
	int size = 0;
}POS;

POS sun;
POS earth[3];
POS moon[3];
void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);              // 윈도우의 위치지정
	glutInitWindowSize(800, 600);                  // 윈도우의 크기 지정
	glutCreateWindow("Example14");                 // 윈도우 생성 (윈도우 이름)
	SetupRC();                              //초기화
	glutDisplayFunc(drawScene);                    // 출력 함수의 지정
	glutReshapeFunc(Reshape);                      // 다시 그리기 함수의 지정
	//glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, Timerfunction, 1);           //타이머 함수 설정
	glutMainLoop();

}

void SetupRC()
{
	sun.x = 0.0f;
	sun.y = 0.0f;
	sun.z = 0.0f;
	earth[0].x = 300.0f;
	earth[0].y = 0.0f;
	earth[0].z = 0.0f;
	earth[1].x = 300 / sqrt(2.0);
	earth[1].y = 300 / sqrt(2.0);
	earth[1].z = 0.0f;
	earth[2].x = 300 / sqrt(2.0);
	earth[2].y = -300 / sqrt(2.0);
	earth[2].z = 0.0f;
}


GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 + 깊이 버퍼 클리어

	glLoadIdentity();

	//glPushMatrix();
	glLineWidth(4.0);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(300, 0, 0);
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 300, 0);
	glEnd();

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 300);
	glEnd();

	glBegin(GL_POINTS);


	glPushMatrix();


	glRotatef(90, 1.0f, 0.0f, 0.0f);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

	/*for (int i = 0; i <= 360; i++){
	float x = 300*cos(i* PI / 180);
	float z = 300*sin(i* PI / 180);
	glVertex3f(sun.x+x, sun.y, sun.z+z);
	}*/

	glutWireTorus(2.0, 300, 20, 360);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glRotatef(60.0f, 1.0f, 1.0f, 0.0f);
	for (int i = 0; i <= 360; i++){
		float x = 300 * cos(i* PI / 180) / sqrt(2.0);
		float y = 300 * cos(i* PI / 180) / sqrt(2.0);
		float z = 300 * sin(i* PI / 180);
		glVertex3f(sun.x + x, sun.y + y, sun.z + z);
	}
	//glRotatef(30.0f, 1.0f, 1.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i <= 360; i++){
		float x = -300 * cos(i* PI / 180) / sqrt(2.0);
		float y = 300 * cos(i* PI / 180) / sqrt(2.0);
		float z = 300 * sin(i* PI / 180);
		glVertex3f(sun.x + x, sun.y + y, sun.z + z);
	}
	glPopMatrix();
	glEnd();

	glPushMatrix();               //태양
	glLineWidth(0.5);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
	glutWireSphere(120.0f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRotatef(earth[0].rotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(earth[0].x, earth[0].y, earth[0].z);
	glutWireSphere(60.0f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glRotatef(earth[1].rotate, -1.0f, 1.0f, 0.0f);
	glTranslatef(earth[1].x, earth[1].y, earth[1].z);
	glutWireSphere(60.0f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRotatef(earth[2].rotate, 1.0f, 1.0f, 0.0f);
	glTranslatef(earth[2].x, earth[2].y, earth[2].z);
	glutWireSphere(60.0f, 30, 30);
	glPopMatrix();

	glPopMatrix();
	//glFlush(); // 화면에 출력하기
	glutSwapBuffers();     //재출력
}

void Reshape(int w, int h) {
	GLfloat nRange = 800.0f;

	//--- 뷰포트 변환 설정
	glViewport(0, 0, w, h);

	// 투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다.
	// 클리핑 공간 설정: 직각 투영인 경우
	//glOrtho (-400, 400.0, -300.0, 300.0, -100.0, 100.0);

	// 클리핑 공간 설정: 원근 투영인 경우
	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	gluLookAt(0.0, 600.0, 600.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timerfunction(int value)
{
	earth[0].rotate += 1.0;
	earth[1].rotate += 2.0;
	earth[2].rotate += 3.0;

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(50, Timerfunction, 1);                                //타이머 함수 재설정
}


void Keyboard(unsigned char key, int x, int y)
{
	//if (key == '1')  //구 
	//   draw = 1;
	//if (key == '2')  //육면체 
	//   draw = 2;


	glutPostRedisplay();
}
