#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void MouseMotion(int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

struct sRect{
	int top, bottom, right, left;
}sRect;

struct sTopRect{
	int iX, iY;
	int iX2, iY2;
}sTopRect;

struct  sSEMouse{
	int isX = 0, isY = 0;
	int ieX = 0, ieY = 0;
}sSEMouse;

typedef struct  sBottomRect{
	int iX, iY;
}sBottomRect;

typedef struct  sWaveRect{
	float iX, iY;
}sWaveRect;

typedef struct  sCut{
	int iWTFRember[5];
	bool bWTF[5];
	int iWTF[5];
	bool bOutRect[5];
	int iOutRectMove[5];
	bool bINrect[5];
	bool bDraw[5];
	int iX[5], iY[5];
}sCut;

void vinit();
void vReset();

void vDrawRect(int, int, int, int);
void vDrawLines(int, int, int, int);
void vDrawBasket();
void vDrawWave();
void vDrawMouseMotion();
void vDrawCompeleteRect();
void vDrawCutRect();
void vDrawCutRectTwo();

int vCalculateTopBottom(int, int, int, int, int);
int vCalculateLeftRight(int, int, int, int, int);

void vCalculateXyXy(int, int, int, int, int, int, int, int);
int iTotalX, iTotalY;

void vCCheck();

void vConfirmCheck(int, int, int, int);
void vCalculateRect();
void vCheck();

int iRealBottom = 0, iRealTop = 0, iRealLeft = 0, iRealRight = 0;


bool bCreateTopRect = false;
bool bCreateBottomRect = false;
bool bCreateWaveRect = false;

bool bMoveRightLeft = false;
bool bMoveBottomRightLeft = false;
bool bDontMove = false;

bool bSinCosLeft = false;
bool bSinCosRight = false;

int iCompare = -1;
int iComplete = 0;
int iLeftBye = 21;
int iRightBye = 31;

int iZ = 0;

bool bDrawMouse = false;
bool bCalculate = false;
bool bResetOkay = false;

bool bTopTimer = true;
bool bBottomTime = true;

bool bStop = false;

sBottomRect sBtmRect[4];
sWaveRect sWavRect[4];
sCut sCutRect[2];

void vClipingSort(int, int, struct  sCut[], bool);
void vClipingCheck(int, int, int, int, int, int, struct  sCut[], bool);
void vCliping(int, int, struct  sCut[], bool);


#define dLimitRect 5
sCut sCompleteRect[dLimitRect];	// 최대 5개까지 저장
sCut sClip[dLimitRect];
void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutTimerFunc(50, TimerFunction, 0);
	glutTimerFunc(25, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);
	glutTimerFunc(50, TimerFunction, 3);
	glutTimerFunc(50, TimerFunction, 4);
	glutTimerFunc(50, TimerFunction, 5);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기

	vinit();
	if (bDontMove == false){
		vDrawRect(sTopRect.iX, sTopRect.iY, sTopRect.iX2, sTopRect.iY2);
	}
	vDrawBasket();
	vDrawWave();
	vDrawMouseMotion();

	if (bCalculate == true){
		int iBottomX, iTopX;
		int iLeftY, iRightY;
		// 직선의 그래프 구하는방법
		iBottomX = vCalculateTopBottom(sSEMouse.isY, sSEMouse.ieY, sSEMouse.isX, sSEMouse.ieX, sTopRect.iY);
		iTopX = vCalculateTopBottom(sSEMouse.isY, sSEMouse.ieY, sSEMouse.isX, sSEMouse.ieX, sTopRect.iY2);
		iLeftY = vCalculateLeftRight(sSEMouse.isY, sSEMouse.ieY, sSEMouse.isX, sSEMouse.ieX, sTopRect.iX);
		iRightY = vCalculateLeftRight(sSEMouse.isY, sSEMouse.ieY, sSEMouse.isX, sSEMouse.ieX, sTopRect.iX2);
		iRealBottom = 0, iRealTop = 0, iRealLeft = 0, iRealRight = 0;
		vConfirmCheck(iLeftY, iRightY, iTopX, iBottomX);

		if (iRealBottom == 0 && iRealTop == 0 && iRealLeft == 0 && iRealRight == 0){
			printf("아무것도 충돌 하지 않음..!\n");
		}
		else{
			//충돌을 하였으니 자르자
			bDontMove = true;
			vCheck();
		}

		bCalculate = false;
	}

	vDrawCompeleteRect();

	glPushMatrix();
	if (bSinCosLeft == true || bSinCosRight == true){
		glRotatef(iZ, 0.0, 0.0, 1.0);
		if (bSinCosLeft == true){
			glTranslated(-iZ * 5, 0, 0);
		}
		if (bSinCosRight == true){
			glTranslated(-iZ * 10, 0, 0);
		}
	}
	if (iCompare == 1){
		vDrawCutRectTwo();
	}
	else{
		vDrawCutRect();
	}
	glPopMatrix();

	if (iCompare == 1){
		vDrawCutRect();
	}
	else{
		vDrawCutRectTwo();
	}

	for (int i = 0; i < dLimitRect; ++i){
		for (int j = 0; j < 5; ++j){
			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2i(sClip[i].iX[j], sClip[i].iY[j]);
		}
		glEnd();
	}

	glFlush(); // 화면에 출력하기
}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력

	switch (value){
	case 0:
		if (bDontMove == false){
			if (bMoveRightLeft == false){
				// Right
				sTopRect.iX += 4;
				sTopRect.iX2 += 4;
				if (sTopRect.iX2 >= 775){
					bMoveRightLeft = true;
				}
			}
			else{
				//Left
				sTopRect.iX -= 4;
				sTopRect.iX2 -= 4;
				if (sTopRect.iX <= 25){
					bMoveRightLeft = false;
				}
			}
		}
		else{
			int imoveRect = 0;
			if (bMoveRightLeft == false){
				for (int i = 0; i < 5; ++i){
					if (iCompare == 0){
						imoveRect = 1;
					}
					else{
						imoveRect = 0;
					}
					sCutRect[imoveRect].iX[i] += 7;
				}
			}
			else{
				for (int i = 0; i < 5; ++i){
					if (iCompare == 0){
						imoveRect = 1;
					}
					else{
						imoveRect = 0;
					}
					sCutRect[imoveRect].iX[i] -= 7;
				}
			}
		}
		if (bTopTimer == true){
			glutTimerFunc(50, TimerFunction, 0); // 타이머함수 재 설정
		}
		break;

	case 1:
		if (bMoveBottomRightLeft == false){
			for (int i = 0; i < 4; ++i){
				sBtmRect[i].iX += 4;
				sWavRect[i].iX += 4;
			}

			for (int k = 0; k < dLimitRect; ++k){
				for (int j = 0; j < 5; ++j){
					if (sCompleteRect[k].iX[j] != 0){
						sCompleteRect[k].iX[j] += 4;
					}
				}
			}

			for (int k = 0; k < dLimitRect; ++k){
				for (int j = 0; j < 5; ++j){
					if (sClip[k].bWTF[0] == true){
						sClip[k].iX[j] += 4;
					}
				}
			}

			sWavRect[0].iY -= 0.3;
			sWavRect[3].iY += 0.3;
			if (sBtmRect[3].iX >= 765){
				bMoveBottomRightLeft = true;
			}
		}
		else{
			for (int i = 0; i < 4; ++i){
				sBtmRect[i].iX -= 4;
				sWavRect[i].iX -= 4;
			}

			for (int k = 0; k < dLimitRect; ++k){
				for (int j = 0; j < 5; ++j){
					if (sCompleteRect[k].iX[j] != 0){
						sCompleteRect[k].iX[j] -= 4;
					}
				}
			}

			for (int k = 0; k < dLimitRect; ++k){
				for (int j = 0; j < 5; ++j){
					if (sClip[k].bWTF[0] == true){
						sClip[k].iX[j] -= 4;
					}
				}
			}

			sWavRect[0].iY += 0.3;
			sWavRect[3].iY -= 0.3;
			if (sBtmRect[0].iX <= 35){
				bMoveBottomRightLeft = false;
			}
		}

		if (bBottomTime == true){
			glutTimerFunc(25, TimerFunction, 1); // 타이머함수 재 설정
		}
		break;

	case 2:

		if (bStop == false){
			if (iCompare != 0 || iCompare != 3){
				for (int i = 0; i < 5; ++i){

					if (iCompare == 0 || iCompare == 1){
						sCutRect[iCompare].iY[i] -= 1;
					}
				}
				if (iCompare == 0 || iCompare == 1){
					vCCheck();
				}
			}
		}
		glutTimerFunc(10, TimerFunction, 2); // 타이머함수 재 설정
		break;

	case 3:
		if (bSinCosLeft == true){
			if (iLeftBye <= 50){
				iZ += 1.0;
				printf("%d, ", iZ);
				iLeftBye += 1;
				if (iLeftBye == 50){
					vReset();
				}
			}
		}
		glutTimerFunc(50, TimerFunction, 3); // 타이머함수 재 설정
		break;

	case 4:
		if (bSinCosRight == true){
			if (iRightBye <= 60){
				iZ -= 1.0;
				iRightBye += 1;
				if (iRightBye == 60){
					vReset();
				}
			}
		}
		glutTimerFunc(50, TimerFunction, 4); // 타이머함수 재 설정
		break;

	case 5:
		for (int i = 0; i < dLimitRect; ++i){
			vClipingSort(i, i, sCompleteRect, false);
		}
		//------------------------------------------------------------------------------------
		for (int k = 0; k < iComplete; ++k){
			int iClipDataY[dLimitRect];
			int iClipDataLocationY[dLimitRect];

			for (int i = 0; i < dLimitRect; ++i){
				iClipDataY[i] = sCompleteRect[k].iY[i];
				iClipDataLocationY[i] = i;
			}

			for (int i = 0; i < dLimitRect - 1; i++){
				for (int j = 0; j < dLimitRect - 1; j++){
					if (iClipDataY[j] > iClipDataY[j + 1]){
						int temp = iClipDataY[j];
						iClipDataY[j] = iClipDataY[j + 1];
						iClipDataY[j + 1] = temp;
						temp = iClipDataLocationY[j];
						iClipDataLocationY[j] = iClipDataLocationY[j + 1];
						iClipDataLocationY[j + 1] = temp;
					}
				}
			}
			int iWavY = sWavRect[0].iY;
			int iWavY2 = sWavRect[3].iY;
			if (sCompleteRect[k].iY[iClipDataLocationY[4]] < ((iWavY + iWavY2) / 2) - 10){
				for (int i = 0; i < dLimitRect; ++i){
					sClip[k].iX[i] = sCompleteRect[k].iX[i];
					sClip[k].iY[i] = sCompleteRect[k].iY[i];
				}
			}
		}
		//------------------------------------------------------------------------------------
		glutTimerFunc(50, TimerFunction, 5); // 타이머함수 재 설정
		break;
	}
}

