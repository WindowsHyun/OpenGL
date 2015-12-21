#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h> // 비트맵 파일 관련 자료 저장

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint texture_object[7];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);


typedef struct _SNOW{
	float dropSpeed;
	int x, y, z;
	float color[3];

	_SNOW(){
		x = rand() % 1000 - 500;
		z = rand() % 1000 - 500;
		y = rand() % 600;
		dropSpeed = rand() % 20 + 1;
		for (int i = 0; i < 3; ++i)
		{
			color[i] = rand() % 10 / 10.0;
		}
	}
}snow;

snow tSnow[100];

void SetupRC(){
	glGenTextures(7, texture_object);
	// 바닥
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	pBytes = LoadDIBitmap("image/Ground.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 1023, 669, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 피라미드
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	pBytes = LoadDIBitmap("image/Pyramid.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 1032, 774, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 지구
	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	pBytes = LoadDIBitmap("image/earth.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 390, 356, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 달
	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	pBytes = LoadDIBitmap("image/moon.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 227, 227, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);

	glEnable(GL_DEPTH_TEST);			 // 은면 제거
	glFrontFace(GL_CCW);					 // 앞면 설정  
	glEnable(GL_CULL_FACE);			 // 내부는 잘라낸다  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 배경색 설정
}


void vLine();
void vPyramid();
void vLightCircle();
void vLight1();
void vLight2();
void vLight3();
void vLight4();
void vDrawSnow();
void vGround();

bool bLight[1] = { (true) };

void vEarth();
void vMoon();

float fAmbient = 1.0;
float fDiffuse = 0.1;
float fSpecular = 0.1;

float fZoomInOut = -180;

float fMapB = 0.0;
float fMapZ = 0.0;
float vMapX = 0.0;
float vMapY = 0.0;
float fView = 0.0;

float fEarth = 0.0;
float fMoon = 0.0;

int posX = 0;
int posZ = 0;
int i360 = 0;

void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(10, TimerFunction, 0);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	SetupRC();
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 설정된 색으로 젂체를 칠하기
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);      // 조명 활성화
	glEnable(GL_COLOR_MATERIAL);
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_NORMALIZE);

	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(fMapB, 0, 1.0, 0);
	glRotated(vMapX, 1.0, 0, 0);
	glRotated(vMapY, 0, 1.0, 0);
	gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);
	glTranslatef(0, 0, fZoomInOut);

	glPushMatrix(); //Save
	glTranslatef(0, -210, 0);
	vDrawSnow();
	glPopMatrix();

	glPushMatrix(); //Save
	vLight1();

	if (bLight[0] == true){
		glEnable(GL_LIGHT0);
	}
	else{
		glDisable(GL_LIGHT0);
	}

	glPushMatrix(); //Save
	glTranslatef(-posX, 100, -posZ);
	vLightCircle();
	glPopMatrix();

	glPopMatrix();



	glPushMatrix(); //Save
	//vLine();
	glPopMatrix();




	glPushMatrix(); //Save
	vGround();
	glPopMatrix();



	glPushMatrix(); //Save
	glTranslatef(0, -210, 0);
	vPyramid();
	glPopMatrix();



	glPushMatrix(); //Save
	glTranslatef(0, -75, 0);
	glPushMatrix(); //Save
	glRotated(fEarth, 0, 1.0, 0);
	glTranslatef(100, 0, 0);
	vEarth();
	glPushMatrix(); //Save
	glRotated(fMoon, 0, 1.0, 0);
	glTranslatef(50, 0, 0);
	vMoon();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();






	glPopMatrix();



	//glFlush(); // 화면에 출력하기
	glutSwapBuffers();     // 화면에 출력하기
}

