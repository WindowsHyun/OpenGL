#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h> // 비트맵 파일 관련 자료 저장

enum{ Draw_Mode, View_Mode };

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void MouseMotion(int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void vMenuFunc(int value);
void TimerFunction(int);
void init();

struct sViewPort{
	int top, bottom, right, left;
}sViewPort;

typedef struct sBuilding{
	int ScaleX = 1.0, ScaleY = 1.0, ScaleZ = 1.0;
	int MoveX, MoveY, MoveZ;
	int PlusMinus_x;
	int PlusMinus_z;
	float color[3];

}sBuilding;

typedef struct sMoveData{
	float moveX[101];
	float moveY[101];
	float moveZ[101];
}sMoveData;

typedef struct Weather{
	float dropSpeed;
	int x, y, z;

	Weather(){
		x = rand() % 1000 - 500;
		z = rand() % 1000 - 500;
		y = rand() % 600;
		dropSpeed = rand() % 20 + 1;
	}
}Weather;

#define LimitBuilding 20
sBuilding tBuilding[LimitBuilding];
#define LimitPoint 22
GLfloat ctrlpoints[LimitPoint][3];
#define LimitData 9
sMoveData tMoveData[LimitData];
#define LimitWeather 100
Weather tWeather[LimitWeather];

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint texture_object[5];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);


void vLeftViewPort();
void vRightViewPort();
void vDrawCurve();
void vDrawCurveDot(float);
void vDrawBuilding();
void vDraw3DBuilding();
void vDrawGround();
void vLine();
void vDrawLines(int, int, int, int);
void vDrawWeather();

void vCalcMove();

float fMapZ = 0.0;
float vMapX = 0.0;
float vMapY = 0.0;
float fView = 0.0;
float angle = 0;

int iMoveNum = 0;
int iDirNum = 0;

int iMemoryX, iMemoryY, iNowCount;
bool bMove = false;

float viewport1_x, viewport1_y;
float viewport2_x, viewport2_y;

int iMmenu, iSmenu, imode;

int count = 0;
int What_Mode = Draw_Mode;

void bresenhamAlg(int, int, int, int, int);
void putPixel(int, int, int);


struct sBar{
	int i = 0;
	int x[102];
	int y[102];
}sBar;
int sBarX = 0, sBarY = 0;

struct sBar2{
	int i = 0;
	int x[52];
	int y[52];
	int j = 0;
	int x2[52];
	int y2[52];
	int k = 0;
	int x3[72];
	int y3[72];
}sBar2;
int sBarX2 = 0, sBarY2 = 0;
int sBarX3 = 0, sBarY3 = 0;
int sBarX4 = 0, sBarY4 = 0;

void init(){
	srand((unsigned)time(NULL));
	for (int i = 0; i < LimitBuilding; ++i){
		tBuilding[i].ScaleX = rand() % 2 + 1;
		tBuilding[i].ScaleY = rand() % 5 + 1;
		tBuilding[i].ScaleZ = rand() % 2 + 1;

		tBuilding[i].MoveX = rand() % 320 + 10;
		tBuilding[i].MoveY = 0;
		tBuilding[i].MoveZ = rand() % 300 + 10;

		tBuilding[i].PlusMinus_x = rand() % 2 + 1;
		tBuilding[i].PlusMinus_z = rand() % 2 + 1;

		for (int j = 0; j < 3; ++j){
			tBuilding[i].color[j] = rand() % 10 / 10.0;
		}
	}

	bresenhamAlg(0, 0, 100, 100, 0);
	sBar.i = 0;
	bresenhamAlg(110, 110, 160, 160, 1);
	sBar2.i = 0;
	bresenhamAlg(110, 160, 160, 110, 2);
	sBar2.j = 0;
	bresenhamAlg(135, 100, 135, 170, 3);
	sBar2.k = 0;
}