void Keyboard(unsigned char key, int x, int y){
	glutPostRedisplay(); // 화면 재 출력
	printf("InPut Key = %c\n", key);

	if (key == 'r'){
		vReset();
	}

	if (key == 't'){
		if (bTopTimer == true){
			bTopTimer = false;
		}
		else{
			bTopTimer = true;
			glutTimerFunc(50, TimerFunction, 0); // 타이머함수 재 설정
		}
	}

	if (key == 'b'){
		if (bBottomTime == true){
			bBottomTime = false;
		}
		else{
			bBottomTime = true;
			glutTimerFunc(25, TimerFunction, 1); // 타이머함수 재 설정
		}
	}

	if (key == 'f'){
		if (bTopTimer == false){
			glutTimerFunc(50, TimerFunction, 0); // 타이머함수 재 설정
		}
	}

	if (key == 'g'){
		if (bBottomTime == false){
			glutTimerFunc(25, TimerFunction, 1); // 타이머함수 재 설정
		}
	}

	if (key == 'z'){
		iZ += 1.0;
	}
	else if (key == 'Z'){
		iZ -= 1.0;
	}
	//printf("X : %d, X2 : %d\n", sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iX[iRealBottomX2]);
	//printf("left : %d, right : %d, top : %d, bottom : %d\n", iLeftY, iRightY, iTopX, iBottomX);
}

void Mouse(int button, int state, int x, int y){
	//---------------------------------------------------------------------
	// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
	y = sRect.right - y;
	// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
	if (y >= 0){
		-y;
	}
	//---------------------------------------------------------------------

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if (sSEMouse.ieX != 0 && sSEMouse.ieY != 0){
			sSEMouse.ieX = 0, sSEMouse.ieY = 0;
		}
		bCalculate = false;
		bDrawMouse = true;
		sSEMouse.isX = x;
		sSEMouse.isY = y;
		//printf("Start = (%d, %d)\n", x, y);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		bCalculate = true;
		bDrawMouse = true;
		sSEMouse.ieX = x;
		sSEMouse.ieY = y;
		//printf("End = (%d, %d)\n", x, y);
		printf("(%d, %d) -> (%d, %d)\n", sSEMouse.isX, sSEMouse.isY, sSEMouse.ieX, sSEMouse.ieY);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("End = (%d, %d)\n", x, y);
		//printf("(%d, %d) -> (%d, %d)\n", sSEMouse.isX, sSEMouse.isY, sSEMouse.ieX, sSEMouse.ieY);
	}
}

void MouseMotion(int x, int y){
	//---------------------------------------------------------------------
	// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
	y = sRect.right - y;
	// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
	if (y >= 0){
		-y;
	}
	//---------------------------------------------------------------------
	if (bDrawMouse == true){
		sSEMouse.ieX = x;
		sSEMouse.ieY = y;
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	sRect.bottom = 0, sRect.top = 800, sRect.left = 0, sRect.right = 600;
	glutPostRedisplay(); // 화면 재 출력
}

void vinit(){
	//---------------------------------------------------------------------
	srand((unsigned)time(NULL));
	if (bCreateTopRect == false){
		sTopRect.iX = 25;
		sTopRect.iY = rand() % 110 + 400;
		sTopRect.iX2 = rand() % 110 + 50;
		sTopRect.iY2 = 540;
		//2printf("(%d, %d) (%d, %d)", sTopRect.iX, sTopRect.iY, sTopRect.iX2, sTopRect.iY2);
		bCreateTopRect = true;
	}

	if (bCreateBottomRect == false){
		sBtmRect[0].iX = 35;
		sBtmRect[0].iY = 150;
		sBtmRect[1].iX = 35;
		sBtmRect[1].iY = 40;
		sBtmRect[2].iX = 190;
		sBtmRect[2].iY = 40;
		sBtmRect[3].iX = 190;
		sBtmRect[3].iY = 150;
		bCreateBottomRect = true;
	}

	if (bCreateWaveRect == false){
		sWavRect[0].iX = 35;
		sWavRect[0].iY = 120;
		sWavRect[1].iX = 35;
		sWavRect[1].iY = 42;
		sWavRect[2].iX = 189;
		sWavRect[2].iY = 42;
		sWavRect[3].iX = 189;
		sWavRect[3].iY = 90;



		bCreateWaveRect = true;
	}


	//---------------------------------------------------------------------
}

void vReset(){
	//---------------------------------------------------------------------
	for (int i = 0; i < 2; ++i){
		for (int j = 0; j < 5; ++j){
			sCutRect[i].iX[j] = 0;
			sCutRect[i].iY[j] = 0;
			sCutRect[i].bINrect[j] = false;
			sCutRect[i].bDraw[j] = false;
			sCutRect[i].bOutRect[j] = false;
			sCutRect[i].iOutRectMove[j] = -1;
			sCutRect[i].bWTF[j] = false;
			sCutRect[i].iWTF[j] = 0;
		}
	}
	bSinCosLeft = false;
	bSinCosRight = false;
	iZ = 0.0;
	iRealBottom = 0, iRealTop = 0, iRealLeft = 0, iRealRight = 0;
	iRightBye = 31;
	iLeftBye = 21;
	if (bDontMove == true){
		bDontMove = false;
	}

	if (bStop == true){
		bStop = false;
	}
	sSEMouse.ieX = 0, sSEMouse.isX = 0;
	sSEMouse.ieY = 0, sSEMouse.isY = 0;
	iCompare = -1;
	bCreateTopRect = false;
	//---------------------------------------------------------------------
}

void vDrawRect(int iX, int iY, int iX2, int iY2){
	//---------------------------------------------------------------------
	glColor3f(255, 0, 0); // 그리기 색을 'Red' 으로 지정
	glRecti(iX, iY, iX2, iY2); // 사각형 그리기 (x1, y1, x2, y2)
	//---------------------------------------------------------------------
}

void vDrawLines(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glBegin(GL_LINES); // 선
	glColor3f(1.0f, 1.0f, 1.0f); // 그리기 색을 'White' 으로 지정
	glVertex2i(isX, isY);
	glVertex2i(isX2, isY2);
	glEnd();
	//---------------------------------------------------------------------
}

void vDrawBasket(){
	//---------------------------------------------------------------------
	vDrawLines(sBtmRect[0].iX, sBtmRect[0].iY, sBtmRect[1].iX, sBtmRect[1].iY);
	vDrawLines(sBtmRect[1].iX, sBtmRect[1].iY, sBtmRect[2].iX, sBtmRect[2].iY);
	vDrawLines(sBtmRect[2].iX, sBtmRect[2].iY, sBtmRect[3].iX, sBtmRect[3].iY);
	//---------------------------------------------------------------------
}

void vDrawWave(){
	//---------------------------------------------------------------------
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < 4; ++i){
		glVertex2i(sWavRect[i].iX, sWavRect[i].iY);
	}
	glEnd();
	//---------------------------------------------------------------------
}

