#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // 비트맵 파일 관렦 자료 저장


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);
void vMenuFunc(int value);


float fBingle = 0.0;
float fBingle2 = 0.0;
int iMmenu, imode;

int  iDepth, iCulling, iShading, iTop, iBottom;

bool bTop = true;
bool bBottom = true;
bool bDepth = false;
bool bCulling = false;
bool bShading = false;

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint texture_object[6];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);


void vLine();

void SetupRC(){
	glGenTextures(6, texture_object);

	// 1
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	pBytes = LoadDIBitmap("image/1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 2
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	pBytes = LoadDIBitmap("image/2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 3
	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	pBytes = LoadDIBitmap("image/3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 65, 63, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 4
	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	pBytes = LoadDIBitmap("image/4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 5
	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	pBytes = LoadDIBitmap("image/5.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 65, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 6
	glBindTexture(GL_TEXTURE_2D, texture_object[5]);
	pBytes = LoadDIBitmap("image/6.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 66, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}


void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);

	iDepth = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	iCulling = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 3);
	glutAddMenuEntry("Off", 4);
	iShading = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 5);
	glutAddMenuEntry("Off", 6);
	iTop = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 7);
	glutAddMenuEntry("Off", 8);
	iBottom = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 9);
	glutAddMenuEntry("Off", 10);

	iMmenu = glutCreateMenu(vMenuFunc);
	glutAddSubMenu("은면제거", iDepth);
	glutAddSubMenu("컬링", iCulling);
	glutAddSubMenu("쉐이딩", iShading);
	glutAddSubMenu("윗면", iTop);
	glutAddSubMenu("옆면", iBottom);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	SetupRC();
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 설정된 색으로 젂체를 칠하기


	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotatef(30, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);


	glPushMatrix(); //Save
	vLine();
	glPopMatrix();

	glPushMatrix(); //Save
	glRotated(fBingle, 0, 1.0, 0);
	glRotated(fBingle2, 1.0, 0, 0);


	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-100.0, 100.0, 100.0);   //1
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-100.0, -100.0, 100.0);   //2
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(100.0, -100.0, 100.0);   //3
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(100.0, 100.0, 100.0);   //4
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(100.0, 100.0, 100.0);   //4
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(100.0, -100.0, 100.0);   //3   
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(100.0, -100.0, -100.0);   //7
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(100.0, 100.0, -100.0);   //6
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-100.0, 100.0, -100.0);   //5
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(100.0, 100.0, -100.0);   //6
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(100.0, -100.0, -100.0);   //7
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-100.0, -100.0, -100.0);   //8
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-100.0, 100.0, 100.0);   //1
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-100.0, 100.0, -100.0);   //5
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-100.0, -100.0, -100.0);   //8   
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-100.0, -100.0, 100.0);   //2
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-100.0, -100.0, 100.0);   //2
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-100.0, -100.0, -100.0);   //8
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(100.0, -100.0, -100.0);   //7
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(100.0, -100.0, 100.0);   //3
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[5]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-100.0, 100.0, 100.0);  //1
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(100.0, 100.0, 100.0);   //4
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(100.0, 100.0, -100.0);   //6
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-100.0, 100.0, -100.0);   //5
	glEnd();


	glPopMatrix();

	glPopMatrix();
	//glFlush(); // 화면에 출력하기
	glutSwapBuffers();	// 화면에 출력하기
}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	fBingle -= 1.0;

	glutTimerFunc(50, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'c'){
		fBingle += 1.0;
	}
	if (key == 'v'){
		fBingle -= 1.0;
	}

	if (key == 'd'){
		fBingle2 += 1.0;
	}
	if (key == 'f'){
		fBingle2 -= 1.0;
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

void vMenuFunc(int iBt){
	switch (iBt){
	default:
	case 1:
		bDepth = true;
		break;
	case 2:
		bDepth = false;
		break;

	case 3:
		bCulling = true;
		break;
	case 4:
		bCulling = false;
		break;

	case 5:
		bShading = true;
		break;
	case 6:
		bShading = false;
		break;

	case 7:
		bTop = true;
		break;
	case 8:
		bTop = false;
		break;
	case 9:
		bBottom = true;
		break;
	case 10:
		bBottom = false;
		break;




	}
	glutPostRedisplay();
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