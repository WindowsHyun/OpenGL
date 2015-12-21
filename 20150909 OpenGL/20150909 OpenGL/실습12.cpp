#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

int imX = -300, imY = -300;

void vDrawline(float, float, float, float);
void vDrawTriangles(float, float);

typedef struct sDrawLine{
	int iStartNum = 0;
	float fDataX[2], fDataY[2];
	bool bDraw = false;
}sDrawLine;

sDrawLine  sRealDraw;

//---------------------------------------
void vinit();
float fDataX[2];
float fDataY[2];
//---------------------------------------
// 직선에 삼각형을 움직이기 위한 방법
void vMoveLineT();
bool bDrawReady = false;
float fTDataX[2];
float fTDataY[2];
float fMoveDataY = 0.1;
float fMoveDataX = 0.1;
//---------------------------------------
// 회오리 움직이기 위한 방법
#define dCircleData 200
void vMoveLineC();
typedef struct  isCircle{
	int icX, icY;
	int icSX, icSY;
}isCircle;
isCircle isTC[dCircleData];
int iSize = 0;
bool bDrawCircleReady = false;
bool bDrawCircleReadyTwo = false;
void vDrawCircle(int, int, int);
void vMakeCircle();
float fCircleSpreadX = 0.1;
float fCircleSpreadY = 0.1;
int iMoveTemp = 199;
//---------------------------------------
#define dZigZagTotal 6
float fZigZagX[dZigZagTotal];
float fZigZagY[dZigZagTotal];
int iZigZagNum = 0;
bool bDrawZigZagReady = false;
bool bDrawZigZagReadyTwo = false;
float fMoveZigZagY = 0.1;
float fMoveZigZagX = 0.1;

float fCopyZigZagX = 0.0;
float fCopyZigZagY = 0.0;

bool bOkayX = false;
bool bOkayY = false;
bool bReverse = false;

int iMoveNum = 0;

void vMovePZigZag();
void vMoveMZigZag();
//---------------------------------------
struct isRect{
	int top, bottom, right, left;
}isRect;

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
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기

	vinit();	// 변수가 길어서 해당 변수를 줄여주기 위해서 만듬
	//---------------------------------------------------------------------
	// 직선 그리기
	if (sRealDraw.bDraw == true){
		vDrawline(sRealDraw.fDataX[0], sRealDraw.fDataY[0], sRealDraw.fDataX[1], sRealDraw.fDataY[1]);
		glPushMatrix();// 행렬을 저장한다.
		glTranslatef(fMoveDataX, fMoveDataY, 0.0f);
		vDrawTriangles(fDataX[0], fDataY[0]);
		glPopMatrix();// 행렬을 불러온다.

	}
	//---------------------------------------------------------------------
	// 회오리 그리기
	if (bDrawCircleReadyTwo == true){
		for (int i = 0; i < dCircleData; ++i){
			vDrawCircle(isTC[i].icSX, isTC[i].icSY, 3);
		}

		glPushMatrix();// 행렬을 저장한다.
		glTranslatef(fCircleSpreadX, fCircleSpreadY, 0.0f);
		vDrawTriangles(isTC[199].icSX, isTC[199].icSY);
		glPopMatrix();// 행렬을 불러온다.
	}
	//---------------------------------------------------------------------
	//지그재그 그리기
	if (bDrawZigZagReadyTwo == true){

		for (int i = 0; i < dZigZagTotal; ++i){
			if (i + 1 >= dZigZagTotal){
				vDrawline(fZigZagX[i], fZigZagY[i], fZigZagX[i], fZigZagY[i]);
			}
			else{
				vDrawline(fZigZagX[i], fZigZagY[i], fZigZagX[i + 1], fZigZagY[i + 1]);
			}
		}
		glPushMatrix();// 행렬을 저장한다.
		glTranslatef(fMoveZigZagX, fMoveZigZagY, 0.0f);
		vDrawTriangles(fZigZagX[iMoveNum], fZigZagY[iMoveNum]);
		glPopMatrix();// 행렬을 불러온다.

	}
	//---------------------------------------------------------------------

	glFlush(); // 화면에 출력하기

}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	if (sRealDraw.bDraw == true){
		vMoveLineT();
	}
	if (bDrawCircleReadyTwo == true){
		vMoveLineC();
	}

	if (bDrawZigZagReadyTwo == true){
		if (bReverse == false){
			vMovePZigZag();
		}
		else{
			vMoveMZigZag();
		}
	}

	glutTimerFunc(10, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'l' || key == 'L'){
		printf("vDrawline is Ready..!\n");
		bDrawReady = true;
		bDrawCircleReady = false;
		bDrawCircleReadyTwo = false;
		bDrawZigZagReady = false;
		bDrawZigZagReadyTwo = false;
	}

	if (key == 'c' || key == 'C'){
		printf("vDrawCircle is Ready..!\n");
		bDrawCircleReady = true;
		bDrawReady = false;
		sRealDraw.bDraw = false;
		bDrawZigZagReady = false;
		bDrawZigZagReadyTwo = false;
	}

	if (key == 'z' || key == 'Z'){
		printf("vDrawZigZag is Ready..!\n");
		bDrawZigZagReady = true;
		bDrawCircleReady = false;
		bDrawReady = false;
		sRealDraw.bDraw = false;
		bDrawCircleReadyTwo = false;
		bDrawZigZagReadyTwo = false;
	}

	if (key == 'q' || key == 'Q'){
		bDrawZigZagReadyTwo = true;
		bDrawZigZagReady = false;
		bDrawCircleReady = false;
		bDrawReady = false;
		sRealDraw.bDraw = false;
		bDrawCircleReadyTwo = false;

		fZigZagX[0] = 100, fZigZagY[0] = 550;
		fZigZagX[1] = 700, fZigZagY[1] = 550;
		fZigZagX[2] = 700, fZigZagY[2] = 350;
		fZigZagX[3] = 100, fZigZagY[3] = 350;
		fZigZagX[4] = 100, fZigZagY[4] = 150;
		fZigZagX[5] = 700, fZigZagY[5] = 150;
	}

}

