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
void vPyramid();
void vLightCircle();
void vLight1();
void vLight2();
void vLight3();


void vAttackCheck();
void vinit();
void vDrawParticle();

float fMapZ = 0.0;
float vMapX = 0.0;
float vMapY = 0.0;
float fView = 0.0;

int iUpDown = 0;
bool bWhatUpDown = true;

float fAmbient = 0.1;
float fAmbient2 = 0.1;
float fAmbient3 = 0.1;

float DiffuseLight1 = 0.8;
float DiffuseLight2 = 0.8;
float DiffuseLight3 = 0.8;

float fDiffuse = 0.1;
float fSpecular = 0.1;
bool bLight1 = false;


bool bSpread = false;
int itimer = 0;
int iCarDown = -190;
int iMoveX = 0;
int iTotalMove = 0;
int iWhatPM = 1;
bool bTurnOn = false;

float fCircleX = 0.0;
float fCircleY = 0.0;
float fCircleZ = 100.0;

bool binit = false;


bool bLeft = false;
bool bRight = false;
bool bTop = false;
bool bBottom = false;

bool bplusminus = true;

bool bturnoff = false;

typedef struct Rect{
	float x[4];
	float z[4];
}Rect;

typedef struct Particle{
	float x = 0;
	float y = 0;
	float z = 0;
	int postion = 0;
	float color[3];

	Particle(){
		for (int i = 0; i < 3; ++i){
			color[i] = rand() % 10 / 10.0;
		}
	}
}Particle;

bool bParticleOnOff = false;

Particle tParticle[30];

GLfloat lightpos[] = { -400, 200, -500, 1 };
GLfloat lightpos2[] = { 400, 200, -500, 1 };

GLfloat lightpos3[] = { fCircleX, fCircleY, fCircleZ, 1 };

GLfloat AmbientLight[] = { fAmbient, fAmbient2, fAmbient3, 1.0f };
GLfloat DiffuseLight[] = { DiffuseLight1, DiffuseLight2, DiffuseLight3, 1.0f };
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };

Rect RedRect;
Rect PinkRect;
Rect BlueRect;
Rect YellowRect;

Rect GreenLeftRect;
Rect GreenRightRect;

Rect Circle;

float fUpDown[4] = { 50.0, -50.0, 50.0, 100.0 };


GLfloat ctrlpoints[3][3][3] = { { { -250.0, 0.0, 150.0 }, { -167.0, fUpDown[0], 150.0 }, { -84.0, 0.0, 150.0 } },
{ { -250.0, 0.0, 0.0 }, { -167.0, fUpDown[0], 0 }, { -84.0, 0, 0 } },
{ { -250.0, 0.0, -150.0 }, { -167.0, fUpDown[0], -150.0 }, { -84.0, 0, -150.0 } } };

GLfloat ctrlpoints2[3][3][3] = { { { -84, 0.0, 150.0 }, { -1.0, fUpDown[1], 150.0 }, { 82.0, 0.0, 150.0 } },
{ { -84.0, 0.0, 0.0 }, { -1.0, fUpDown[1], 0 }, { 82.0, 0, 0 } },
{ { -84.0, 0.0, -150.0 }, { -1.0, fUpDown[1], -150.0 }, { 82.0, 0, -150.0 } } };

GLfloat ctrlpoints3[3][3][3] = { { { 82, 0.0, 150.0 }, { 166.0, fUpDown[2], 150.0 }, { 250.0, 0.0, 150.0 } },
{ { 82.0, 0.0, 0.0 }, { 166.0, fUpDown[2], 0 }, { 250.0, 0, 0 } },
{ { 82.0, 0.0, -150.0 }, { 166.0, fUpDown[2], -150.0 }, { 250.0, 0, -150.0 } } };


GLfloat ctrlpoints4[3][3][3] = { { { -50, 0.0, 50.0 }, { 0, 0, fUpDown[3] }, { 50, 0.0, 50 } },
{ { -50.0, -150.0, 50.0 }, { 0, -150, fUpDown[3] }, { 50, -150, 50 } },
{ { -50.0, -200.0, 50.0 }, { 0, -200, fUpDown[3] }, { 50, -200, 50 } } };