void SetupRC(){
	glGenTextures(7, texture_object);
	// 바닥
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	pBytes = LoadDIBitmap("image/Ground.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 790, 593, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	pBytes = LoadDIBitmap("image/B01.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	pBytes = LoadDIBitmap("image/B02.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	pBytes = LoadDIBitmap("image/B03.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	pBytes = LoadDIBitmap("image/B04.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);

	glEnable(GL_DEPTH_TEST);			 // 은면 제거
	glFrontFace(GL_CCW);					 // 앞면 설정  
	glEnable(GL_CULL_FACE);			 // 내부는 잘라낸다  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 배경색 설정
}

void vMenuFunc(int iBt){

	switch (iBt){
	default:
	case 1:
		imode = 1;
		break;
	case 2:
		imode = 2;
		break;
	case 3:
		imode = 3;
		break;
	}
	glutPostRedisplay();
}


void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutTimerFunc(10, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 0);
	glutTimerFunc(10, TimerFunction, 2);
	glutTimerFunc(10, TimerFunction, 3);
	glutTimerFunc(10, TimerFunction, 4);
	glutTimerFunc(10, TimerFunction, 5);
	glutTimerFunc(10, TimerFunction, 6);

	iSmenu = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("눈", 1);
	glutAddMenuEntry("비", 2);
	glutAddMenuEntry("맑음", 3);
	iMmenu = glutCreateMenu(vMenuFunc);
	glutAddSubMenu("날씨", iSmenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	init();
	SetupRC();
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 설정된 색으로 전체를 칠하기 + 깊이 버퍼 클리어
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (What_Mode == Draw_Mode){
		//------------------------------------------------------------------------------------------------------------------------------
		// 왼쪽 뷰포트 설정.
		vLeftViewPort();
		//------------------------------------------------------------------------------------------------------------------------------
		vDrawCurve();
		vDrawCurveDot(5.0);
		vDrawBuilding();
		//------------------------------------------------------------------------------------------------------------------------------
		// 오른쪽 뷰포트 설정.
		vDrawLines(399, 0, 399, sViewPort.top);
		glPushMatrix(); //Save
		vRightViewPort();
		glTranslatef(0, 0, sViewPort.top / 2);
		//------------------------------------------------------------------------------------------------------------------------------
		vDrawCurve();
		vDrawCurveDot(10.0);

		glPopMatrix();
		//------------------------------------------------------------------------------------------------------------------------------
	}
	else if (What_Mode == View_Mode){
		Reshape(sViewPort.right * 2, sViewPort.top);

		glPushMatrix(); //Save
		glRotated(fMapZ, 0, 0, 1.0);
		glRotated(vMapX, 1.0, 0, 0);
		glRotated(vMapY, 0, 1.0, 0);
		gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);

		vLine();

		glPushMatrix(); //Save
		glTranslatef(-210, -210, 0);
		vDrawCurve();

		glPopMatrix();

		vDrawGround();

		vDraw3DBuilding();

		vCalcMove();


		glPushMatrix(); //Save
		glTranslatef(tMoveData[iDirNum].moveX[iMoveNum] - 210, tMoveData[iDirNum].moveY[iMoveNum] - 210, tMoveData[iDirNum].moveZ[iMoveNum]);
		glPushMatrix(); //Save
		glutSolidCube(20);
		glPopMatrix();
		glPopMatrix();
		iMoveNum += 1;

		if (iMoveNum >= 100){
			iMoveNum = 0;
			iDirNum += 1;
			if (iDirNum >= LimitData - 2){
				iDirNum = 0;
				glLoadIdentity();
			}
		}

		glPushMatrix(); //Save
		glTranslatef(0, -210, 0);
		vDrawWeather();
		glPopMatrix();


		glPushMatrix(); //Save
		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(5.0);
		glBegin(GL_LINE_STRIP);
		glVertex2i(0, 0);
		glVertex2i(sBarX, sBarY);
		glEnd();
		glPopMatrix();

		glPushMatrix(); //Save
		if (sBar.i == 100){
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_STRIP);
			glVertex2i(110, 160);
			glVertex2i(sBarX3, sBarY3);
			glEnd();

			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_STRIP);
			glVertex2i(135, 100);
			glVertex2i(sBarX4, sBarY4);
			glEnd();

			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_STRIP);
			glVertex2i(110, 110);
			glVertex2i(sBarX2, sBarY2);
			glEnd();
		}
		glPopMatrix();



		glPopMatrix(); // 마지막 PushPop
	}

	glutSwapBuffers();     // 화면에 출력하기
}