void Mouse(int button, int state, int x, int y){
	//---------------------------------------------------------------------
	// y값이 반전 출력으로 인하여 전체값에서 y를 빼줌
	y = isRect.right - y;
	// 혹시라도 마이너스 값이 있을수 있으니 해당 마이너스 부분은 다시 플러스로 변경.
	if (y >= 0){
		-(y);
	}
	//---------------------------------------------------------------------

	imX = x, imY = y;	// 마우스 좌표 넣어놓는다.

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Left = (%d, %d)\n", x, y);
		//----------------------------------------------------------------------------------------------------
		// 직선을 따라 움직인다.
		if (bDrawReady == true){
			if (sRealDraw.iStartNum == 0){
				sRealDraw.fDataX[sRealDraw.iStartNum] = x;
				sRealDraw.fDataY[sRealDraw.iStartNum] = y;
				printf("RealDraw0 = (%f, %f)\n", sRealDraw.fDataX[sRealDraw.iStartNum], sRealDraw.fDataY[sRealDraw.iStartNum]);
				sRealDraw.bDraw = false;
				sRealDraw.iStartNum += 1;
			}
			else{
				sRealDraw.fDataX[sRealDraw.iStartNum] = x;
				sRealDraw.fDataY[sRealDraw.iStartNum] = y;
				printf("RealDraw1 = (%f, %f)\n", sRealDraw.fDataX[sRealDraw.iStartNum], sRealDraw.fDataY[sRealDraw.iStartNum]);
				sRealDraw.iStartNum = 0;
				sRealDraw.bDraw = true;
				fMoveDataY = 0.1;
				fMoveDataX = 0.1;
				for (int i = 0; i < 2; ++i){
					fTDataX[i] = sRealDraw.fDataX[i];
					fTDataY[i] = sRealDraw.fDataY[i];
				}
			}
		}
		//----------------------------------------------------------------------------------------------------
		// 회오리를  따라 움직인다.
		if (bDrawCircleReady == true){
			vMakeCircle();
			iMoveTemp = 199;
			fCircleSpreadX = 0.1;
			fCircleSpreadY = 0.1;
		}
		//----------------------------------------------------------------------------------------------------
		// 지그재그를 따라 움직인다.
		if (bDrawZigZagReady == true){

			fZigZagX[iZigZagNum] = x;
			fZigZagY[iZigZagNum] = y;
			printf("fZigZag[%d] = (%f, %f)\n", iZigZagNum, fZigZagX[iZigZagNum], fZigZagY[iZigZagNum]);
			iZigZagNum += 1;
			if (iZigZagNum >= dZigZagTotal){
				bDrawZigZagReadyTwo = true;
				iZigZagNum = 0;
				iMoveNum = 0;
				bReverse = false;
				fCopyZigZagX = fZigZagX[iMoveNum];
				fCopyZigZagY = fZigZagY[iMoveNum];
			}



		}
		//----------------------------------------------------------------------------------------------------

	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 800, isRect.left = 0, isRect.right = 600;
}


