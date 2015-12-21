#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정


	int isX = 0, isY = 50;

	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
	
	for (int i = 0; i < 6; ++i){
		if (i % 2 == 0){
			glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // 그리기 색을 'Blue' 으로 지정
			glRectf(0, isX, 50, isY); // 사각형 그리기 (x1, y1, x2, y2)
			isX += 50, isY += 50;
		}
		else{
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // 그리기 색을 'Green' 으로 지정
			glRectf(0, isX, 50, isY); // 사각형 그리기 (x1, y1, x2, y2)
			isX += 50, isY += 50;
		}
	}
	
	isX = 50, isY = 100;
	int isXT = 0, isYT = 50, isColor = 0;

	for (int j = 0; j < 6; ++j){
		for (int i = 0; i < 7; ++i){
			if (i % 2 == 0){
				if (isColor % 2 == 0){
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // 그리기 색을 'Green' 으로 지정
				}
				else{
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // 그리기 색을 'Blue' 으로 지정
				}
				glRectf(isX, isXT, isY, isYT); // 사각형 그리기 (x1, y1, x2, y2)
				isX += 50, isY += 50;
			}
			else{
				if (isColor % 2 == 0){
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // 그리기 색을 'Blue' 으로 지정
				}
				else{
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // 그리기 색을 'Green' 으로 지정
				}
				glRectf(isX, isXT, isY, isYT); // 사각형 그리기 (x1, y1, x2, y2)
				isX += 50, isY += 50;
			}
		}
		isXT += 50, isYT += 50;
		isX = 50, isY = 100;
		isColor += 1;
	}

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0, 400.0, 0, 300.0, -1.0, 1.0);
}