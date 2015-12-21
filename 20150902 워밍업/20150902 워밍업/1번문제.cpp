#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

int is3x3[3][3];
int is3x3Two[3][3];
int is3x3Result[3][3];
int is4x4[4][4];

int determinantResult = 0;

void input3x3();
void inputRand3x3();
void show3x3(int);
void pluse3x3();
void minus3x3();
void multiplication3x3();
void determinant3x3();
void is3x3To4x4();

int main(){
	int isNum;
	inputRand3x3();
	while (1){
		printf("0. 자동 행렬 생성\n");
		printf("1. 3x3 행렬 입력하기\n");
		printf("2. 행렬의 곱셈\n");
		printf("3. 행렬의 덧셈\n");
		printf("4, 행렬의 뺄셈\n");
		printf("5. 행렬식의 값\n");
		printf("6. 3x3 행렬을 4x4 행렬로 변환\n");
		printf("7. 3x3 행렬 확인하기\n");
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		if (isNum == 0){
			inputRand3x3();
		}
		else 	if (isNum == 1){
			input3x3();
		}
		else 	if (isNum == 2){
			multiplication3x3();
			show3x3(3);
		}
		else 	if (isNum == 3){
			pluse3x3();
			show3x3(3);
		}
		else 	if (isNum == 4){
			minus3x3();
			show3x3(3);
		}
		else 	if (isNum == 5){
			determinant3x3();
		}
		else 	if (isNum == 6){
			is3x3To4x4();
		}
		else if (isNum == 7){
			system("cls");
			show3x3(1);
			show3x3(2);
			show3x3(3);
			show3x3(4);
		}
		else{
			system("cls");
			printf("오류 : 입력값 오류..!\n\n");
		}
	}
}



void is3x3To4x4(){
	system("cls");
	int isNum;

	printf("1. A 행렬식 변환하기.\n");
	printf("2. B 행렬식 변환하기.\n");
	printf("3. R 행렬식 변환하기.\n");
	printf("Input Num : ");
	scanf_s("%d", &isNum);
	printf("\n");


	if (isNum == 1){
		printf("A를 3x3 에서 4x4로 변환 : \n");
		show3x3(1);
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				is4x4[i][j] = is3x3[i][j];
			}
		}
		is4x4[3][3] = 1;
		show3x3(4);
	}
	else if (isNum == 2){
		printf("B를 3x3 에서 4x4로 변환 : \n");
		show3x3(2);
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				is4x4[i][j] = is3x3Two[i][j];
			}
		}
		is4x4[3][3] = 1;
		show3x3(4);
	}
	else if (isNum == 3){
		printf("R를 3x3 에서 4x4로 변환 : \n");
		show3x3(3);
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				is4x4[i][j] = is3x3Result[i][j];
			}
		}
		is4x4[3][3] = 1;
		show3x3(4);
	}

}

void determinant3x3(){
	system("cls");
	int isNum;

	printf("1. A 행렬식 구하기.\n");
	printf("2. B 행렬식 구하기.\n");
	printf("3. R 행렬식 구하기.\n");
	printf("Input Num : ");
	scanf_s("%d", &isNum);
	printf("\n");

	if (isNum == 1){
		printf("A행렬식 : \n");
		show3x3(1);
		determinantResult = is3x3[0][0] * is3x3[1][1] * is3x3[2][2]
			+ is3x3[0][1] * is3x3[1][2] * is3x3[2][0]
			+ is3x3[0][2] * is3x3[1][0] * is3x3[2][1]
			- is3x3[0][0] * is3x3[1][2] * is3x3[2][1]
			- is3x3[0][1] * is3x3[1][0] * is3x3[2][2]
			- is3x3[0][2] * is3x3[1][1] * is3x3[2][0];
		printf("A행렬식 : %d\n\n\n", determinantResult);
	}
	else if (isNum == 2){
		printf("B행렬식 : \n");
		show3x3(2);
		determinantResult = is3x3Two[0][0] * is3x3Two[1][1] * is3x3Two[2][2]
			+ is3x3Two[0][1] * is3x3Two[1][2] * is3x3Two[2][0]
			+ is3x3Two[0][2] * is3x3Two[1][0] * is3x3Two[2][1]
			- is3x3Two[0][0] * is3x3Two[1][2] * is3x3Two[2][1]
			- is3x3Two[0][1] * is3x3Two[1][0] * is3x3Two[2][2]
			- is3x3Two[0][2] * is3x3Two[1][1] * is3x3Two[2][0];
		printf("A행렬식 : %d\n\n\n", determinantResult);
	}
	else if (isNum == 3){
		printf("R행렬식 : \n");
		show3x3(2);
		determinantResult = is3x3Result[0][0] * is3x3Result[1][1] * is3x3Result[2][2]
			+ is3x3Result[0][1] * is3x3Result[1][2] * is3x3Result[2][0]
			+ is3x3Result[0][2] * is3x3Result[1][0] * is3x3Result[2][1]
			- is3x3Result[0][0] * is3x3Result[1][2] * is3x3Result[2][1]
			- is3x3Result[0][1] * is3x3Result[1][0] * is3x3Result[2][2]
			- is3x3Result[0][2] * is3x3Result[1][1] * is3x3Result[2][0];
		printf("A행렬식 : %d\n\n\n", determinantResult);
	}

	
}