void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(500, TimerFunction, 1);
	glutTimerFunc(100, TimerFunction, 2);
	glutTimerFunc(100, TimerFunction, 3);
	glutTimerFunc(100, TimerFunction, 4);
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
	glEnable(GL_LIGHTING);      // 조명 활성화
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	if (bturnoff == false){
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
	else{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		vLight3();
	}
	if (binit == false){
		binit = true;
		vinit();
	}
	//-------------------------------------
	//조명
	glPushMatrix(); //Save
	glTranslatef(-400, 200, -500);
	vLightCircle();
	vLight1();
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslatef(400, 200, -500);
	vLightCircle();
	vLight2();
	glPopMatrix();
	//-------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(vMapX, 1.0, 0, 0);
	glRotated(vMapY, 0, 1.0, 0);
	gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);
	//-------------------------------------
	// 좌표계
	glPushMatrix(); //Save
	vLine();
	glPopMatrix();
	//-------------------------------------
	// 땅
	glPushMatrix(); //Save
	//vGround();
	glPopMatrix();
	//-------------------------------------
	// 왼쪽 뒤
	glPushMatrix(); //Save
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(-175, -150, -100);
	glScaled(1.0, 2.0, 1.0);
	glutSolidCube(50);
	glPopMatrix();
	//-------------------------------------
	// 왼쪽 중간
	glPushMatrix(); //Save
	glColor3f(1.0, 0.0, 1.0);
	glTranslatef(-175, -130, 0);
	glScaled(1.0, 3.0, 1.0);
	glutSolidCube(50);
	glPopMatrix();
	//-------------------------------------
	// 왼쪽 앞
	glPushMatrix(); //Save
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-125, -180, 125);
	glScaled(3.0, 1.0, 1.0);
	glutSolidCube(50);
	glPopMatrix();
	//-------------------------------------
	// 피라미드
	glPushMatrix(); //Save
	glTranslatef(0, -210, 0);
	//vPyramid();
	glPopMatrix();
	//-------------------------------------
	// 오른쪽 뒤
	glPushMatrix(); //Save
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(155, -160, -100);
	glutSolidCube(100);
	glPopMatrix();
	//-------------------------------------
	// 탑
	glPushMatrix(); //Save
	glColor3f(0.5, 1.0, 0.0);
	glTranslatef(175, -150, 25);
	glScaled(1.0, 3.0, 1.0);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix(); //Save
	glColor3f(0.5, 1.0, 0.0);
	glTranslatef(175, -150, 120);
	glScaled(1.0, 3.0, 1.0);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix(); //Save
	glColor3f(0.5, 1.0, 0.0);
	glTranslatef(175, -100, 80);
	glScaled(1.0, 1.0, 2.5);
	glutSolidCube(50);
	glPopMatrix();
	//-------------------------------------
	glPushMatrix(); //Save
	glColor3f(0.5, 1.0, 1.0);
	glTranslatef(0, -187, 0);

	if (bParticleOnOff == false){
		glPushMatrix(); //Save
		glTranslatef(fCircleX, fCircleY, fCircleZ);
		lightpos3[0] = fCircleX;
		lightpos3[1] = fCircleY;
		lightpos3[2] = fCircleZ;
		glutSolidSphere(20, 20, 10);
		glPushMatrix(); //Save
		glTranslatef(0, 90, 0);
		vLightCircle();
		glPopMatrix();
		glPopMatrix();
	}
	else{
		vDrawParticle();
	}


	glPopMatrix();

	glPushMatrix(); //Save
	glTranslatef(0, -100, 0);

	glPushMatrix(); //Save
	glTranslatef(-50, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.5, 1.0, 1.0);
	glVertex3f(0, 100, 50);
	glVertex3f(0, 100, -50);
	glVertex3f(0, -100, -50);
	glVertex3f(0, -100, 50);
	glEnd();
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslatef(50, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.5, 1.0, 1.0);
	glVertex3f(0, 100, 50);
	glVertex3f(0, 100, -50);
	glVertex3f(0, -100, -50);
	glVertex3f(0, -100, 50);
	glEnd();
	glPopMatrix();

	glPushMatrix(); //Save
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0, 100, 0);
	glBegin(GL_QUADS);
	glColor3f(0.5, 1.0, 1.0);
	glVertex3f(-50, 0, -50);
	glVertex3f(-50, 0, 50);
	glVertex3f(50, 0, 50);
	glVertex3f(50, 0, -50);
	glEnd();
	glPopMatrix();

	glPushMatrix(); //Save
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0, -100, 0);
	glBegin(GL_QUADS);
	glColor3f(0.5, 1.0, 1.0);
	glVertex3f(-50, 0, -50);
	glVertex3f(-50, 0, 50);
	glVertex3f(50, 0, 50);
	glVertex3f(50, 0, -50);
	glEnd();
	glPopMatrix();
	glPopMatrix();


	//------------------------
	// 상자 구현
	glPushMatrix(); //Save
	glTranslatef(0, 0, 0);
	//------------------------
	// 원
	glBegin(GL_QUADS);
	glColor3f(0.5, 1.0, 1.0);
	for (int i = 0; i < 4; ++i){
		glVertex3f(Circle.x[i], 0, Circle.z[i]);
	}

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 4; ++i){
		glVertex3f(RedRect.x[i], 0, RedRect.z[i]);
	}
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	for (int i = 0; i < 4; ++i){
		glVertex3f(PinkRect.x[i], 0, PinkRect.z[i]);
	}
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < 4; ++i){
		glVertex3f(BlueRect.x[i], 0, BlueRect.z[i]);
	}
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < 4; ++i){
		glVertex3f(YellowRect.x[i], 0, YellowRect.z[i]);
	}
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5, 1.0, 0.0);
	for (int i = 0; i < 4; ++i){
		glVertex3f(GreenLeftRect.x[i], 0, GreenLeftRect.z[i]);
	}
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5, 1.0, 0.0);
	for (int i = 0; i < 4; ++i){
		glVertex3f(GreenRightRect.x[i], 0, GreenRightRect.z[i]);
	}
	glEnd();
	//------------------------
	glPopMatrix();
	//------------------------
	//----------------------------------------------------------------------
	glPushMatrix(); //Save
	glTranslatef(0, -210, 0);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);

	glPointSize(2.0); glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlpoints[i][j]);
	glEnd();
	glPopMatrix();
	//----------------------------------------------------------------------
	glPushMatrix(); //Save
	glTranslatef(0, -210, 0);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints2[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);

	glPointSize(2.0); glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlpoints2[i][j]);
	glEnd();
	glPopMatrix();
	//----------------------------------------------------------------------
	glPushMatrix(); //Save
	glTranslatef(0, -210, 0);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints3[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);

	glPointSize(2.0); glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlpoints2[i][j]);
	glEnd();
	glPopMatrix();
	//----------------------------------------------------------------------
	//----------------------------------------------------------------------
	glPushMatrix(); //Save
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints4[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);

	glPointSize(2.0); glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlpoints4[i][j]);
	glEnd();
	glPopMatrix();
	//----------------------------------------------------------------------
	//----------------------------------------------------------------------
	glPushMatrix(); //Save
	glTranslated(0, 0, -100);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints4[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	// 그리드를 이용한 곡면 드로잉
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);

	glPointSize(2.0); glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			glVertex3fv(ctrlpoints4[i][j]);
	glEnd();
	glPopMatrix();
	//----------------------------------------------------------------------

	glPopMatrix();


	//glFlush(); // 화면에 출력하기
	glutSwapBuffers();     // 화면에 출력하기
}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력

	switch (value){
	case 1:

		//glutTimerFunc(500, TimerFunction, 1); // 타이머함수 재 설정
		break;

	case 2:
		if (Circle.x[0] >= 151.0 && Circle.z[0] >= 50.0 && Circle.z[0] <= 55.0){
			DiffuseLight1 = 1.0;
			DiffuseLight2 = 0.0;
			DiffuseLight3 = 0.0;

			DiffuseLight[0] = DiffuseLight1;
			DiffuseLight[1] = DiffuseLight2;
			DiffuseLight[2] = DiffuseLight3;
		}
		else{
			DiffuseLight1 = 1.0;
			DiffuseLight2 = 1.0;
			DiffuseLight3 = 1.0;

			DiffuseLight[0] = DiffuseLight1;
			DiffuseLight[1] = DiffuseLight2;
			DiffuseLight[2] = DiffuseLight3;
		}
		glutTimerFunc(100, TimerFunction, 2); // 타이머함수 재 설정
		break;

	case 3:
		if (bParticleOnOff == true){

			for (int i = 0; i < 30; ++i){
				if (bSpread == false){
					tParticle[i].x = fCircleX;
					tParticle[i].y = fCircleY;
					tParticle[i].z = fCircleZ;
					tParticle[i].postion = rand() % 9;
				}
			}

			/*for (int i = 0; i < 30; ++i){
			printf("x : %f, y = %f, z = %f\n", tParticle[i].x, tParticle[i].y, tParticle[i].z);
			printf("postion : %d \n", tParticle[i].postion);
			printf("r : %f, g : %f, b: %f\n", tParticle[i].color[0], tParticle[i].color[1], tParticle[i].color[2]);

			}*/
			itimer += 1;
			bSpread = true;
			if (itimer >= 10){
				itimer = 0;
				bParticleOnOff = false;
				bSpread = false;
			}
		}
		glutTimerFunc(100, TimerFunction, 3); // 타이머함수 재 설정
		break;

	case 4:
		if (bSpread == true){
			for (int i = 0; i < 30; ++i){
				int irand = rand() % 6;


				if (irand == 0){
					tParticle[i].x += rand() % 10;
					tParticle[i].y += rand() % 10;
					tParticle[i].z += rand() % 10;
				}
				else if (irand == 1){
					tParticle[i].x -= rand() % 10;
					tParticle[i].y -= rand() % 10;
					tParticle[i].z -= rand() % 10;
				}
				else if (irand == 2){
					tParticle[i].x -= rand() % 10;
					tParticle[i].y += rand() % 10;
					tParticle[i].z -= rand() % 10;
				}
				else if (irand == 3){
					tParticle[i].x -= rand() % 10;
					tParticle[i].y -= rand() % 10;
					tParticle[i].z += rand() % 10;
				}
				else if (irand == 4){
					tParticle[i].x += rand() % 10;
					tParticle[i].y -= rand() % 10;
					tParticle[i].z -= rand() % 10;
				}
				else if (irand == 5){
					tParticle[i].x += rand() % 10;
					tParticle[i].y += rand() % 10;
					tParticle[i].z -= rand() % 10;
				}

			}
		}
		glutTimerFunc(100, TimerFunction, 4); // 타이머함수 재 설정
		break;

	}




}

