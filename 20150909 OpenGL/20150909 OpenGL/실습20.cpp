#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);


typedef struct sCircle{
	bool draw;
	int xyz;
	int x;
	int y;
	int z;
}sCircle;

sCircle sRealCricel[5];

bool bRectColor[5] = { (false, false, false, false, false) };
int idraw = 0;
float fBingle = 0.0;
float fBingle2 = 0.0;

void vLine();

void vCircle(int);
void vCheck(int);

void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 설정된 색으로 젂체를 칠하기
	glEnable(GL_DEPTH_TEST);


	//-------------------------------------------------------------
	glPushMatrix(); //Save
	//glRotatef(30, 1.0, 0.0, 0.0);
	//glRotatef(45, 0.0, 1.0, 0.0);
	glTranslated(0, 0, 200);
	
	glRotated(fBingle, 0, 0, 1.0);
	glRotated(fBingle2, 1.0, 0, 0);

	//뒤
	glPushMatrix(); //Save
	glBegin(GL_QUADS);
	if (bRectColor[0] == true){
		glColor3f(0.5f, 0.5f, 0.0f); // 노랑
		bRectColor[0] = false;
	}
	else{
		glColor3f(1.0f, 1.0f, 0.0f); // 노랑
	}
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, 100, -100);
	glVertex3f(100, 100, -100);
	glVertex3f(100, -100., -100);
	glEnd();

	//왼쪽
	glBegin(GL_QUADS);
	if (bRectColor[1] == true){
		glColor3f(0.5f, 0.5f, 0.5f); // 흰색
		bRectColor[1] = false;
	}
	else{
		glColor3f(1.0f, 1.0f, 1.0f); // 흰색
	}
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, -100, 100);
	glVertex3f(-100, 100, 100);
	glVertex3f(-100, 100, -100);
	glEnd();

	// 오른쪽
	glBegin(GL_QUADS);
	if (bRectColor[2] == true){
		glColor3f(0.0f, 0.5f, 0.5f); // 하늘
		bRectColor[2] = false;
	}
	else{
		glColor3f(0.0f, 1.0f, 1.0f); // 하늘
	}
	glVertex3f(100, -100, -100);
	glVertex3f(100, -100, 100);
	glVertex3f(100, 100, 100);
	glVertex3f(100, 100, -100);
	glEnd();

	//위
	glBegin(GL_QUADS);
	if (bRectColor[3] == true){
		glColor3f(0.5f, 0.0f, 0.5f); // 보라
		bRectColor[3] = false;
	}
	else{
		glColor3f(1.0f, 0.0f, 1.0f); // 보라
	}
	glVertex3f(-100, 100, -100);
	glVertex3f(-100, 100, 100);
	glVertex3f(100, 100, 100);
	glVertex3f(100, 100, -100);
	glEnd();

	//아래
	glBegin(GL_QUADS);
	if (bRectColor[4] == true){
		glColor3f(0.5f, 0.0f, 0.0f); // 빨강
		bRectColor[4] = false;
	}
	else{
		glColor3f(1.0f, 0.0f, 0.0f); // 빨강
	}
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, -100, 100);
	glVertex3f(100, -100, 100);
	glVertex3f(100, -100, -100);
	glEnd();

	glPushMatrix(); //Save
		glTranslated(sRealCricel[0].x, 0, 0);
		glTranslated(0, sRealCricel[0].y, 0);
		glTranslated(0, 0, sRealCricel[0].z);
		vCircle(0);
		vCheck(0);
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslated(sRealCricel[1].x, 0, 0);
	glTranslated(0, sRealCricel[1].y, 0);
	glTranslated(0, 0, sRealCricel[1].z);
	vCircle(1);
	vCheck(1);
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslated(sRealCricel[2].x, 0, 0);
	glTranslated(0, sRealCricel[2].y, 0);
	glTranslated(0, 0, sRealCricel[2].z);
	vCircle(2);
	vCheck(2);
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslated(sRealCricel[3].x, 0, 0);
	glTranslated(0, sRealCricel[3].y, 0);
	glTranslated(0, 0, sRealCricel[3].z);
	vCircle(3);
	vCheck(3);
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslated(sRealCricel[4].x, 0, 0);
	glTranslated(0, sRealCricel[4].y, 0);
	glTranslated(0, 0, sRealCricel[4].z);
	vCircle(4);
	vCheck(4);
	glPopMatrix();


	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();     // 화면에 출력하기
}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == 'c'){
		fBingle += 1.0;
	}

	if (key == 'v'){
		fBingle2 += 1.0;
	}
	if (key == 'b'){
		sRealCricel[idraw].draw = true;
		sRealCricel[idraw].xyz = 1;
		sRealCricel[idraw].x = 0;
		sRealCricel[idraw].y = 0;
		sRealCricel[idraw].z = 0;
		idraw += 1;

		if (idraw >= 5){
			idraw = 0;
		}

	}

	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){

	}
	if (key == GLUT_KEY_RIGHT){

	}
	if (key == GLUT_KEY_DOWN){

	}
	if (key == GLUT_KEY_UP){

	}
	glutPostRedisplay();
}