void TimerFunction(int value){
	switch (value){

	case 0:
		fEarth += 3.0;
		fMoon += 3.0;
		if (i360 >= 360){
			i360 = 0;
		}
		posX += 3 * cos(i360*(3.14 / 180));
		posZ += 3 * sin(i360 * (3.14 / 180));
		i360 += 1;
		glutTimerFunc(10, TimerFunction, 0); // 타이머함수 재 설정
		break;

	case 1:
		for (int i = 0; i < 100; ++i){
			if (tSnow[i].y < 0)
				tSnow[i].y = rand() % 600;
			else
				tSnow[i].y -= tSnow[i].dropSpeed;
		}
		glutTimerFunc(10, TimerFunction, 1); // 타이머함수 재 설정
		break;

	case 2:

		fZoomInOut += 10;
		if (fZoomInOut == 10){
			glutTimerFunc(10, TimerFunction, 3); // 타이머함수 재 설정
		}
		else{
			glutTimerFunc(10, TimerFunction, 2); // 타이머함수 재 설정
		}
		break;

	case 3:
		fMapB += 3.0;

		if (fMapB >= 1080){
			fMapB = 0.0;
			glutTimerFunc(10, TimerFunction, 4); // 타이머함수 재 설정
		}
		else{
			glutTimerFunc(10, TimerFunction, 3); // 타이머함수 재 설정
		}
		break;

	case 4:
		fZoomInOut -= 10;
		if (fZoomInOut == -180){
		}
		else{
			glutTimerFunc(10, TimerFunction, 4); // 타이머함수 재 설정
		}
		break;


	}
	glutPostRedisplay(); // 화면 재 출력
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == '`'){
		glutTimerFunc(10, TimerFunction, 2); // 타이머함수 재 설정
	}


	if (key == '+'){
		fView += 3.0;
	}
	else if (key == '-'){
		fView -= 3.0;
	}

	if (key == '1'){
		int ikey = key - 49;
		if (bLight[ikey] == true){
			bLight[ikey] = false;
		}
		else{
			bLight[ikey] = true;
		}
	}

	if (key == 'a'){
		fAmbient += 0.3;
	}
	else if (key == 'A'){
		fAmbient -= 0.3;
	}

	if (key == 'd'){
		fDiffuse += 0.3;
	}
	else if (key == 'D'){
		fDiffuse -= 0.3;
	}

	if (key == 's'){
		fSpecular += 0.3;
	}
	else if (key == 'S'){
		fSpecular -= 0.3;
	}

	if (key == 'r'){
		vMapY += 3.0;
	}

	for (int i = 0; i < 4; ++i){
		printf("bLight[%d] : %d\n", i, bLight[i]);
	}
	printf("\n");

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

void vPyramid(){
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_TRIANGLES);	//앞
	glNormal3f(0.0, 1200, -6000);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0, 150.0, 0);   //1
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(20, 0, 30);   //2
	glTexCoord2d(0.5f, 1.0f);
	glVertex3f(-20, 0, 30);   //3
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_TRIANGLES);	// 뒤
	glNormal3f(0, 1200, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0, 150.0, 0);   //1
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-20, 0, -30);   //2
	glTexCoord2d(0.5f, 1.0f);
	glVertex3f(20, 0, -30);   //3
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_TRIANGLES);	//옆
	glNormal3f(9000, -1200, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0, 150.0, 0);   //1
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(20, 0, 30);   //2
	glTexCoord2d(0.5f, 1.0f);
	glVertex3f(20, 0, -30);   //3
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_TRIANGLES);	//옆
	glNormal3f(9000, 1200, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0, 150.0, 0);   //1
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-20, 0, 30);   //3
	glTexCoord2d(0.5f, 1.0f);
	glVertex3f(-20, 0, -30);   //2
	glEnd();
}

void vEarth(){
	// 자동 매핑 설정
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	// 구 매핑
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(15, 20, 10);		//지구

	// 자동 매핑 해제
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void vMoon(){
	// 자동 매핑 설정
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	// 구 매핑
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(7, 20, 10);		//지구

	// 자동 매핑 해제
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void vLightCircle(){
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(5, 20, 10);
}

void vLight1(){
	GLfloat lightpos[] = { -posX, -100, -posZ, 1 };
	GLfloat ambientLight[] = { fAmbient, fAmbient, fAmbient, 1.0f };       // 흰색 주변광
	GLfloat DiffuseLight[] = { fDiffuse, fDiffuse, fDiffuse, 1.0f };
	GLfloat SpecularLight[] = { fSpecular, fSpecular, fSpecular, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
}

void vDrawSnow(){
	for (int i = 0; i < 100; ++i){
		glPushMatrix();
		glTranslatef(tSnow[i].x, tSnow[i].y, tSnow[i].z);
		glColor3f(tSnow[i].color[0], tSnow[i].color[1], tSnow[i].color[2]);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
}


void vGround(){
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-250, -200, 250);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(250, -200, 250);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(250, -200, -250);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-250, -200, -250);
	glEnd();
}


GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
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