void Keyboard(unsigned char key, int x, int y){
	//printf("InPut Key = %c\n", key);
	if (key == '+'){
		fView += 3.0;
	}
	else if (key == '-'){
		fView -= 3.0;
	}
	if (key == 'r'){
		vMapY += 3.0;
	}

	if (key == '3'){
		if (bturnoff == false){
			bturnoff = true;
		}
		else{
			bturnoff = false;
		}
	}

	if (key == '4'){
		bParticleOnOff = true;
	}

	if (key == 'c'){
		if (fUpDown[0] >= 50){
			fUpDown[0] = -50;
			for (int i = 0; i < 3; ++i){
				ctrlpoints[i][1][1] = fUpDown[0];
			}
		}
		else{
			fUpDown[0] = +50;
			for (int i = 0; i < 3; ++i){
				ctrlpoints[i][1][1] = fUpDown[0];
			}
		}

		if (fUpDown[1] <= -50){
			fUpDown[1] = 50;
			for (int i = 0; i < 3; ++i){
				ctrlpoints2[i][1][1] = fUpDown[1];
			}
		}
		else{
			fUpDown[1] = -50;
			for (int i = 0; i < 3; ++i){
				ctrlpoints2[i][1][1] = fUpDown[1];
			}
		}

		if (fUpDown[2] >= 50){
			fUpDown[2] = -50;
			for (int i = 0; i < 3; ++i){
				ctrlpoints3[i][1][1] = fUpDown[2];
			}
		}
		else{
			fUpDown[2] = 50;
			for (int i = 0; i < 3; ++i){
				ctrlpoints3[i][1][1] = fUpDown[2];
			}
		}

		if (fUpDown[3] >= 100){
			fUpDown[3] = -100;
			for (int i = 0; i < 3; ++i){
				ctrlpoints4[i][1][2] = fUpDown[3];
			}
		}
		else{
			fUpDown[3] = 100;
			for (int i = 0; i < 3; ++i){
				ctrlpoints4[i][1][2] = fUpDown[3];
			}
		}

	}

	if (key == 'w' && bTop == false){
		fCircleZ -= 1.0;
		for (int i = 0; i < 4; ++i){
			Circle.z[i] -= 1.0;
		}

	}
	if (key == 's' && bBottom == false){
		fCircleZ += 1.0;
		for (int i = 0; i < 4; ++i){
			Circle.z[i] += 1.0;
		}
	}
	if (key == 'a' && bLeft == false){
		fCircleX -= 1.0;
		for (int i = 0; i < 4; ++i){
			Circle.x[i] -= 1.0;
		}
	}
	if (key == 'd' && bRight == false){
		fCircleX += 1.0;
		for (int i = 0; i < 4; ++i){
			Circle.x[i] += 1.0;
		}
	}
	vAttackCheck();
	//printf("X : %f, Z : %f\n", fCircleX, fCircleZ);

	//fCircleX, fCircleY, fCircleZ
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){
		fMapZ -= 3.0;
	}
	if (key == GLUT_KEY_RIGHT){
		fMapZ += 3.0;
	}
	if (key == GLUT_KEY_DOWN){
		vMapX += 3.0;
	}
	if (key == GLUT_KEY_UP){
		vMapX -= 3.0;
	}
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

	gluLookAt(0, 0, 550, 0, 0, -1, 0, 1, 0);

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
	glTranslatef(0, -210, 0);
	for (int x = -300; x < 300; x += 10){
		for (int z = -300; z < 300; z += 10){
			glBegin(GL_POLYGON);
			glColor3f(0.2, 0.2, 0.2);
			glNormal3f(0, 1, 0);
			glVertex3f(x, 0, z);
			glVertex3f(x, 0, z + 10);
			glVertex3f(x + 10, 0, z + 10);
			glVertex3f(x + 10, 0, z);
			glEnd();
		}
	}
}

