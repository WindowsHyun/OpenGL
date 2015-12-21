#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int isNum;
	int *isData;
	int isTemp;
	srand((unsigned int)time(NULL));
	printf("Input the Numver : ");
	scanf_s("%d", &isNum);
	isData = (int *)malloc(sizeof(int)*isNum);

	printf("List is : ");
	for (int i = 0; i < isNum; ++i){
	esc:
		isData[i] = rand() % isNum+1;

		for (int j = 0; j < i; ++j){
			if (isData[j] == isData[i]){
				goto esc;
			}
		}
		printf("%d ", isData[i]);
	}

	//-------------------------------------------------------
	//정렬 코드
	for (int i = 0; i < isNum - 1; i++){
		for (int j = 0; j<isNum - 1 - i; j++){
			if (isData[j]>isData[j + 1])
			{
				isTemp = isData[j];
				isData[j] = isData[j + 1];
				isData[j + 1] = isTemp;
			}
		}
	}
	//-------------------------------------------------------
	printf("\n\nascending order : ");
	for (int i = 0; i < isNum; ++i){
		printf("%d ", isData[i]);
	}
	//-------------------------------------------------------
	//정렬 코드
	for (int i = 0; i < isNum - 1; i++){
		for (int j = 0; j<isNum - 1 - i; j++){
			if (isData[j]<isData[j + 1])
			{
				isTemp = isData[j];
				isData[j] = isData[j + 1];
				isData[j + 1] = isTemp;
			}
		}
	}
	//-------------------------------------------------------
	printf("\n\ndescending order : ");
	for (int i = 0; i < isNum; ++i){
		printf("%d ", isData[i]);
	}

	printf("\n");

}