void TimerFunction(int value){
	switch (value){
	case 0:
		if (What_Mode == View_Mode){
			for (int i = 0; i < 100; ++i){
				if (tWeather[i].y < 0)
					tWeather[i].y = rand() % 600;
				else
					tWeather[i].y -= tWeather[i].dropSpeed;
			}
		}
		glutTimerFunc(10, TimerFunction, 0);
		break;

	case 1:
		glutPostRedisplay(); // 화면 재 출력
		glutTimerFunc(10, TimerFunction, 1);
		break;

	case 2:
		if (What_Mode == View_Mode){
			//vMapY += 0.1;
		}
		glutTimerFunc(10, TimerFunction, 2);
		break;

	case 3:
		if (What_Mode == View_Mode){
			sBarX = sBar.x[sBar.i];
			sBarY = sBar.y[sBar.i];
			sBar.i += 1;
			if (sBar.i >= 101){
				sBar.i = 100;
			}
		}
		glutTimerFunc(10, TimerFunction, 3);
		break;

	case 4:
		if (What_Mode == View_Mode){
			if (sBar.i == 100){
				sBarX2 = sBar2.x[sBar2.i];
				sBarY2 = sBar2.y[sBar2.i];
				sBar2.i += 1;
				if (sBar2.i >= 51){
					sBar2.i = 50;
				}
			}
		}
		glutTimerFunc(10, TimerFunction, 4);
		break;

	case 5:
		if (What_Mode == View_Mode){
			if (sBar.i == 100){
				sBarX3 = sBar2.x2[sBar2.j];
				sBarY3 = sBar2.y2[sBar2.j];
				sBar2.j += 1;
				if (sBar2.j >= 51){
					sBar2.j = 50;
				}
			}
		}
		glutTimerFunc(10, TimerFunction, 5);
		break;

	case 6:
		if (What_Mode == View_Mode){
			if (sBar.i == 100){
				sBarX4 = sBar2.x3[sBar2.k];
				sBarY4 = sBar2.y3[sBar2.k];
				sBar2.k += 1;
				if (sBar2.k >= 71){
					sBar2.k = 70;

					sBar.i = 0, sBar2.i = 0;
					sBar2.j = 0, sBar2.k = 0;
					sBarX2 = 0, sBarY2 = 0;
					sBarX3 = 0, sBarY3 = 0;
					sBarX4 = 0, sBarY4 = 0;


				}
			}
		}
		glutTimerFunc(10, TimerFunction, 6);
		break;

	}
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == '+'){
		fView += 3.0;
	}
	else if (key == '-'){
		fView -= 3.0;
	}

	if (key == 'r'){
		vMapY += 3.0;
	}

	if (key == 's'){
		for (int i = 0; i < 101; ++i){
			printf("x : %f, y : %f, z : %f\n", tMoveData[0].moveX[i], tMoveData[0].moveY[i], tMoveData[0].moveZ[i]);
		}
		printf("\n---------------------------------------\n");
		for (int i = 0; i < 101; ++i){
			printf("x : %f, y : %f, z : %f\n", tMoveData[1].moveX[i], tMoveData[1].moveY[i], tMoveData[1].moveZ[i]);
		}
	}

	if (key == 'c' || key == 'C'){
		if (What_Mode == Draw_Mode){
			What_Mode = View_Mode;
		}
		else{
			What_Mode = Draw_Mode;
		}
	}
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
	//---------------------------------------------------------------------
	// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
	y = sViewPort.top - y;
	// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
	if (y >= 0){
		-(y);
	}
	//---------------------------------------------------------------------
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && y >= 130){
		if (What_Mode == Draw_Mode){
			if (sViewPort.right <= x){
				//printf("Left = (%d, %d)\n", x - sViewPort.right, y);

				for (int i = 0; i < count; ++i){
					if (ctrlpoints[i][0] - 5 <= x - sViewPort.right && ctrlpoints[i][0] + 5 >= x - sViewPort.right){
						if ((sViewPort.top / 2) - 5 <= y && (sViewPort.top / 2) + 5 >= y){
							//printf("%d번째와 충돌함.\n", i);
							iMemoryX = x - sViewPort.right, iMemoryY = y;
							iNowCount = i;
							bMove = true;
						}
					}

				}

			}
			else{
				bMove = false;
				if (count == LimitPoint - 1){
					count = LimitPoint - 1;
				}
				else{
					if (x <= sViewPort.right){
						//printf("Count : %d (%d, %d)\n", count, x, y);
						ctrlpoints[count][0] = x;
						ctrlpoints[count][1] = y;
						ctrlpoints[count][2] = 0;
						for (int i = count; i < LimitPoint; i++){
							ctrlpoints[i][0] = x;
							ctrlpoints[i][1] = y;
							ctrlpoints[i][2] = 0;
						}
						count++;
					}
				}
			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && bMove == true){

		iNowCount = -1;
		bMove = false;
	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		init();

		for (int i = 0; i < LimitBuilding; ++i){
			printf("%d.\n-------------------------------------------------------\n", i);
			printf("XYZ = %d, %d, %d\n", tBuilding[i].ScaleX, tBuilding[i].ScaleY, tBuilding[i].ScaleZ);
			printf("Move = %d, %d, %d\n", tBuilding[i].MoveX, tBuilding[i].MoveY, tBuilding[i].MoveZ);
			printf("Color = %f, %f, %f\n", tBuilding[i].color[0], tBuilding[i].color[1], tBuilding[i].color[2]);
			printf("-------------------------------------------------------\n");
		}

	}
	glutPostRedisplay(); // 화면 재 출력
}

void MouseMotion(int x, int y){
	//---------------------------------------------------------------------
	// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
	y = sViewPort.top - y;
	// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
	if (y >= 0){
		-y;
	}
	//---------------------------------------------------------------------
	if (bMove == true){
		int iMoveX = 0;
		int iMoveZ = 0;

		iMoveX = (x - sViewPort.right);// - iMemoryX;
		iMoveZ = y - iMemoryY;

		ctrlpoints[iNowCount][0] = iMoveX;
		ctrlpoints[iNowCount][2] = iMoveZ;
	}
}

void vDrawLines(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glBegin(GL_LINES); // 선
	glColor3f(1.0f, 1.0f, 0.0f); // 그리기 색을 'Yellow' 으로 지정
	glVertex2i(isX, isY);
	glVertex2i(isX2, isY2);
	glEnd();
	//---------------------------------------------------------------------
}

GLvoid Reshape(int w, int h){
	sViewPort.right = w * 0.5;
	sViewPort.top = h;
	if (What_Mode == View_Mode){
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, w / h, 1.0, 1500.0);
		gluLookAt(0, 0, 700, 0, 0, -1, 0, 1, 0);
		glMatrixMode(GL_MODELVIEW);
	}
	else{
		viewport1_x = 0.5 * w; // 첫 번째 뷰포트의 폭을 설정 윈도우 폭의 50%.
		viewport1_y = h; // 높이는 윈도우 높이와 같다.
		viewport2_x = w - viewport1_x; //두 번째 뷰포트의 폭은 나머지 부분이 된다.
		viewport2_y = h; // 역시 높이는 동일하다.

		sViewPort.right = w * 0.5;
		sViewPort.top = h;
		sViewPort.left = 0;
		sViewPort.bottom = 0;
	}
}