void vPyramid(){
	glBegin(GL_TRIANGLES);	//앞
	glColor3f(255, 0, 0);
	glVertex3f(0, 150.0, 0);   //1
	glColor3f(0, 255, 0);
	glVertex3f(20, 0, 30);   //2
	glColor3f(0, 0, 255);
	glVertex3f(-20, 0, 30);   //3
	glEnd();

	glBegin(GL_TRIANGLES);	// 뒤
	glColor3f(255, 0, 0);
	glVertex3f(0, 150.0, 0);   //1
	glColor3f(0, 255, 0);
	glVertex3f(-20, 0, -30);   //2
	glColor3f(0, 0, 255);
	glVertex3f(20, 0, -30);   //3
	glEnd();

	glBegin(GL_TRIANGLES);	//옆
	glColor3f(255, 0, 0);
	glVertex3f(0, 150.0, 0);   //1
	glColor3f(0, 255, 0);
	glVertex3f(20, 0, 30);   //2
	glColor3f(0, 0, 255);
	glVertex3f(20, 0, -30);   //3
	glEnd();

	glBegin(GL_TRIANGLES);	//옆
	glColor3f(255, 0, 0);
	glVertex3f(0, 150.0, 0);   //1
	glColor3f(0, 255, 0);
	glVertex3f(-20, 0, 30);   //3
	glColor3f(0, 0, 255);
	glVertex3f(-20, 0, -30);   //2
	glEnd();
}