void vDrawMouseMotion(){
	//---------------------------------------------------------------------
	if (bDrawMouse == true){
		if (sSEMouse.ieX == 0 && sSEMouse.ieY == 0){
			vDrawLines(sSEMouse.isX, sSEMouse.isY, sSEMouse.isX, sSEMouse.isY);
		}
		else{
			vDrawLines(sSEMouse.isX, sSEMouse.isY, sSEMouse.ieX, sSEMouse.ieY);
		}
	}
	//---------------------------------------------------------------------
}

void vDrawCompeleteRect(){
	//---------------------------------------------------------------------
	for (int i = 0; i < dLimitRect; ++i){
		if (sCompleteRect[i].bDraw[i] == true){
			for (int j = 0; j < 5; ++j){
				glBegin(GL_POLYGON);
				glColor3f(1.0f, 1.0f, 1.0f);
				glVertex2i(sCompleteRect[i].iX[j], sCompleteRect[i].iY[j]);
			}
			glEnd();
		}
	}
	//---------------------------------------------------------------------
}

void vDrawCutRect(){
	int i = 0;

	glBegin(GL_POLYGON);
	if (i == 0){
		glColor3f(1.0f, 0.0f, 1.0f);
	}
	else{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	for (int j = 0; j < 5; ++j){
		glVertex2i(sCutRect[i].iX[j], sCutRect[i].iY[j]);
	}
	glEnd();

}

void vDrawCutRectTwo(){
	int i = 1;
	glBegin(GL_POLYGON);
	if (i == 0){
		glColor3f(1.0f, 0.0f, 1.0f);
	}
	else{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	for (int j = 0; j < 5; ++j){
		glVertex2i(sCutRect[i].iX[j], sCutRect[i].iY[j]);
	}
	glEnd();

}

int vCalculateTopBottom(int MouseStartY, int MouseEndY, int MouseStartX, int MouseEndX, int TopRextY){
	//printf("\n");
	float fTop = MouseStartY - MouseEndY;
	//printf("기울기 위 : %f\n", fTop);
	float  fBottom = MouseStartX - MouseEndX;
	//printf("기울기 아래 : %f\n", fBottom);
	float fM = fTop / fBottom;
	//printf("기울기 결과 : %f\n", fM);
	float fC2 = fM * MouseEndX;
	float fC = MouseEndY - fC2;
	int iResult = TopRextY - fC;
	iResult /= fM;

	return iResult;
	//printf("결과다 : %d\n", iResult);
}

int vCalculateLeftRight(int MouseStartY, int MouseEndY, int MouseStartX, int MouseEndX, int TopRextX){
	//printf("\n");
	float fTop = MouseStartY - MouseEndY;
	//printf("기울기 위 : %f\n", fTop);
	float  fBottom = MouseStartX - MouseEndX;
	//printf("기울기 아래 : %f\n", fBottom);
	float fM = fTop / fBottom;
	float fC2 = fM * MouseEndX;
	float fC = MouseEndY - fC2;
	int iResult = TopRextX*fM;
	iResult += fC;
	return iResult;
}

void vCalculateXyXy(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
	int iTopXM = ((x1*y2) - (y1*x2))*(x3 - x4);
	int iTopXM2 = (x1 - x2)*((x3*y4) - (y3*x4));
	int iBottomXM = (x1 - x2)*(y3 - y4);
	int iBottomXM2 = (y1 - y2)*(x3 - x4);

	iTotalX = (iTopXM - iTopXM2) / (iBottomXM - iBottomXM2);

	int iTopYM = ((x1*y2) - (y1*x2))*(y3 - y4);
	int iTopYM2 = (y1 - y2)*((x3*y4) - (y3*x4));
	int iBottomYM = (x1 - x2)*(y3 - y4);
	int iBottomYM2 = (y1 - y2)*(x3 - x4);

	iTotalY = (iTopYM - iTopYM2) / (iBottomYM - iBottomYM2);
}

void vConfirmCheck(int iLeftY, int iRightY, int iTopX, int iBottomX){
	if (iLeftY >= sTopRect.iY && iLeftY <= sTopRect.iY2){
		//2printf("왼쪽 : (%d, %d)\n", sTopRect.iX, iLeftY);
		iRealLeft = iLeftY;
	}

	if (iRightY >= sTopRect.iY && iRightY <= sTopRect.iY2){
		//2printf("오른쪽 : (%d, %d)\n", sTopRect.iX2, iRightY);
		iRealRight = iRightY;
	}

	if (iTopX >= sTopRect.iX && iTopX <= sTopRect.iX2){
		//2printf("위 : (%d, %d)\n", iTopX, sTopRect.iY2);
		iRealTop = iTopX;
	}

	if (iBottomX >= sTopRect.iX && iBottomX <= sTopRect.iX2){
		//2printf("아래 : (%d, %d)\n", iBottomX, sTopRect.iY);
		iRealBottom = iBottomX;
	}
}

void vCheck(){
	if (iRealTop != 0 && iRealBottom != 0){
		// 둘다 사각형
		//--------------------------------------------
		sCutRect[0].iX[0] = sTopRect.iX;
		sCutRect[0].iY[0] = sTopRect.iY2;
		sCutRect[0].iX[1] = sTopRect.iX;
		sCutRect[0].iY[1] = sTopRect.iY;
		sCutRect[0].iX[2] = iRealBottom;
		sCutRect[0].iY[2] = sTopRect.iY;
		sCutRect[0].iX[3] = iRealTop;
		sCutRect[0].iY[3] = sTopRect.iY2;
		sCutRect[0].iX[4] = iRealTop;
		sCutRect[0].iY[4] = sTopRect.iY2;
		if (sCutRect[0].iX[2] >= sCutRect[0].iX[3]){
			sCutRect[0].iWTF[0] = 11;
		}
		else{
			sCutRect[0].iWTF[0] = 12;
		}
		//--------------------------------------------
		sCutRect[1].iX[0] = iRealTop;
		sCutRect[1].iY[0] = sTopRect.iY2;
		sCutRect[1].iX[1] = iRealBottom;
		sCutRect[1].iY[1] = sTopRect.iY;
		sCutRect[1].iX[2] = sTopRect.iX2;
		sCutRect[1].iY[2] = sTopRect.iY;
		sCutRect[1].iX[3] = sTopRect.iX2;
		sCutRect[1].iY[3] = sTopRect.iY2;
		sCutRect[1].iX[4] = sTopRect.iX2;
		sCutRect[1].iY[4] = sTopRect.iY2;
		if (sCutRect[1].iX[0] >= sCutRect[1].iX[1]){
			sCutRect[1].iWTF[0] = 13;
		}
		else{
			sCutRect[1].iWTF[0] = 14;
		}

		//--------------------------------------------
		iCompare = 3; //계산 해야한다.
	}
	else if (iRealTop != 0 && iRealRight != 0){
		//--------------------------------------------
		sCutRect[0].iX[0] = sTopRect.iX;
		sCutRect[0].iY[0] = sTopRect.iY2;
		sCutRect[0].iX[1] = sTopRect.iX;
		sCutRect[0].iY[1] = sTopRect.iY;
		sCutRect[0].iX[2] = sTopRect.iX2;
		sCutRect[0].iY[2] = sTopRect.iY;
		sCutRect[0].iX[3] = sTopRect.iX2;
		sCutRect[0].iY[3] = iRealRight;
		sCutRect[0].iX[4] = iRealTop;
		sCutRect[0].iY[4] = sTopRect.iY2;
		sCutRect[0].iWTF[0] = 6;
		//--------------------------------------------
		sCutRect[1].iX[0] = iRealTop;
		sCutRect[1].iY[0] = sTopRect.iY2;
		sCutRect[1].iX[1] = sTopRect.iX2;
		sCutRect[1].iY[1] = iRealRight;
		sCutRect[1].iX[2] = sTopRect.iX2;
		sCutRect[1].iY[2] = sTopRect.iY2;
		sCutRect[1].iX[3] = sTopRect.iX2;
		sCutRect[1].iY[3] = sTopRect.iY2;
		sCutRect[1].iX[4] = sTopRect.iX2;
		sCutRect[1].iY[4] = sTopRect.iY2;
		sCutRect[1].iWTF[0] = 5;
		//--------------------------------------------
		iCompare = 1; //1번이 작다.
	}
	else if (iRealBottom != 0 && iRealRight != 0){
		//--------------------------------------------
		sCutRect[0].iX[0] = sTopRect.iX;
		sCutRect[0].iY[0] = sTopRect.iY2;
		sCutRect[0].iX[1] = sTopRect.iX;
		sCutRect[0].iY[1] = sTopRect.iY;
		sCutRect[0].iX[2] = iRealBottom;
		sCutRect[0].iY[2] = sTopRect.iY;
		sCutRect[0].iX[3] = sTopRect.iX2;
		sCutRect[0].iY[3] = iRealRight;
		sCutRect[0].iX[4] = sTopRect.iX2;
		sCutRect[0].iY[4] = sTopRect.iY2;
		sCutRect[0].iWTF[0] = 6;
		//--------------------------------------------
		sCutRect[1].iX[0] = iRealBottom;
		sCutRect[1].iY[0] = sTopRect.iY;
		sCutRect[1].iX[1] = sTopRect.iX2;
		sCutRect[1].iY[1] = sTopRect.iY;
		sCutRect[1].iX[2] = sTopRect.iX2;
		sCutRect[1].iY[2] = iRealRight;
		sCutRect[1].iX[3] = sTopRect.iX2;
		sCutRect[1].iY[3] = iRealRight;
		sCutRect[1].iX[4] = sTopRect.iX2;
		sCutRect[1].iY[4] = iRealRight;
		sCutRect[1].iWTF[0] = 2;
		//--------------------------------------------
		iCompare = 1; //1번이 작다.
	}
	else if (iRealTop != 0 && iRealLeft != 0){
		//--------------------------------------------
		sCutRect[0].iX[0] = sTopRect.iX;
		sCutRect[0].iY[0] = iRealLeft;
		sCutRect[0].iX[1] = sTopRect.iX;
		sCutRect[0].iY[1] = sTopRect.iY;
		sCutRect[0].iX[2] = sTopRect.iX2;
		sCutRect[0].iY[2] = sTopRect.iY;
		sCutRect[0].iX[3] = sTopRect.iX2;
		sCutRect[0].iY[3] = sTopRect.iY2;
		sCutRect[0].iX[4] = iRealTop;
		sCutRect[0].iY[4] = sTopRect.iY2;
		sCutRect[0].iWTF[0] = 6;
		//--------------------------------------------
		sCutRect[1].iX[0] = sTopRect.iX;
		sCutRect[1].iY[0] = sTopRect.iY2;
		sCutRect[1].iX[1] = sTopRect.iX;
		sCutRect[1].iY[1] = iRealLeft;
		sCutRect[1].iX[2] = iRealTop;
		sCutRect[1].iY[2] = sTopRect.iY2;
		sCutRect[1].iX[3] = iRealTop;
		sCutRect[1].iY[3] = sTopRect.iY2;
		sCutRect[1].iX[4] = iRealTop;
		sCutRect[1].iY[4] = sTopRect.iY2;
		sCutRect[1].iWTF[0] = 4;
		//--------------------------------------------
		iCompare = 1; //1번이 작다.
	}
	else if (iRealRight != 0 && iRealLeft != 0){
		//--------------------------------------------
		sCutRect[0].iX[0] = sTopRect.iX;
		sCutRect[0].iY[0] = sTopRect.iY2;
		sCutRect[0].iX[1] = sTopRect.iX;
		sCutRect[0].iY[1] = iRealLeft;
		sCutRect[0].iX[2] = sTopRect.iX2;
		sCutRect[0].iY[2] = iRealRight;
		sCutRect[0].iX[3] = sTopRect.iX2;
		sCutRect[0].iY[3] = sTopRect.iY2;
		sCutRect[0].iX[4] = sTopRect.iX2;
		sCutRect[0].iY[4] = sTopRect.iY2;
		if (sCutRect[0].iY[1] >= sCutRect[0].iY[2]){
			sCutRect[0].iWTF[0] = 15;
		}
		else{
			sCutRect[0].iWTF[0] = 16;
		}
		//--------------------------------------------
		sCutRect[1].iX[0] = sTopRect.iX;
		sCutRect[1].iY[0] = iRealLeft;
		sCutRect[1].iX[1] = sTopRect.iX;
		sCutRect[1].iY[1] = sTopRect.iY;
		sCutRect[1].iX[2] = sTopRect.iX2;
		sCutRect[1].iY[2] = sTopRect.iY;
		sCutRect[1].iX[3] = sTopRect.iX2;
		sCutRect[1].iY[3] = iRealRight;
		sCutRect[1].iX[4] = sTopRect.iX2;
		sCutRect[1].iY[4] = iRealRight;
		if (sCutRect[1].iY[0] >= sCutRect[1].iY[3]){
			sCutRect[1].iWTF[0] = 17;
		}
		else{
			sCutRect[1].iWTF[0] = 18;
		}
		//--------------------------------------------
		iCompare = 4; //계산이 필요하다.
	}
	else if (iRealLeft != 0 && iRealBottom != 0){
		//--------------------------------------------
		sCutRect[0].iX[0] = sTopRect.iX;
		sCutRect[0].iY[0] = sTopRect.iY2;
		sCutRect[0].iX[1] = sTopRect.iX;
		sCutRect[0].iY[1] = iRealLeft;
		sCutRect[0].iX[2] = iRealBottom;
		sCutRect[0].iY[2] = sTopRect.iY;
		sCutRect[0].iX[3] = sTopRect.iX2;
		sCutRect[0].iY[3] = sTopRect.iY;
		sCutRect[0].iX[4] = sTopRect.iX2;
		sCutRect[0].iY[4] = sTopRect.iY2;
		sCutRect[0].iWTF[0] = 6;
		//--------------------------------------------
		sCutRect[1].iX[0] = sTopRect.iX;
		sCutRect[1].iY[0] = iRealLeft;
		sCutRect[1].iX[1] = sTopRect.iX;
		sCutRect[1].iY[1] = sTopRect.iY;
		sCutRect[1].iX[2] = iRealBottom;
		sCutRect[1].iY[2] = sTopRect.iY;
		sCutRect[1].iX[3] = iRealBottom;
		sCutRect[1].iY[3] = sTopRect.iY;
		sCutRect[1].iX[4] = iRealBottom;
		sCutRect[1].iY[4] = sTopRect.iY;
		sCutRect[1].iWTF[0] = 3;
		//--------------------------------------------
		iCompare = 1; //1번이 작다.
	}
	vCalculateRect();
}

void vCalculateRect(){

	if (iCompare == 0 || iCompare == 1){
		// 계산할 필요가 없이 이미 답이 나왔다..!
		//glutTimerFunc(50, TimerFunction, 2); // 타이머함수 재 설정
	}
	else{
		if (iCompare == 3){
			int iTopH[2], iBottomH[2], iVertical[2], iCalculate[2];
			iTopH[0] = sCutRect[0].iX[3] - sCutRect[0].iX[0];
			iTopH[1] = sCutRect[1].iX[3] - sCutRect[1].iX[0];
			iBottomH[0] = sCutRect[0].iX[2] - sCutRect[0].iX[1];
			iBottomH[1] = sCutRect[1].iX[2] - sCutRect[1].iX[1];
			iVertical[0] = sCutRect[0].iY[0] - sCutRect[0].iY[1];
			iVertical[1] = sCutRect[1].iY[0] - sCutRect[1].iY[1];

			iCalculate[0] = iTopH[0] + iBottomH[0];
			iCalculate[0] *= iVertical[0];
			iCalculate[0] /= 2;

			iCalculate[1] = iTopH[1] + iBottomH[1];
			iCalculate[1] *= iVertical[1];
			iCalculate[1] /= 2;

			if (iCalculate[0] <= iCalculate[1]){
				iCompare = 0;
			}
			else{
				iCompare = 1;
			}
		}

		if (iCompare == 4){
			int iVertical[2], iHorizontal[2], iCalculate[2];
			iVertical[0] = sCutRect[0].iY[0] - sCutRect[0].iY[1];
			iVertical[1] = sCutRect[1].iY[0] - sCutRect[1].iY[1];
			iHorizontal[0] = sCutRect[0].iX[2] - sCutRect[0].iX[1];
			iHorizontal[1] = sCutRect[1].iX[2] - sCutRect[1].iX[1];
			iCalculate[0] = iHorizontal[0] * iVertical[0];
			iCalculate[1] = iHorizontal[1] * iVertical[1];

			if (iCalculate[0] <= iCalculate[1]){
				iCompare = 0;
			}
			else{
				iCompare = 1;
			}
		}
	}
}

void vCCheck(){
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// X, Y 좌표를 정렬을 이용해 가장 하단부분 구하는 것과
	// X, Y 좌표의 최소 최대값을 구한다.
	int iRectDataY[dLimitRect];
	int iRectDataX[dLimitRect];
	int iRectDataLocationY[dLimitRect];
	int iRectDataLocationX[dLimitRect];

	for (int i = 0; i < dLimitRect; ++i){
		iRectDataY[i] = sCutRect[iCompare].iY[i];
		iRectDataX[i] = sCutRect[iCompare].iX[i];
		iRectDataLocationY[i] = i;
		iRectDataLocationX[i] = i;
	}

	for (int i = 0; i < dLimitRect - 1; i++){
		for (int j = 0; j < dLimitRect - 1; j++){
			if (iRectDataY[j] > iRectDataY[j + 1]){
				int temp = iRectDataY[j];
				iRectDataY[j] = iRectDataY[j + 1];
				iRectDataY[j + 1] = temp;
				temp = iRectDataLocationY[j];
				iRectDataLocationY[j] = iRectDataLocationY[j + 1];
				iRectDataLocationY[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < dLimitRect - 1; i++){
		for (int j = 0; j < dLimitRect - 1; j++){
			if (iRectDataX[j] > iRectDataX[j + 1]){
				int temp = iRectDataX[j];
				iRectDataX[j] = iRectDataX[j + 1];
				iRectDataX[j + 1] = temp;
				temp = iRectDataLocationX[j];
				iRectDataLocationX[j] = iRectDataLocationX[j + 1];
				iRectDataLocationX[j + 1] = temp;
			}
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 왼쪽 모서리에 걸리는지, 오른쪽 모서리에 걸리는지 체크 하는 함수
	int iRealBottom = iRectDataLocationY[0];
	int iRealBottom2 = iRectDataLocationY[1];
	int iRealBottomX = iRectDataLocationX[0];
	int iRealBottomX2 = iRectDataLocationX[dLimitRect - 1];

	int iHeightM = 0;

	if (sBtmRect[0].iY >= sCutRect[iCompare].iY[iRealBottom]){
		if (sCutRect[iCompare].iX[iRealBottomX] <= sBtmRect[0].iX && sCutRect[iCompare].iX[iRealBottomX2] >= sBtmRect[0].iX){
			iHeightM = sCutRect[iCompare].iY[iRealBottom2] + sCutRect[iCompare].iY[iRealBottom];
			iHeightM /= 2;
			if (iHeightM == sBtmRect[0].iY){
				printf("Left");
				bSinCosLeft = true;
				bStop = true;
				iLeftBye = 0;
				//glutTimerFunc(10, TimerFunction, 3);
			}
		}

		if (sCutRect[iCompare].iX[iRealBottomX] <= sBtmRect[3].iX && sCutRect[iCompare].iX[iRealBottomX2] >= sBtmRect[3].iX){
			iHeightM = sCutRect[iCompare].iY[iRealBottom2] + sCutRect[iCompare].iY[iRealBottom];
			iHeightM /= 2;
			if (iHeightM == sBtmRect[3].iY){
				printf("Right");
				bSinCosRight = true;
				bStop = true;
				iRightBye = 0;
				//glutTimerFunc(10, TimerFunction, 3);
			}
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	//물통 안에 들어왔지만 나가려고 할때의 체크
	if (sBtmRect[0].iX <= sCutRect[iCompare].iX[iRealBottomX] && sBtmRect[3].iX >= sCutRect[iCompare].iX[iRealBottomX2]){
		if (sBtmRect[0].iY >= sCutRect[iCompare].iY[iRealBottom]){
			//printf("일단 안에 들어와있다..!");
			sCutRect[iCompare].bINrect[iCompare] = true;
		}
	}

	if (sCutRect[iCompare].bINrect[iCompare] == true){
		if (sCutRect[iCompare].iX[iRealBottomX] <= sBtmRect[0].iX){
			for (int j = 0; j < 5; ++j){
				sCutRect[iCompare].iX[j] += 2;
				sClip[iCompare].iX[j] += 2;
			}
		}
	}

	if (sCutRect[iCompare].bINrect[iCompare] == true){
		if (sCutRect[iCompare].iX[iRealBottomX2] >= sBtmRect[3].iX){
			for (int j = 0; j < 5; ++j){
				sCutRect[iCompare].iX[j] -= 2;
				sClip[iCompare].iX[j] -= 2;
			}
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	//이미 일정 수준 이상 내려가서 바구니 안에 못들어 가게 한다.
	if (sBtmRect[0].iY >= sCutRect[iCompare].iY[iRealBottom] && sCutRect[iCompare].bINrect[iCompare] == false){
		sCutRect[iCompare].bOutRect[iCompare] = true;

		if (sCutRect[iCompare].bOutRect[iCompare] == true){
			if (sCutRect[iCompare].iX[iRealBottomX2] <= sBtmRect[0].iX && sCutRect[iCompare].iX[iRealBottomX2] <= sBtmRect[3].iX){
				//왼쪽 = 1
				sCutRect[iCompare].iOutRectMove[iCompare] = 1;
			}
		}

		if (sCutRect[iCompare].bOutRect[iCompare] == true){
			if (sCutRect[iCompare].iX[iRealBottomX] >= sBtmRect[3].iX  && sCutRect[iCompare].iX[iRealBottomX] >= sBtmRect[0].iX){
				// 오른쪽 = 2
				sCutRect[iCompare].iOutRectMove[iCompare] = 2;
			}
		}
	}

	if (sCutRect[iCompare].iX[iRealBottomX2] >= sBtmRect[0].iX && sCutRect[iCompare].iOutRectMove[iCompare] == 1){
		for (int j = 0; j < 5; ++j){
			sCutRect[iCompare].iX[j] -= 2;
		}
	}

	if (sCutRect[iCompare].iX[iRealBottomX] <= sBtmRect[3].iX && sCutRect[iCompare].iOutRectMove[iCompare] == 2){
		for (int j = 0; j < 5; ++j){
			sCutRect[iCompare].iX[j] += 2;
		}
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 정확하게 물 안에 들어갈 경우
	if (sBtmRect[0].iX <= sCutRect[iCompare].iX[iRealBottomX] && sBtmRect[3].iX >= sCutRect[iCompare].iX[iRealBottomX2]){
		//클리핑 함수?
		vClipingSort(iCompare, iComplete, sCutRect, true);
		if (sBtmRect[1].iY >= sCutRect[iCompare].iY[iRealBottom]){
			bStop = true;
			for (int i = 0; i < dLimitRect; ++i){
				sCompleteRect[iComplete].iX[i] = sCutRect[iCompare].iX[i];
				sCompleteRect[iComplete].iY[i] = sCutRect[iCompare].iY[i];
			}
			//클리핑이 어긋나거나 할경우를 대비한 부분..!
			int iClipDataY[dLimitRect];
			int iClipDataLocationY[dLimitRect];

			for (int i = 0; i < dLimitRect; ++i){
				iClipDataY[i] = sClip[iCompare].iY[i];
				iClipDataLocationY[i] = i;
			}

			for (int i = 0; i < dLimitRect - 1; i++){
				for (int j = 0; j < dLimitRect - 1; j++){
					if (iClipDataY[j] > iClipDataY[j + 1]){
						int temp = iClipDataY[j];
						iClipDataY[j] = iClipDataY[j + 1];
						iClipDataY[j + 1] = temp;
						temp = iClipDataLocationY[j];
						iClipDataLocationY[j] = iClipDataLocationY[j + 1];
						iClipDataLocationY[j + 1] = temp;
					}
				}
			}

			if (sClip[iCompare].iY[iClipDataLocationY[4]] <= (iClipDataY[0] + iClipDataY[3]) / 2){
				for (int i = 0; i < dLimitRect; ++i){
					sClip[iComplete].iX[i] = sCompleteRect[iComplete].iX[i];
					sClip[iComplete].iY[i] = sCompleteRect[iComplete].iY[i];
				}
			}
			//클리핑이 어긋나거나 할경우를 대비한 부분..!
			sCompleteRect[iComplete].iWTF[0] = sCutRect[iCompare].iWTF[0];
			sCompleteRect[iComplete].bDraw[iComplete] = true;
			iComplete++;
			if (iComplete > dLimitRect){
				iComplete = 0;
			}
			vReset();
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	//화면 밖으로 완전히 나갈시 초기화..!
	if (iCompare != -1 && sCutRect[iCompare].iY[iRealBottom2] <= 0){
		bStop = true;
		vReset();
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
}


void vClipingSort(int iCompare, int iComplete, struct sCut sCutRect[], bool bNewRect){
	// 클리핑 어떻게 해야하지?
	int iBottomX, iTopX;
	int iLeftY, iRightY;
	// 직선의 그래프 구하는방법
	int iRectDataY[dLimitRect];
	int iRectDataX[dLimitRect];
	int iRectDataLocationY[dLimitRect];
	int iRectDataLocationX[dLimitRect];

	for (int i = 0; i < dLimitRect; ++i){
		iRectDataY[i] = sCutRect[iCompare].iY[i];
		iRectDataX[i] = sCutRect[iCompare].iX[i];
		iRectDataLocationY[i] = i;
		iRectDataLocationX[i] = i;
	}

	for (int i = 0; i < dLimitRect - 1; i++){
		for (int j = 0; j < dLimitRect - 1; j++){
			if (iRectDataY[j] > iRectDataY[j + 1]){
				int temp = iRectDataY[j];
				iRectDataY[j] = iRectDataY[j + 1];
				iRectDataY[j + 1] = temp;
				temp = iRectDataLocationY[j];
				iRectDataLocationY[j] = iRectDataLocationY[j + 1];
				iRectDataLocationY[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < dLimitRect - 1; i++){
		for (int j = 0; j < dLimitRect - 1; j++){
			if (iRectDataX[j] > iRectDataX[j + 1]){
				int temp = iRectDataX[j];
				iRectDataX[j] = iRectDataX[j + 1];
				iRectDataX[j + 1] = temp;
				temp = iRectDataLocationX[j];
				iRectDataLocationX[j] = iRectDataLocationX[j + 1];
				iRectDataLocationX[j + 1] = temp;
			}
		}
	}
	int iRealBottomY = iRectDataLocationY[0];
	int iRealBottomY2 = iRectDataLocationY[dLimitRect - 1];
	int iRealBottomX = iRectDataLocationX[0];
	int iRealBottomX2 = iRectDataLocationX[dLimitRect - 1];

	iBottomX = vCalculateTopBottom(sWavRect[0].iY, sWavRect[3].iY, sWavRect[0].iX, sWavRect[3].iX, sCutRect[iCompare].iY[iRealBottomY]);
	iTopX = vCalculateTopBottom(sWavRect[0].iY, sWavRect[3].iY, sWavRect[0].iX, sWavRect[3].iX, sCutRect[iCompare].iY[iRealBottomY2]);
	iLeftY = vCalculateLeftRight(sWavRect[0].iY, sWavRect[3].iY, sWavRect[0].iX, sWavRect[3].iX, sCutRect[iCompare].iX[iRealBottomX]);
	iRightY = vCalculateLeftRight(sWavRect[0].iY, sWavRect[3].iY, sWavRect[0].iX, sWavRect[3].iX, sCutRect[iCompare].iX[iRealBottomX2]);

	vClipingCheck(iLeftY, iRightY, iTopX, iBottomX, iCompare, iComplete, sCutRect, bNewRect);
}


void vClipingCheck(int iLeftY, int iRightY, int iTopX, int iBottomX, int iCompare, int iComplete, struct sCut sCutRect[], bool bNewRect){
	int iRectDataY[dLimitRect];
	int iRectDataX[dLimitRect];
	int iRectDataLocationY[dLimitRect];
	int iRectDataLocationX[dLimitRect];

	for (int i = 0; i < dLimitRect; ++i){
		iRectDataY[i] = sCutRect[iCompare].iY[i];
		iRectDataX[i] = sCutRect[iCompare].iX[i];
		iRectDataLocationY[i] = i;
		iRectDataLocationX[i] = i;
	}

	for (int i = 0; i < dLimitRect - 1; i++){
		for (int j = 0; j < dLimitRect - 1; j++){
			if (iRectDataY[j] > iRectDataY[j + 1]){
				int temp = iRectDataY[j];
				iRectDataY[j] = iRectDataY[j + 1];
				iRectDataY[j + 1] = temp;
				temp = iRectDataLocationY[j];
				iRectDataLocationY[j] = iRectDataLocationY[j + 1];
				iRectDataLocationY[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < dLimitRect - 1; i++){
		for (int j = 0; j < dLimitRect - 1; j++){
			if (iRectDataX[j] > iRectDataX[j + 1]){
				int temp = iRectDataX[j];
				iRectDataX[j] = iRectDataX[j + 1];
				iRectDataX[j + 1] = temp;
				temp = iRectDataLocationX[j];
				iRectDataLocationX[j] = iRectDataLocationX[j + 1];
				iRectDataLocationX[j + 1] = temp;
			}
		}
	}

	int iRealBottomY = iRectDataLocationY[0];
	int iRealBottomY2 = iRectDataLocationY[dLimitRect - 1];
	int iRealBottomX = iRectDataLocationX[0];
	int iRealBottomX2 = iRectDataLocationX[dLimitRect - 1];
	iRealLeft = 0, iRealRight = 0, iRealTop = 0, iRealBottom = 0;

	bool bDelete[4] = { (false, false, false, false) };

	if (iLeftY >= sCutRect[iCompare].iY[iRealBottomY] && iLeftY <= sCutRect[iCompare].iY[iRealBottomY2]){
		//2printf("왼쪽 : (%d, %d)\n", sCutRect[iCompare].iX[iRealBottomX], iLeftY);
		iRealLeft = iLeftY;
		bDelete[0] = true;
	}

	if (iRightY >= sCutRect[iCompare].iY[iRealBottomY] && iRightY <= sCutRect[iCompare].iY[iRealBottomY2]){
		//2printf("오른쪽 : (%d, %d)\n", sCutRect[iCompare].iX[iRealBottomX2], iRightY);
		iRealRight = iRightY;
		bDelete[1] = true;
	}

	if (iTopX >= sCutRect[iCompare].iX[iRealBottomX] && iTopX <= sCutRect[iCompare].iX[iRealBottomX2]){
		//2printf("위 : (%d, %d)\n", iTopX, sCutRect[iCompare].iY[iRealBottomY2]);
		iRealTop = iTopX;
		bDelete[2] = true;
	}

	if (iBottomX >= sCutRect[iCompare].iX[iRealBottomX] && iBottomX <= sCutRect[iCompare].iX[iRealBottomX2]){
		//2printf("아래 : (%d, %d)\n", iBottomX, sCutRect[iCompare].iY[iRealBottomY]);
		iRealBottom = iBottomX;
		bDelete[3] = true;
	}

	for (int i = 0; i < 4; ++i){
		if (bDelete[i] == false){
			if (i == 0){
				iRealLeft = 0;
			}
			else if (i == 1){
				iRealRight = 0;
			}
			else if (i == 2){
				iRealTop = 0;
			}
			else if (i == 3){
				iRealBottom = 0;
			}

		}
	}


	vCliping(iCompare, iComplete, sCutRect, bNewRect);
}

void vCliping(int iCompare, int iComplete, struct sCut sCutRect[], bool bNewRect){
	int iRectDataY[dLimitRect];
	int iRectDataX[dLimitRect];
	int iRectDataLocationY[dLimitRect];
	int iRectDataLocationX[dLimitRect];

	for (int i = 0; i < dLimitRect; ++i){
		iRectDataY[i] = sCutRect[iCompare].iY[i];
		iRectDataX[i] = sCutRect[iCompare].iX[i];
		iRectDataLocationY[i] = i;
		iRectDataLocationX[i] = i;
	}

	for (int i = 0; i < dLimitRect - 1; i++){
		for (int j = 0; j < dLimitRect - 1; j++){
			if (iRectDataY[j] > iRectDataY[j + 1]){
				int temp = iRectDataY[j];
				iRectDataY[j] = iRectDataY[j + 1];
				iRectDataY[j + 1] = temp;
				temp = iRectDataLocationY[j];
				iRectDataLocationY[j] = iRectDataLocationY[j + 1];
				iRectDataLocationY[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < dLimitRect - 1; i++){
		for (int j = 0; j < dLimitRect - 1; j++){
			if (iRectDataX[j] > iRectDataX[j + 1]){
				int temp = iRectDataX[j];
				iRectDataX[j] = iRectDataX[j + 1];
				iRectDataX[j + 1] = temp;
				temp = iRectDataLocationX[j];
				iRectDataLocationX[j] = iRectDataLocationX[j + 1];
				iRectDataLocationX[j + 1] = temp;
			}
		}
	}
	int iRealBottomY = iRectDataLocationY[0];
	int iRealBottomY2 = iRectDataLocationY[dLimitRect - 1];
	int iRealBottomX = iRectDataLocationX[0];
	int iRealBottomX2 = iRectDataLocationX[dLimitRect - 1];

	/*printf("X 정렬 : ");
	for (int i = 0; i < 5; ++i){
	printf("%d ", iRectDataX[i]);
	}
	printf("\n");

	printf("Y 정렬 : ");
	for (int i = 0; i < 5; ++i){
	printf("%d ", iRectDataY[i]);
	}
	printf("\n");
	*/
	//printf("WTF : %d\n", sCutRect[iCompare].iWTF[0]);
	//printf("[%d]= %d\n", iComplete, sClip[iComplete].iX[0]);
	if (iRealLeft != 0 && iRealBottom != 0){

		if (sCutRect[iCompare].iWTF[0] == 2){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[1] = iTotalX;
			sClip[iComplete].iY[1] = iTotalY;
			sClip[iComplete].iX[2] = iRealBottom;
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = iRealBottom;
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[4] = iRealBottom;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY];
		}

		if (sCutRect[iCompare].iWTF[0] == 3){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = iRealLeft;
			sClip[iComplete].iX[2] = iRealBottom;
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = iRealBottom;
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[4] = iRealBottom;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY];
		}

		if (sCutRect[iCompare].iWTF[0] == 4){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = iRealLeft;
			sClip[iComplete].iX[2] = iTotalX;
			sClip[iComplete].iY[2] = iTotalY;
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

		if (sCutRect[iCompare].iWTF[0] == 11){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = iRealBottom;
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = iRealBottom;
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[4] = iRealBottom;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY];
		}

		if (sCutRect[iCompare].iWTF[0] == 12){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRectDataLocationX[dLimitRect - 3]], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = iTotalX;
			sClip[iComplete].iY[2] = iTotalY;
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

		if (sCutRect[iCompare].iWTF[0] == 13){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRectDataLocationX[1]], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = iTotalX;
			sClip[iComplete].iY[0] = iTotalY;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = iRealBottom;
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = iRealBottom;
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[4] = iRealBottom;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY];
		}

		if (sCutRect[iCompare].iWTF[0] == 14){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY2], sCutRect[iCompare].iX[iRectDataLocationX[1]], sCutRect[iCompare].iY[iRealBottomY]);
			sClip[iComplete].iX[0] = iTotalX;
			sClip[iComplete].iY[0] = iTotalY;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRectDataLocationX[1]];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = iRealBottom;
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = iRealBottom;
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[4] = iRealBottom;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY];
		}

		if (sCutRect[iCompare].iWTF[0] == 16){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRectDataLocationY[1]]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = iTotalX;
			sClip[iComplete].iY[2] = iTotalY;
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

		if (sCutRect[iCompare].iWTF[0] == 17){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRectDataLocationY[1]]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = iTotalX;
			sClip[iComplete].iY[2] = iTotalY;
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

		if (sCutRect[iCompare].iWTF[0] == 18){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRectDataLocationY[1]]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = iTotalX;
			sClip[iComplete].iY[2] = iTotalY;
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

	}

	if (iRealLeft != 0 && iRealRight != 0){
		// 삼각형일때!
		if (sCutRect[iCompare].iWTF[0] == 2){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[1] = iTotalX;
			sClip[iComplete].iY[1] = iTotalY;
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = iRealRight;
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY];
		}

		if (sCutRect[iCompare].iWTF[0] == 3){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY2], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = iRealLeft;
			sClip[iComplete].iX[2] = iTotalX;
			sClip[iComplete].iY[2] = iTotalY;
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY];
		}

		if (sCutRect[iCompare].iWTF[0] == 4){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = iRealLeft;
			sClip[iComplete].iX[2] = iTotalX;
			sClip[iComplete].iY[2] = iTotalY;
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

		if (sCutRect[iCompare].iWTF[0] == 5){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY2], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY]);
			sClip[iComplete].iX[0] = iTotalX;
			sClip[iComplete].iY[0] = iTotalY;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = iRealRight;
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = iRealRight;
		}

		if (sCutRect[iCompare].iWTF[0] == 11){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRectDataLocationX[dLimitRect - 2]], sCutRect[iCompare].iY[iRealBottomY2], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

		if (sCutRect[iCompare].iWTF[0] == 12){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRectDataLocationX[dLimitRect - 3]], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRectDataLocationX[dLimitRect - 3]];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

		if (sCutRect[iCompare].iWTF[0] == 13){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRectDataLocationX[1]], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = iTotalX;
			sClip[iComplete].iY[0] = iTotalY;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = iRealRight;
		}

		if (sCutRect[iCompare].iWTF[0] == 14){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY2], sCutRect[iCompare].iX[iRectDataLocationX[1]], sCutRect[iCompare].iY[iRealBottomY]);
			sClip[iComplete].iX[0] = iTotalX;
			sClip[iComplete].iY[0] = iTotalY;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRectDataLocationX[1]];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = iRealRight;
		}

		if (sCutRect[iCompare].iWTF[0] == 15){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRectDataLocationX[1]];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = iRealRight;
		}

		if (sCutRect[iCompare].iWTF[0] == 16){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRectDataLocationY[1]]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];

			if (iTotalX >= sCutRect[iCompare].iX[iRealBottomX2]){
				iTotalX = sCutRect[iCompare].iX[iRealBottomX2];
			}

			if (iRealRight >= sCutRect[iCompare].iY[iRectDataLocationY[1]]){
				sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
				sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRectDataLocationY[1]];
				sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
				sClip[iComplete].iY[3] = iRealRight;
				sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
				sClip[iComplete].iY[4] = iRealRight;

			}
			else{
				sClip[iComplete].iX[2] = iTotalX;
				sClip[iComplete].iY[2] = iTotalY;
				sClip[iComplete].iX[3] = iTotalX;
				sClip[iComplete].iY[3] = iTotalY;
				sClip[iComplete].iX[4] = iTotalX;
				sClip[iComplete].iY[4] = iTotalY;
			}

		}

		if (sCutRect[iCompare].iWTF[0] == 17){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = iRealRight;
		}

		if (sCutRect[iCompare].iWTF[0] == 18){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRectDataLocationY[dLimitRect - 3]], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			if (sCutRect[iCompare].iY[iRectDataLocationY[dLimitRect - 3]] <= iRealLeft){
				sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
				sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRectDataLocationY[dLimitRect - 3]];
			}
			else{
				sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
				sClip[iComplete].iY[0] = iRealLeft;
			}
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			if (sCutRect[iCompare].iY[iRectDataLocationY[dLimitRect - 3]] <= iRealLeft){
				sClip[iComplete].iX[4] = iTotalX;
				sClip[iComplete].iY[4] = iTotalY;
			}
			else{
				sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
				sClip[iComplete].iY[4] = iRealRight;
			}
		}


	}

	if (iRealTop != 0 && iRealLeft != 0){

		if (sCutRect[iCompare].iWTF[0] == 15){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRectDataLocationX[1]];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}


		if (sCutRect[iCompare].iWTF[0] == 16){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRectDataLocationY[1]];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}

	}

	if (iRealTop != 0 && iRealRight != 0){
		// 삼각형일때!
		if (sCutRect[iCompare].iWTF[0] == 2){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[1] = iTotalX;
			sClip[iComplete].iY[1] = iTotalY;
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = iRealRight;
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY];
		}

		if (sCutRect[iCompare].iWTF[0] == 4){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iY[iRealBottomX2];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[2] = iRealRight;
			sClip[iComplete].iX[3] = iTotalX;
			sClip[iComplete].iY[3] = iTotalY;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

		if (sCutRect[iCompare].iWTF[0] == 5){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = iRealRight;
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = iRealRight;
		}

		if (sCutRect[iCompare].iWTF[0] == 12){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRectDataLocationX[dLimitRect - 3]], sCutRect[iCompare].iY[iRealBottomY], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRectDataLocationX[dLimitRect - 3]];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}

		if (sCutRect[iCompare].iWTF[0] == 13){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRectDataLocationX[1]];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}

		if (sCutRect[iCompare].iWTF[0] == 14){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRectDataLocationX[1]];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}

		if (sCutRect[iCompare].iWTF[0] == 15){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRectDataLocationX[1]];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}

		if (sCutRect[iCompare].iWTF[0] == 16){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRectDataLocationY[1]];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}


		if (sCutRect[iCompare].iWTF[0] == 17){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRectDataLocationY[dLimitRect - 3]];
			sClip[iComplete].iX[4] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRectDataLocationY[dLimitRect - 3]];
		}

		if (sCutRect[iCompare].iWTF[0] == 18){
			vCalculateXyXy(sWavRect[0].iX, sWavRect[0].iY, sWavRect[3].iX, sWavRect[3].iY, sCutRect[iCompare].iX[iRealBottomX], sCutRect[iCompare].iY[iRectDataLocationY[dLimitRect - 3]], sCutRect[iCompare].iX[iRealBottomX2], sCutRect[iCompare].iY[iRealBottomY2]);
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = sCutRect[iCompare].iY[iRectDataLocationY[dLimitRect - 3]];
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = iRealRight;
			sClip[iComplete].iX[4] = iTotalX;
			sClip[iComplete].iY[4] = iTotalY;
		}

	}

	if (iRealTop != 0 && iRealLeft != 0 && iRealRight != 0){
		if (sCutRect[iCompare].iWTF[0] == 15){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRectDataLocationX[1]];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}

		if (sCutRect[iCompare].iWTF[0] == 16){
			sClip[iComplete].iX[0] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[0] = iRealLeft;
			sClip[iComplete].iX[1] = sCutRect[iCompare].iX[iRealBottomX];
			sClip[iComplete].iY[1] = sCutRect[iCompare].iY[iRealBottomY];
			sClip[iComplete].iX[2] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[2] = sCutRect[iCompare].iY[iRectDataLocationY[1]];
			sClip[iComplete].iX[3] = sCutRect[iCompare].iX[iRealBottomX2];
			sClip[iComplete].iY[3] = sCutRect[iCompare].iY[iRealBottomY2];
			sClip[iComplete].iX[4] = iRealTop;
			sClip[iComplete].iY[4] = sCutRect[iCompare].iY[iRealBottomY2];
		}

	}

	if (iRealTop == 0 && iRealRight == 0 && iRealLeft == 0 && iRealBottom == 0 || iRealTop != 0 || iRealTop != 0 && iRealRight != 0){
		//다끝난거다!!
		if (sBtmRect[0].iX <= sCutRect[iCompare].iX[iRealBottomX] && sBtmRect[3].iX >= sCutRect[iCompare].iX[iRealBottomX2]){
			sClip[iComplete].bWTF[0] = true;
			for (int i = 0; i < 5; ++i){
				if (bNewRect == true){
					// 물안에 들어왔는지 체크이후에 작동을 하게 한다..!
					sClip[iComplete].iY[i] -= 1;
					//sClip[iComplete].iY[i] = sCutRect[iCompare].iY[i];
					//sClip[iComplete].iX[i] = sCutRect[iCompare].iX[i];
				}
			}
		}

	}
}