void vLeftViewPort(){
	glViewport(0, 0, viewport1_x, viewport1_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, sViewPort.right, 0.0, sViewPort.top, -sViewPort.top, sViewPort.top);
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

void vRightViewPort(){
	glViewport(viewport1_x, 0, viewport2_x, viewport2_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, sViewPort.right, 0.0, sViewPort.top, 0, sViewPort.top);
	gluLookAt(0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void vDrawCurve(){
	for (int j = 0; j * 3 < count; j++){
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[j * 3][0]);
		glEnable(GL_MAP1_VERTEX_3);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 100; i++)
			glEvalCoord1f((GLfloat)i / 100.0);
		glEnd();
		glDisable(GL_MAP1_VERTEX_3);
	}
}

void vDrawCurveDot(float fDotSize){
	glPointSize(fDotSize);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < count; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();
}

void vDrawBuilding(){
	for (int i = 0; i < LimitBuilding; ++i){
		glPushMatrix(); //Save
		glColor3f(tBuilding[i].color[0], tBuilding[i].color[1], tBuilding[i].color[2]);
		glTranslatef(tBuilding[i].MoveX, tBuilding[i].MoveY, tBuilding[i].MoveZ);
		glScaled(tBuilding[i].ScaleX, tBuilding[i].ScaleY, tBuilding[i].ScaleZ);
		glutSolidCube(50);
		glPopMatrix();
	}
}

void vDraw3DBuilding(){
	for (int i = 0; i < LimitBuilding; ++i){
		glPushMatrix(); //Save

		if (tBuilding[i].MoveX >= 200){
			tBuilding[i].MoveX = 200;
		}

		if (tBuilding[i].MoveZ >= 200){
			tBuilding[i].MoveZ = 200;
		}

		if (tBuilding[i].PlusMinus_x == 1){
			tBuilding[i].MoveX = -tBuilding[i].MoveX;
			tBuilding[i].PlusMinus_x = 2;
		}

		if (tBuilding[i].PlusMinus_z == 1){
			tBuilding[i].MoveZ = -tBuilding[i].MoveZ;
			tBuilding[i].PlusMinus_z = 2;
		}
		//1 ~ 5까지 y를 스캐일링함
		int MoveY = -170;

		if (tBuilding[i].ScaleY == 1){
			MoveY = 195;
		}
		else if (tBuilding[i].ScaleY == 2){
			MoveY = 185;
		}
		else if (tBuilding[i].ScaleY == 3){
			MoveY = 175;
		}
		else if (tBuilding[i].ScaleY == 4){
			MoveY = 165;
		}
		else if (tBuilding[i].ScaleY == 5){
			MoveY = 155;
		}

		glTranslatef(tBuilding[i].MoveX, -MoveY, tBuilding[i].MoveZ);

		glColor3f(tBuilding[i].color[0], tBuilding[i].color[1], tBuilding[i].color[2]);
		glScaled(tBuilding[i].ScaleX, tBuilding[i].ScaleY, tBuilding[i].ScaleZ);
		glutSolidCube(25);
		glPopMatrix();
	}
}


void vDrawGround(){
	glPushMatrix(); //Save
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//바닥
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-250, -213, 250);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(250, -213, 250);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(250, -213, -250);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-250, -213, -250);
	glEnd();

	//벽면
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-250, -213, 250);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-250, -213, -250);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-250, 100.0, -250);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-250, 100.0, 250);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-250, -213, -250);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(250, -213, -250);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(250, 100.0, -250);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-250, 100.0, -250);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(250, -213, -250);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(250, -213, 250);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(250, 100.0, 250);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(250, 100.0, -250);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(250, -213, 250);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-250, -213, 250);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-250, 100.0, 250);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(250, 100.0, 250);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void vLine(){
	glPushMatrix(); //Save
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
	glPopMatrix();
}