void pluse3x3(){
	system("cls");
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			is3x3Result[i][j] = is3x3[i][j] + is3x3Two[i][j];
			printf("%d + %d = %d\n", is3x3[i][j], is3x3Two[i][j], is3x3Result[i][j]);
		}
	}
}

void minus3x3(){
	system("cls");
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			is3x3Result[i][j] = is3x3[i][j] - is3x3Two[i][j];
			printf("%d - %d = %d\n", is3x3[i][j], is3x3Two[i][j], is3x3Result[i][j]);
		}
	}
}

void multiplication3x3(){
	system("cls");

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int h = 0; h < 3; h++){
				is3x3Result[i][j] += is3x3[i][h] * is3x3Two[h][j];
			}
		}
	}
}

void input3x3(){
	system("cls");
	printf("1. 3x3 행렬 A 입력하기\n");
	printf("1번째 열 자료를 입력해주세요 : \n");
	for (int i = 0; i < 3; ++i){
		printf("[0][%d] 값 : ", i);
		scanf_s("%d", &is3x3[0][i]);
	}
	printf("2번째 열 자료를 입력해주세요 : \n");
	for (int i = 0; i < 3; ++i){
		printf("[1][%d] 값 : ", i);
		scanf_s("%d", &is3x3[1][i]);
	}

	printf("3번째 열 자료를 입력해주세요 : \n");
	for (int i = 0; i < 3; ++i){
		printf("[2][%d] 값 : ", i);
		scanf_s("%d", &is3x3[2][i]);
	}

	printf("1. 3x3 행렬 B 입력하기\n");
	printf("1번째 열 자료를 입력해주세요 : \n");
	for (int i = 0; i < 3; ++i){
		printf("[0][%d] 값 : ", i);
		scanf_s("%d", &is3x3Two[0][i]);
	}
	printf("2번째 열 자료를 입력해주세요 : \n");
	for (int i = 0; i < 3; ++i){
		printf("[1][%d] 값 : ", i);
		scanf_s("%d", &is3x3Two[1][i]);
	}

	printf("3번째 열 자료를 입력해주세요 : \n");
	for (int i = 0; i < 3; ++i){
		printf("[2][%d] 값 : ", i);
		scanf_s("%d", &is3x3Two[2][i]);
	}

	printf("\n\n");
}

void inputRand3x3(){
	system("cls");
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			is3x3[i][j] = rand() % 9 + 1;
		}
	}

	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			is3x3Two[i][j] = rand() % 9 + 1;
		}
	}
	printf("Auto init..!\n\n");
}

void show3x3(int isNum){
	if (isNum == 1){
		printf("3x3 행렬 A 확인하기\n\n");
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				printf("%d ", is3x3[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
	else if (isNum == 2){
		printf("\n3x3 행렬 B 확인하기\n\n");
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				printf("%d ", is3x3Two[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
	else if (isNum == 3){
		printf("\n3x3 행렬 R 확인하기\n\n");
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				printf("%d ", is3x3Result[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
	else if (isNum == 4){
		printf("\n4x4 행렬 확인하기\n\n");
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				printf("%d ", is4x4[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
}