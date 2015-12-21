#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);

void vLine();
void vGround();
void vBox();
void vBox2();
void vBox3();
void vCircle();


float fOneNumX = 0.0;
float fOneNumZ = 0.0;

float fCubeNumX = 0.0;


float fXNum = 0.0;
float fMinPlu = 2.0;
float fZNum = 0.0;


float fMidTurn = 0.0;
float fMidWow = 0.0;

float fHighTurn = 0.0;
float fHighWow = 0.0;


float fXXNum = 0.0;
float fXZNum = 0.0;
float fCXNum = 0.0;
float fCYNum = 0.0;
float fCZNum = 0.0;

typedef struct sRect{
	int x;
	int z;
}sRect;

typedef struct sCircle{
	int x;
	int z;
}sCircle;


sRect sRectReal[4] = { { -100, -220 }, { -100, 50 }, { 100, 50 }, { 100, -220 } };

sCircle sCircleReal[4] = { { -20, -20 }, { -20, 20 }, { 20, 20 }, { 20, -20 } };

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
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotatef(30, 1.0, 0, 0.0);

	glPushMatrix();
	//glTranslatef(0, -200, 0);
	
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(sRectReal[0].x, 0, sRectReal[0].z);
	glVertex3f(sRectReal[3].x, 0, sRectReal[3].z);
	glVertex3f(sRectReal[2].x, 0, sRectReal[2].z);
	glVertex3f(sRectReal[1].x, 0, sRectReal[1].z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(sCircleReal[0].x, 0, sCircleReal[0].z);
	glVertex3f(sCircleReal[3].x, 0, sCircleReal[3].z);
	glVertex3f(sCircleReal[2].x, 0, sCircleReal[2].z);
	glVertex3f(sCircleReal[1].x, 0, sCircleReal[1].z);
	glEnd();
	
	glPopMatrix();

	//-------------------------------------------------------------
	glPushMatrix(); //Save
	vGround();
	glPopMatrix();
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	//vLine();
	glPopMatrix();
	//-------------------------------------------------------------
	glRotated(fZNum, 0, 1.0, 0);
	glTranslatef(0, -200, 0);
	glTranslatef(fXNum, 0, 0);
	
	for (int i = 0; i < 4; ++i){
		printf("Rect = %d. x = %d, z= %d\nCircle = %d. x = %d, z= %d\n", i, sRectReal[i].x, sRectReal[i].z, i ,sCircleReal[i].x, sCircleReal[i].z);
	}
	printf("\n");
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	
	vBox();						// 몸통
	
	glPopMatrix();
	//-------------------------------------------------------------
	glTranslatef(0, 70, 0);
	glRotated(fMidTurn, 0, 1.0, 0);
	glRotated(fMidWow, 1.0, 0.0, 0);
	glTranslatef(0, 50, 0);
	glPushMatrix(); //Save
	vBox2();					// 두번째 몸통
	glPopMatrix();
	//-------------------------------------------------------------
	glTranslatef(0, 50, 0);
	glRotated(fHighTurn, 0, 1.0, 0);
	glRotated(fHighWow, 1.0, 0.0, 0);
	glTranslatef(0, 50, 0);
	glPushMatrix(); //Save
	vBox3();
	glPopMatrix();
	//-------------------------------------------------------------

	glPopMatrix();

	glPushMatrix(); //Save
	glTranslatef(0, -200, 0);
	glPushMatrix(); //Save

	

	glTranslatef(fXXNum, 0, 0);
	glRotated(fCXNum, 0, 0, 1.0);

	glTranslatef(0, 0, fXZNum);
	glRotated(fCZNum, 1.0, 0, 0);


	vCircle();
	glPopMatrix();
	glPopMatrix();


	glFlush(); // 화면에 출력하기

}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	bool bstop = false;

	for (int i = 0; i < 4; ++i){

		if (sRectReal[0].x <= sCircleReal[i].x  && sCircleReal[i].x <= sRectReal[3].x){
			if (sRectReal[0].z <= sCircleReal[i].z && sCircleReal[i].z  <= sRectReal[1].z){
				bstop = true;
			}
		}
		else{
			//bstop = false;
		}


	}

	if (bstop == false){
		fXNum += fMinPlu;

		sRectReal[0].x += fMinPlu;
		sRectReal[1].x += fMinPlu;
		sRectReal[2].x += fMinPlu;
		sRectReal[3].x += fMinPlu;

		if (fXNum == 210.0){
			fMinPlu = -2.0;
		}
		else if (fXNum == -210.0){
			fMinPlu = 2.0;
		}
	}

	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'y'){
		// 몸통이 움직인다.
		fZNum += 1.0;
	}
	else if (key == 'Y'){
		fZNum -= 1.0;
	}

	if (key == 'z'){
		// 중간 몸통이 돈다.
		fMidTurn += 2.0;
	}
	else if (key == 'Z'){
		fMidTurn -= 2.0;
	}

	if (key == 'x'){
		fMidWow += 2.0;
	}
	else if (key == 'X'){
		fMidWow -= 2.0;
	}

	if (key == 'c'){
		fHighTurn += 2.0;
	}
	else if (key == 'C'){
		fHighTurn -= 2.0;
	}

	if (key == 'v'){
		fHighWow += 2.0;
	}
	else if (key == 'V'){
		fHighWow -= 2.0;
	}

	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){
		fCXNum -= 5.0;
		fXXNum -= 5.0;
		fCZNum = 0.0;
		fOneNumX -= 5.0;
		sCircleReal[0].x -= 5;
		sCircleReal[1].x -= 5;
		sCircleReal[2].x -= 5;
		sCircleReal[3].x -= 5;
	}
	if (key == GLUT_KEY_RIGHT){
		fCXNum += 5.0;
		fXXNum += 5.0;
		fCZNum = 0.0;
		fOneNumX += 5.0;
		sCircleReal[0].x += 5;
		sCircleReal[1].x += 5;
		sCircleReal[2].x += 5;
		sCircleReal[3].x += 5;
	}
	if (key == GLUT_KEY_DOWN){
		fCZNum += 5.0;
		fXZNum += 5.0;
		fCXNum = 0.0;
		fOneNumZ += 5.0;
		sCircleReal[0].z += 5;
		sCircleReal[1].z += 5;
		sCircleReal[2].z += 5;
		sCircleReal[3].z += 5;
	}
	if (key == GLUT_KEY_UP){
		fCZNum -= 5.0;
		fXZNum -= 5.0;
		fCXNum = 0.0;
		fOneNumZ -= 5.0;
		sCircleReal[0].z -= 5;
		sCircleReal[1].z -= 5;
		sCircleReal[2].z -= 5;
		sCircleReal[3].z -= 5;
	}



	//printf("fXNum = %f, fZNum = %f\nfCXNum = %f, fCZNum = %f\n\n", fXNum, fZNum, fCXNum, fCZNum);
	//printf("X : %f, Z : %f\n", fOneNumX, fOneNumZ);
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Left = (%d, %d)\n", x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1500.0);

	//glTranslatef(0, 0, -500);
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

void vGround(){
	glTranslatef(0, -120, 100);
	glScaled(4.4, 0.0, 3.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
}


sRect sRectReal[4] = { { -100, -220 }, { -100, 50 }, { 100, 50 }, { 100, -220 } };

void vBox(){
	glColor3f(1.0, 0.0, 0.0);
	glScaled(2.0, 1.5, 1.0);
	//glutSolidCube(100);
	glutWireCube(100);
	//printf("%f   ", fXNum );
	//154.000
}

void vBox2(){
	glScaled(1.0, 2.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	//glutSolidCube(50);
	glutWireCube(50);
}

void vBox3(){
	glScaled(1.0, 4.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	//glutSolidCube(50);
	glutWireCube(25);
	// 변의 길이가 25
}

void vCircle(){
	glColor3f(1.0, 0.0, 1.0);
	glutWireSphere(30, 20, 10);
	// 반지름 30
}