void vCalcMove(){
	int nt = 0;
	for (int n = 0; n < LimitPoint; n += 3){
		float a, b, c, d;
		int i = 0;
		for (float t = 0.0; t < 1.0; t += 0.01){
			a = (1 - t)*(1 - t)*(1 - t);
			b = 3 * t * (1 - t)*(1 - t);
			c = 3 * t*t*(1 - t);
			d = t*t*t;
			tMoveData[nt].moveX[i] = (a*ctrlpoints[n][0]) + (b*ctrlpoints[n + 1][0]) + (c*ctrlpoints[n + 2][0]) + (d*ctrlpoints[n + 3][0]);
			tMoveData[nt].moveY[i] = (a*ctrlpoints[n][1]) + (b*ctrlpoints[n + 1][1]) + (c*ctrlpoints[n + 2][1]) + (d*ctrlpoints[n + 3][1]);
			tMoveData[nt].moveZ[i] = (a*ctrlpoints[n][2]) + (b*ctrlpoints[n + 1][2]) + (c*ctrlpoints[n + 2][2]) + (d*ctrlpoints[n + 3][2]);
			++i;
		}
		nt += 1;
	}
}

void vDrawWeather(){
	for (int i = 0; i < 100; ++i){
		glPushMatrix();
		glTranslatef(tWeather[i].x, tWeather[i].y, tWeather[i].z);
		if (imode == 1){
			glColor3f(252, 254, 253);
			glutSolidSphere(5, 10, 10);
		}
		else if (imode == 2){
			glColor3f(0, 0, 255);
			glScaled(0.1, 1.0, 0.1);
			glutSolidCube(10);
		}
		glPopMatrix();
	}
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info){
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인핚다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 갂다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 핛당을 핚다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 핛당핚다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장핚다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}






