#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#include <windows.h>

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint texture_object[12];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);


void vLine();
void vinit();
void vGround();
void vLightCircle();
void vLight1();

void RotationCircle();
void AxisOfRotation();
void CubeBox();
void CubeBox2();
void CubeBox3();

void Hammock();
void NoHammock();
void Snow();

float fMapZ = 0.0;
float vMapX = 0.0;
float vMapY = 0.0;
float fView = 0.0;

float turn0 = 0.0, turn1 = 0.0;

float turnCircle = 0.0, turnCircle2 = 0.0;

bool hammock = true;
int hammockTurn = 0;

bool hammock2 = true;
int hammockTurn2 = 0;

bool WhereSnow = true;

float fAmbient = 1.0, fAmbient2 = 1.0, fAmbient3 = 1.0;
float DiffuseLight1 = 1.0, DiffuseLight2 = 1.0, DiffuseLight3 = 1.0;

GLfloat lightpos[] = { 0, 0, 0, 1 };
GLfloat AmbientLight[] = { fAmbient, fAmbient2, fAmbient3, 1.0f };
GLfloat DiffuseLight[] = { DiffuseLight1, DiffuseLight2, DiffuseLight3, 1.0f };
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };

void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	vinit();
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutTimerFunc(50, TimerFunction, 2);
	glutTimerFunc(50, TimerFunction, 3);
	glutTimerFunc(50, TimerFunction, 4);
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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);      // 조명 활성화
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(vMapX, 1.0, 0, 0);
	glRotated(vMapY, 0, 1.0, 0);

	glPushMatrix(); //Save
	glTranslatef(0, 0, 0);
	vLightCircle();
	vLight1();
	glPopMatrix();


	glPushMatrix(); //Save
	vLine();
	glPopMatrix();


	glPushMatrix();			//바닥
	vGround();
	glPopMatrix();

	//------------------------------------------------
	glPushMatrix();
	glTranslatef(120, 0, -230);
	glRotated(turnCircle, 0, 0, 1.0);

	RotationCircle();	// 원 토러스

	AxisOfRotation();	// 회전축

	glPopMatrix();
	//------------------------------------------------
	glPushMatrix();

	glTranslatef(-250, -50, 10);

	glPushMatrix();
	glRotated(hammockTurn, 0, 0, 1.0);
	if (WhereSnow == true){
		Hammock();
	}
	else{
		NoHammock();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslated(180, 0, 0);
	glRotated(hammockTurn2, 0, 0, 1.0);
	if (WhereSnow == false){
		Hammock();
	}
	else{
		NoHammock();
	}
	glPopMatrix();

	glPopMatrix();
	//------------------------------------------------
	glPushMatrix();
	glTranslatef(-120, -100, -230);
	glPushMatrix();
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glRotated(65, 1.0, 1.0, 0);
	glTranslatef(-100, 0, 0.0);
	glRotated(turn0, 1.0, 1.0, 1.0);
	glutSolidCube(50);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glColor4f(1.0, 0.0, 0.0, 0.5);
	glRotated(65, 1.0, 1.0, 0);
	glTranslatef(-100, 0, 0.0);
	glRotated(turn1, 0, 1.0, 0);
	glutSolidCube(100);
	glDisable(GL_BLEND);
	glPopMatrix();
	glPopMatrix();
	//------------------------------------------------



	glPopMatrix();
	//glFlush(); // 화면에 출력하기
	glutSwapBuffers();     // 화면에 출력하기
}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	switch (value){

	case 1:
		turn0 += 5.0;
		turn1 -= 5.0;
		glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
		break;

	case 2:
		turnCircle += 1.0;
		turnCircle2 += turnCircle/360;
		glutTimerFunc(50, TimerFunction, 2); // 타이머함수 재 설정
		break;

	case 3:
		if (hammockTurn == 24){
			hammock = false;
			if (WhereSnow == false){
				WhereSnow = true;
			}
			else{
				WhereSnow = false;
			}
		}
		if (hammockTurn == -24){
			hammock = true;
		}

		if (hammock == true){
			hammockTurn += 1;
		}
		else{
			hammockTurn -= 1;
		}
		glutTimerFunc(50, TimerFunction, 3); // 타이머함수 재 설정
		break;

	case 4:
		if (hammockTurn2 == -24){
			hammock2 = false;

		}
		if (hammockTurn2 == 24){
			hammock2 = true;
		}

		if (hammock2 == true){
			hammockTurn2 -= 1;
		}
		else{
			hammockTurn2 += 1;
		}
		glutTimerFunc(50, TimerFunction, 4); // 타이머함수 재 설정
		break;


	}
	
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if(key == 'r'){
		vMapY -= 1.0;
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

	gluLookAt(0, 0, 700, 0, 0, -1, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
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

void vinit(){
	glGenTextures(11, texture_object);

	// 바닥
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	pBytes = LoadDIBitmap("image/Ground.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1023, 669, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 벽면
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	pBytes = LoadDIBitmap("image/B01.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void vGround(){
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3i(-300, -200, 300);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3i(300, -200, 300);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3i(300, -200, -300);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3i(-300, -200, -300);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-300.0, -200.0, -300.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(300.0, -200.0, -300.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(300.0, 200.0, -300.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-300.0, 200.0, -300.0);
	glEnd();
}

void vLightCircle(){
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(5, 20, 10);
}


void vLight1(){
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
}

void RotationCircle(){
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glutSolidTorus(5, 150, 10, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -50);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidTorus(5, 150, 10, 30);
	glPopMatrix();
}

void AxisOfRotation(){
	glPushMatrix();
	glTranslatef(0, 0, -20);



	glPushMatrix();
	CubeBox();
	glColor3f(1.0, 1.0, 1.0);
	glScaled(8.0, 0.1, 0.0);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glPushMatrix();
	CubeBox();
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glScaled(8.0, 0.1, 0.0);
	glutSolidCube(50);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 0, 0, 1.0);
	glPushMatrix();
	CubeBox2();
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glScaled(8.0, 0.1, 0.0);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glRotated(-45, 0, 0, 1.0);
	glPushMatrix();
	CubeBox3();
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glScaled(8.0, 0.1, 0.0);
	glutSolidCube(50);
	glPopMatrix();



	glPopMatrix();
}

void CubeBox(){
	glPushMatrix();
	glTranslatef(0, 180, 0);
	glRotated(-turnCircle, 0, 0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -180, 0);
	glRotated(-turnCircle, 0, 0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(40);
	glPopMatrix();
}

void CubeBox2(){
	glPushMatrix();
	glTranslatef(0, 180, 0);
	glRotated(-turnCircle, 0, 0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glRotated(-45, 0, 0, 1.0);
	glutSolidCube(40);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -180, 0);
	glRotated(-90, 0, 0, 1.0);
	glRotated(-turnCircle-90, 0, 0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glRotated(-45, 0, 0, 1.0);
	glutSolidCube(40);
	glPopMatrix();
	glPopMatrix();
}


void CubeBox3(){
	glPushMatrix();
	glTranslatef(0, 180, 0);
	glRotated(-turnCircle, 0, 0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glRotated(45, 0, 0, 1.0);
	glutSolidCube(40);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -180, 0);
	glRotated(-90, 0, 0, 1.0);
	glRotated(-turnCircle - 90, 0, 0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glRotated(45, 0, 0, 1.0);
	glutSolidCube(40);
	glPopMatrix();
	glPopMatrix();
}


void Hammock(){
	glPushMatrix();

	glTranslatef(0, -30, 0);
	Snow();
	glTranslatef(0, -20, 0);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glScaled(3.0, 0.2, 1.0);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25, 0, 0);
	glRotated(90, 1.0, 1.0, 0);
	glColor4f(1.0, 0.0, 0.0, 0.0);
	glScaled(0.1, 0.2, 2.5);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25, 0, 0);
	glRotated(-90, -1.0, 1.0, 0);
	glColor4f(1.0, 0.0, 0.0, 0.0);
	glScaled(0.1, 0.2, 2.5);
	glutSolidCube(50);
	glPopMatrix();
}

void NoHammock(){
	glPushMatrix();
	glTranslatef(0, -50, 0);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glScaled(3.0, 0.2, 1.0);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25, 0, 0);
	glRotated(90, 1.0, 1.0, 0);
	glColor4f(1.0, 0.0, 0.0, 0.0);
	glScaled(0.1, 0.2, 2.5);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25, 0, 0);
	glRotated(-90, -1.0, 1.0, 0);
	glColor4f(1.0, 0.0, 0.0, 0.0);
	glScaled(0.1, 0.2, 2.5);
	glutSolidCube(50);
	glPopMatrix();
}

void Snow(){
	glPushMatrix();
	glTranslatef(0, 25, 0);
	glColor4f(1.0, 0.0, 1.0, 0);
	glutSolidSphere(10, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 0.0, 1.0, 0);
	glutSolidSphere(20, 20, 10);
	glPopMatrix();
}