void vLight1(){
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
}

void vLight2(){
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
}

void vLight3(){
	float Spot_direction[] = { 0.0, -1.0, 0.0 };
	float Spot_cutoff[] = { 15.0f };
	GLfloat AmbientLight2[] = { 0.2, 0.2, 0.2f, 1.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Spot_direction);
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, Spot_cutoff);
}

void vLightCircle(){
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(5, 20, 10);
}

void vinit(){

	float fCircleX = 0.0;
	float fCircleY = 0.0;
	float fCircleZ = 100.0;

	Circle.x[0] = -20;
	Circle.z[0] = 80;
	Circle.x[1] = -20;
	Circle.z[1] = 120;
	Circle.x[2] = 20;
	Circle.z[2] = 120;
	Circle.x[3] = 20;
	Circle.z[3] = 80;

	RedRect.x[0] = -200;
	RedRect.z[0] = 100;
	RedRect.x[1] = -200;
	RedRect.z[1] = 150;
	RedRect.x[2] = -50;
	RedRect.z[2] = 150;
	RedRect.x[3] = -50;
	RedRect.z[3] = 100;

	PinkRect.x[0] = -200;
	PinkRect.z[0] = -25;
	PinkRect.x[1] = -200;
	PinkRect.z[1] = 25;
	PinkRect.x[2] = -150;
	PinkRect.z[2] = 25;
	PinkRect.x[3] = -150;
	PinkRect.z[3] = -25;

	BlueRect.x[0] = -200;
	BlueRect.z[0] = -125;
	BlueRect.x[1] = -200;
	BlueRect.z[1] = -75;
	BlueRect.x[2] = -150;
	BlueRect.z[2] = -75;
	BlueRect.x[3] = -150;
	BlueRect.z[3] = -125;

	YellowRect.x[0] = 105;
	YellowRect.z[0] = -150;
	YellowRect.x[1] = 105;
	YellowRect.z[1] = -50;
	YellowRect.x[2] = 205;
	YellowRect.z[2] = -50;
	YellowRect.x[3] = 205;
	YellowRect.z[3] = -150;

	GreenLeftRect.x[0] = 150;
	GreenLeftRect.z[0] = 0;
	GreenLeftRect.x[1] = 150;
	GreenLeftRect.z[1] = 50;
	GreenLeftRect.x[2] = 200;
	GreenLeftRect.z[2] = 50;
	GreenLeftRect.x[3] = 200;
	GreenLeftRect.z[3] = 0;

	GreenRightRect.x[0] = 150;
	GreenRightRect.z[0] = 95;
	GreenRightRect.x[1] = 150;
	GreenRightRect.z[1] = 145;
	GreenRightRect.x[2] = 200;
	GreenRightRect.z[2] = 145;
	GreenRightRect.x[3] = 200;
	GreenRightRect.z[3] = 95;
}