int iX[2];

void Mouse(int button, int state, int x, int y){


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		iX[0] = x;
		printf("Left = (%d, %d)\n", x, y);
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		iX[1] = x;
		printf("Left = (%d, %d)\n", x, y);
	}

	if (iX[0] >= iX[1]){
		fBingle += 5.0;
	}
	else{
		fBingle -= 5.0;
	}

}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1500.0);

	gluLookAt(0, 0, 500, 0, 0, -1, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
}

void vLine(){
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -100);
	glVertex3f(0, 0, 100);
	glEnd();
}

void vCircle(int num){

	if (sRealCricel[num].draw == true){
		glColor3f(0.0, 0.0, 0.0);
		glutSolidSphere(3.0, 20, 20);

		if (sRealCricel[num].xyz == 1){
			sRealCricel[num].x += 3;
			printf("(%d, %d, %d)\n", sRealCricel[num].x, sRealCricel[num].y, sRealCricel[num].z);
		}

		if (sRealCricel[num].xyz == 2){
			sRealCricel[num].y += 3;
			sRealCricel[num].x -= 3;
			printf("(%d, %d, %d)\n", sRealCricel[num].x, sRealCricel[num].y, sRealCricel[num].z);
		}

		if (sRealCricel[num].xyz == 3){
			sRealCricel[num].y -= 3;
			sRealCricel[num].x -= 3;
			printf("(%d, %d, %d)\n", sRealCricel[num].x, sRealCricel[num].y, sRealCricel[num].z);
		}

		if (sRealCricel[num].xyz == 4){
			sRealCricel[num].y -= 3;
			sRealCricel[num].x += 3;
			printf("(%d, %d, %d)\n", sRealCricel[num].x, sRealCricel[num].y, sRealCricel[num].z);
		}

		if (sRealCricel[num].xyz == 5){
			sRealCricel[num].y += 3;
			sRealCricel[num].x += 0;
			sRealCricel[num].z -= 3;
			printf("(%d, %d, %d)\n", sRealCricel[num].x, sRealCricel[num].y, sRealCricel[num].z);
		}

		if (sRealCricel[num].xyz == 6){
			sRealCricel[num].y += 0;
			sRealCricel[num].x += 3;
			sRealCricel[num].z += 3;
			printf("(%d, %d, %d)\n", sRealCricel[num].x, sRealCricel[num].y, sRealCricel[num].z);
		}

	}

}

void vCheck(int num){

	if (sRealCricel[num].draw == true){

		if (sRealCricel[num].x >= 98){
			sRealCricel[num].xyz = 2;
			bRectColor[2] = true;
		}

		if (sRealCricel[num].y >= 98){
			sRealCricel[num].xyz = 3;
			bRectColor[3] = true;
		}

		if (sRealCricel[num].x <= -98){
			sRealCricel[num].xyz = 4;
			bRectColor[1] = true;
		}

		if (sRealCricel[num].y <= -98){
			sRealCricel[num].xyz = 5;
			bRectColor[4] = true;
		}

		if (sRealCricel[num].z <= -98){
			sRealCricel[num].xyz = 6;
			bRectColor[0] = true;
		}

	}

}