void vDrawline(float fDataX0, float fDataY0, float fDataX1, float fDataY1){
	//---------------------------------------------------------------------
	glBegin(GL_LINES); // 선
	glColor3f(1.0f, 0.0f, 0.0f); // 그리기 색을 'Red' 으로 지정
	//glVertex2i(sRealDraw.fDataX[0], sRealDraw.fDataY[0]);
	//glVertex2i(sRealDraw.fDataX[1], sRealDraw.fDataY[1]);
	glVertex2i(fDataX0, fDataY0);
	glVertex2i(fDataX1, fDataY1);

	glEnd();
	//---------------------------------------------------------------------
}

void vDrawTriangles(float fDataX, float fDataY){
	//---------------------------------------------------------------------
	glBegin(GL_TRIANGLES); //삼각형
	glColor3f(1.0f, 1.0f, 1.0f); // 그리기 색을 'White' 으로 지정
	glVertex2f(fDataX, fDataY + 30); //삼각형의 첫번째 꼭지점의 좌표를 지정한다.
	glVertex2f(fDataX - 30, fDataY - 30); //삼각형의 두번째 꼭지점의 좌표를 지정한다.
	glVertex2f(fDataX + 30, fDataY - 30); //삼각형의 세번째 꼭지점의 좌표를 지정한다.
	glEnd(); //그리기를 종료한다.
	//---------------------------------------------------------------------
}

void vMoveLineT(){
	float ftempX = abs(fTDataX[1] - fTDataX[0]) / 40;
	float ftempY = abs(fTDataY[1] - fTDataY[0]) / 40;

	if (fTDataX[1] > fTDataX[0]){

		fMoveDataX += ftempX;
		fTDataX[0] += ftempX;
	}
	else{
		fMoveDataX -= ftempX;
		fTDataX[0] -= ftempX;
	}


	if (fTDataY[1] > fTDataY[0]){

		fMoveDataY += ftempY;
		fTDataY[0] += ftempY;
	}
	else{
		fMoveDataY -= ftempY;
		fTDataY[0] -= ftempY;
	}


}

void vMoveLineC(){
	float ftempX = abs(isTC[iMoveTemp].icSX - isTC[iMoveTemp - 1].icSX);
	float ftempY = abs(isTC[iMoveTemp].icSY - isTC[iMoveTemp - 1].icSY);

	if (isTC[iMoveTemp].icSX > isTC[iMoveTemp - 1].icSX){
		fCircleSpreadX -= ftempX;
	}
	else{
		fCircleSpreadX += ftempX;
	}

	if (isTC[iMoveTemp].icSY > isTC[iMoveTemp - 1].icSY){
		fCircleSpreadY -= ftempY;
	}
	else{
		fCircleSpreadY += ftempY;
	}

	iMoveTemp -= 1;

	if (iMoveTemp <= 0){
		iMoveTemp = 199;
		fCircleSpreadX = 0.1;
		fCircleSpreadY = 0.1;
	}
}

void vMakeCircle(){
	int isRkreh = 0;
	bDrawCircleReadyTwo = false;
	iSize = 30;
	for (int i = 0; i < dCircleData; ++i){

		isTC[i].icSX = iSize * sin(i*(3.141592 / 18));
		isTC[i].icSX += imX;

		isTC[i].icSY = iSize * cos(i*(3.141592 / 18));
		isTC[i].icSY += imY;
		isRkreh += 10;
		iSize++;
	}
	bDrawCircleReadyTwo = true;
}