void putPixel(int x, int y, int menu){

	if (menu == 0){
		sBar.x[sBar.i] = x;
		sBar.y[sBar.i] = y;
		sBar.i += 1;
	}

	if (menu == 1){
		sBar2.x[sBar2.i] = x;
		sBar2.y[sBar2.i] = y;
		sBar2.i += 1;
	}
	if (menu == 2){
		sBar2.x2[sBar2.j] = x;
		sBar2.y2[sBar2.j] = y;
		sBar2.j += 1;
	}
	if (menu == 3){
		sBar2.x3[sBar2.k] = x;
		sBar2.y3[sBar2.k] = y;
		sBar2.k += 1;
	}

	//glColor3f(255, 0, 0);
	//glPointSize(3.0);
	//glBegin(GL_POINTS);
	//glVertex2i(x, y); // set the point  
	//glEnd();
	//glFlush();
}

void bresenhamAlg(int x0, int y0, int x1, int y1, int menu){
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x, y;
	if (dx >= dy){
		int d = 2 * dy - dx;
		int ds = 2 * dy;
		int dt = 2 * (dy - dx);
		if (x0 < x1){
			x = x0;
			y = y0;
		}
		else{
			x = x1;
			y = y1;
			x1 = x0;
			y1 = y0;
		}
		putPixel(x, y, menu);
		while (x < x1){
			if (d < 0)
				d += ds;
			else {
				if (y < y1) {
					y++;
					d += dt;
				}
				else {
					y--;
					d += dt;
				}
			}
			x++;
			putPixel(x, y, menu);
		}
	}
	else {
		int d = 2 * dx - dy;
		int ds = 2 * dx;
		int dt = 2 * (dx - dy);
		if (y0 < y1) {
			x = x0;
			y = y0;
		}
		else {
			x = x1;
			y = y1;
			y1 = y0;
			x1 = x0;
		}
		putPixel(x, y, menu);
		while (y < y1)
		{
			if (d < 0)
				d += ds;
			else {
				if (x > x1){
					x--;
					d += dt;
				}
				else {
					x++;
					d += dt;
				}
			}
			y++;
			putPixel(x, y, menu);
		}
	}
}