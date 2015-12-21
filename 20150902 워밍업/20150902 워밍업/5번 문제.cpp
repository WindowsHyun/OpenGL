#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>

double isA[3];
double isB[3];
double isC[3];
double isD[3];

void isAutoRnad();
void isPutMake();
void isShow();

void isVector3();
void isVector4();

int main(){
	int isNum;
	isAutoRnad();
	while (1){
		printf("0. 자동 꼭지점 생성\n");
		printf("1. 수동 꼭지점 생성\n");
		printf("2. 입력된 값 확인하기.\n");
		printf("3. 4개의 꼭지점으로 구성되는 1개의 면의 방정식.\n");
		printf("4. 4개의 꼭지점으로 구성되는 4개의 선의 좌표와 길이.\n");
		printf("5. 4개의 꼭지점의 좌표값.\n");
		printf("Input Num : ");

		scanf_s("%d", &isNum);

		if (isNum == 0){
			isAutoRnad();
		}
		else if (isNum == 1){
			isPutMake();
		}
		else if (isNum == 2){
			system("cls");
			isShow();
		}
		else if (isNum == 3){

		}
		else if (isNum == 4){
			 isVector4();
		}
		else if (isNum == 5){
			system("cls");
			isShow();
		}


	}

}


void isVector3(){
	// sqrt(((x2 - x1)*(x2 - x1) + (y2-y1)*(y2-y1) +  (z2-z1)*(z2-z1)));

}

void isVector4(){
	system("cls");
	double isResult = 0;
	printf("4. 4개의 꼭지점으로 구성되는 4개의 선의 좌표와 길이.\n");
	printf("(");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isA[i]);
	}
	printf(") - (");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isB[i]);
	}
	isResult = sqrt(((isB[1] - isA[1])*(isB[1] - isA[1]) + (isB[2] - isA[2])*(isB[2] - isA[2]) + (isB[3] - isA[3])*(isB[3] - isA[3])));
	printf(") = %f\n\n", isResult);

	

}

void isShow(){
	printf("2. 입력된 값 확인하기.\n\n");
	printf("A 꼭지점 : \n");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isA[i]);
	}
	printf("\n\nB 꼭지점 : \n");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isB[i]);
	}

	printf("\n\nC 꼭지점 : \n");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isC[i]);
	}

	printf("\n\nD 꼭지점 : \n");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isD[i]);
	}
	printf("\n\n");
}

void isAutoRnad(){
	system("cls");
	printf("Auto init..!\n\n");
	for (int i = 0; i < 3; ++i){
		srand((unsigned int)time(NULL) + i);
		isA[i] = rand() % 2 + 1;
		isB[i] = rand() % 3 + 1;
		isC[i] = rand() % 4 + 1;
		isD[i] = rand() % 5 + 1;
	}

}

void isPutMake(){
	system("cls");
	int isNum;

	for (int i = 0; i < 3; ++i){
		printf("꼭지점 A의 %d번째 값 입력해주세요..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isA[i] = isNum;
	}

	for (int i = 0; i < 3; ++i){
		printf("꼭지점 B의 %d번째 값 입력해주세요..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isB[i] = isNum;
	}

	for (int i = 0; i < 3; ++i){
		printf("꼭지점 C의 %d번째 값 입력해주세요..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isC[i] = isNum;
	}

	for (int i = 0; i < 3; ++i){
		printf("꼭지점 D의 %d번째 값 입력해주세요..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isD[i] = isNum;
	}

}