void vDrawCircle(int isMX, int isMY, int iSize){
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f); // 그리기 색을 'Red' 으로 지정
	for (int i = 0; i < 360; ++i){
		int icX = iSize * cos(i*(3.141592 / 180)), icY = iSize * sin(i*(3.141592 / 180));

		icX += isMX;
		icY += isMY;

		glVertex3f(icX, icY, 0);
	}
	glEnd();
}

void vinit(){
	for (int i = 0; i < 2; ++i){
		fDataX[i] = sRealDraw.fDataX[i];
		fDataY[i] = sRealDraw.fDataY[i];
	}
}

void vMovePZigZag(){
	float ftempX = abs(fZigZagX[iMoveNum + 1] - fZigZagX[iMoveNum]) / 100;
	float ftempY = abs(fZigZagY[iMoveNum + 1] - fZigZagY[iMoveNum]) / 100;

	float ftempCX = ftempX * 100;
	float ftempCY = ftempY * 100;

	if (abs(fMoveZigZagX) >= ftempCX){
		bOkayX = true;
		//printf("\n\nbOkayX = True\n\n");
	}
	else{
		if (fZigZagX[iMoveNum + 1] > fZigZagX[iMoveNum]){
			fMoveZigZagX += ftempX;
			fCopyZigZagX += ftempX;
		}
		else{
			fMoveZigZagX -= ftempX;
			fCopyZigZagX -= ftempX;
		}
	}


	if (abs(fMoveZigZagY) >= ftempCY){
		bOkayY = true;
		//printf("\n\nbOkayY = True\n\n");
	}
	else{
		if (fZigZagY[iMoveNum + 1] > fZigZagY[iMoveNum]){
			fMoveZigZagY += ftempY;
			fCopyZigZagY += ftempY;
		}
		else{
			fMoveZigZagY -= ftempY;
			fCopyZigZagY -= ftempY;
		}
	}


	if (bOkayX == true && bOkayY == true){
		iMoveNum += 1;
		if (iMoveNum == dZigZagTotal - 1){
			bReverse = true;
		}
		//printf("\n\nChange!!!\n\n");
		fCopyZigZagX = fZigZagX[iMoveNum];
		fCopyZigZagY = fZigZagY[iMoveNum];
		fMoveZigZagY = 0.1;
		fMoveZigZagX = 0.1;
		bOkayX = false, bOkayY = false;
	}
	//printf("(%f, %f) => (%f, %f)\n", fMoveZigZagX, fMoveZigZagY, ftempCX, ftempCY);
}

void vMoveMZigZag(){
	float ftempX = abs(fZigZagX[iMoveNum - 1] - fZigZagX[iMoveNum]) / 100;
	float ftempY = abs(fZigZagY[iMoveNum - 1] - fZigZagY[iMoveNum]) / 100;

	float ftempCX = ftempX * 100;
	float ftempCY = ftempY * 100;

	if (abs(fMoveZigZagX) >= ftempCX){
		bOkayX = true;
		//printf("\n\nbOkayX = True\n\n");
	}
	else{
		if (fZigZagX[iMoveNum - 1] > fZigZagX[iMoveNum]){
			fMoveZigZagX += ftempX;
			fCopyZigZagX += ftempX;
		}
		else{
			fMoveZigZagX -= ftempX;
			fCopyZigZagX -= ftempX;
		}
	}


	if (abs(fMoveZigZagY) >= ftempCY){
		bOkayY = true;
		//printf("\n\nbOkayY = True\n\n");
	}
	else{
		if (fZigZagY[iMoveNum - 1] > fZigZagY[iMoveNum]){
			fMoveZigZagY += ftempY;
			fCopyZigZagY += ftempY;
		}
		else{
			fMoveZigZagY -= ftempY;
			fCopyZigZagY -= ftempY;
		}
	}


	if (bOkayX == true && bOkayY == true){
		iMoveNum -= 1;
		if (iMoveNum == 0){
			bReverse = false;
		}
		//printf("\n\nChange!!!\n\n");
		fCopyZigZagX = fZigZagX[iMoveNum];
		fCopyZigZagY = fZigZagY[iMoveNum];
		fMoveZigZagY = 0.1;
		fMoveZigZagX = 0.1;
		bOkayX = false, bOkayY = false;
	}
	//printf("(%f, %f) => (%f, %f)\n", fMoveZigZagX, fMoveZigZagY, ftempCX, ftempCY);
}