void vAttackCheck(){
	//fCircleX, fCircleY, fCircleZ

	bLeft = false;
	bRight = false;
	bTop = false;
	bBottom = false;

	for (int i = 0; i < 4; ++i){
		if (RedRect.x[2] <= Circle.x[0] && Circle.x[1] <= RedRect.x[3]){
			if (RedRect.z[0] <= Circle.z[i] && Circle.z[i] <= RedRect.z[1]){
				// 빨간색 오른쪽 충돌체크
				bLeft = true;
			}
		}

		if (RedRect.x[0] <= Circle.x[1] && Circle.x[2] <= RedRect.x[3]){
			if (RedRect.z[0] <= Circle.z[i] && Circle.z[i] <= RedRect.z[3]){
				// 빨간색 아래
				bBottom = true;
			}
		}


		if (PinkRect.x[2] <= Circle.x[0] && Circle.x[1] <= PinkRect.x[3]){
			if (PinkRect.z[0] <= Circle.z[i] && Circle.z[i] <= PinkRect.z[1]){
				// 핑크 오른쪽
				bLeft = true;
			}
		}

		if (PinkRect.x[1] <= Circle.x[0] && Circle.x[3] <= PinkRect.x[2]){
			if (PinkRect.z[1] <= Circle.z[i] && Circle.z[i] <= PinkRect.z[2]){
				// 핑크 위
				bTop = true;
			}
		}

		if (PinkRect.x[0] <= Circle.x[1] && Circle.x[2] <= PinkRect.x[3]){
			if (PinkRect.z[0] <= Circle.z[i] && Circle.z[i] <= PinkRect.z[3]){
				// 핑크 아래
				bBottom = true;
			}
		}


		if (BlueRect.x[2] <= Circle.x[0] && Circle.x[1] <= BlueRect.x[3]){
			if (BlueRect.z[0] <= Circle.z[i] && Circle.z[i] <= BlueRect.z[1]){
				// 파란색 오른쪽
				bLeft = true;
			}
		}

		if (BlueRect.x[1] <= Circle.x[0] && Circle.x[3] <= BlueRect.x[2]){
			if (BlueRect.z[1] <= Circle.z[i] && Circle.z[i] <= BlueRect.z[2]){
				// 파란색 위
				bTop = true;
			}
		}

		if (BlueRect.x[0] <= Circle.x[1] && Circle.x[2] <= BlueRect.x[3]){
			if (BlueRect.z[0] <= Circle.z[i] && Circle.z[i] <= BlueRect.z[3]){
				// 파란색 아래
				bBottom = true;
			}
		}

		if (YellowRect.x[0] <= Circle.x[2] && Circle.x[3] <= YellowRect.x[1]){
			if (YellowRect.z[0] <= Circle.z[i] && Circle.z[i] <= YellowRect.z[1]){
				// 노랑 오른쪽
				bRight = true;
			}
		}

		if (YellowRect.x[1] <= Circle.x[0] && Circle.x[3] <= YellowRect.x[2]){
			if (YellowRect.z[1] <= Circle.z[i] && Circle.z[i] <= YellowRect.z[2]){
				// 파란색 위
				bTop = true;
			}
		}


		if (GreenLeftRect.x[0] <= Circle.x[2] && Circle.x[3] <= GreenLeftRect.x[1]){
			if (GreenLeftRect.z[0] <= Circle.z[i] && Circle.z[i] <= GreenLeftRect.z[1]){
				// 초록 제일 아래 오른쪽
				bRight = true;
			}
		}

		if (GreenLeftRect.x[0] <= Circle.x[1] && Circle.x[2] <= GreenLeftRect.x[3]){
			if (GreenLeftRect.z[0] <= Circle.z[i] && Circle.z[i] <= GreenLeftRect.z[3]){
				// 초록 제일 아래 아래
				bBottom = true;
			}
		}

		if (GreenLeftRect.x[1] <= Circle.x[0] && Circle.x[3] <= GreenLeftRect.x[2]){
			if (GreenLeftRect.z[1] <= Circle.z[i] && Circle.z[i] <= GreenLeftRect.z[2]){
				// 초록 제일 아래 위
				bTop = true;
			}
		}


		if (GreenRightRect.x[0] <= Circle.x[2] && Circle.x[3] <= GreenRightRect.x[1]){
			if (GreenRightRect.z[0] <= Circle.z[i] && Circle.z[i] <= GreenRightRect.z[1]){
				// 초록 제일 위 오른쪽
				bRight = true;
			}
		}

		if (GreenRightRect.x[0] <= Circle.x[1] && Circle.x[2] <= GreenRightRect.x[3]){
			if (GreenRightRect.z[0] <= Circle.z[i] && Circle.z[i] <= GreenRightRect.z[3]){
				// 초록 제일 아래 아래
				bBottom = true;
			}
		}
	}
}


void vDrawParticle(){
	for (int i = 0; i < 30; ++i){
		glPushMatrix();
		glTranslatef(tParticle[i].x, tParticle[i].y, tParticle[i].z);
		glColor3f(tParticle[i].color[0], tParticle[i].color[1], tParticle[i].color[2]);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
}