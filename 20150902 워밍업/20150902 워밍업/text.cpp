#include<iostream>
#include <cmath>
using namespace std;
#define SIZE 3

void add(int vector1[SIZE], int vector2[SIZE]); //벡터 합
int main()
{
	int vector1[SIZE];
	int vector2[SIZE];
	int vectorplus1;
	int vectorplus2;
	int vectorplus3;
	int vectormi1;
	int vectormi2;
	int vectormi3;
	char ch;
	cout << "input vector1의 1번째 값 입력 "; cin >> vector1[0];
	cout << "input vector1의 2번째 값 입력 "; cin >> vector1[1];
	cout << "input vector1의 3번째 값 입력 "; cin >> vector1[2];
	cout << "input vector2의 1번째 값 입력 "; cin >> vector2[0];
	cout << "input vector2의 2번째 값 입력 "; cin >> vector2[1];
	cout << "input vector2의 3번째 값 입력 "; cin >> vector2[2];
	while (1)
	{
		cout << "+: 두 벡터의 합" << endl << "-: 두 벡터의 차" << endl
			<< "d: 두 벡터의 내적과 두 벡터의 사잇각(코사인 값으로 출력)" << endl
			<< "c 두 벡터의 외적" << endl << "l: 두 벡터의 각각의 크기" << endl;



		cout << "vector1 : <" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << endl;
		cout << "vector2 : <" << vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">" << endl;
		cout << "선택 : "; cin >> ch;
		if (ch == '+')
		{
			vectorplus1 = vector1[0] + vector2[0];
			vectorplus2 = vector1[1] + vector2[1];
			vectorplus3 = vector1[2] + vector2[2];
			cout << "+: <" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << " + " << "<"
				<< vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">"
				<< " = " << "<" << vectorplus1 << ", " << vectorplus2 << ", " << vectorplus3 << "> " << endl;
		}
		else if (ch == '-')
		{
			vectormi1 = vector1[0] - vector2[0];
			vectormi2 = vector1[1] - vector2[1];
			vectormi3 = vector1[2] - vector2[2];
			cout << "-: <" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << " - " << "<"
				<< vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">"
				<< " = " << "<" << vectormi1 << ", " << vectormi2 << ", " << vectormi3 << "> " << endl;
		}
		else if (ch == 'd')
		{
			int inner = 0;
			double Root1;
			double Root2;
			double a = 0;
			double b = 0;
			double cosain;
			for (int i = 0; i < SIZE; ++i)
			{
				inner = inner + vector1[i] * vector2[i];
			}
			cout << "내적: " << inner << ", ";

			for (int i = 0; i < SIZE; ++i)
			{
				a = a + vector1[i];
				b = b + vector2[i];
			}
			Root1 = sqrt(a);
			Root2 = sqrt(b);

			cosain = cos(inner / Root1*Root2);

			cout << "cos =  " << cosain << endl;

		}
		else if (ch == 'c')
		{
			int temp1;
			int temp2;
			int temp3;
			temp1 = vector1[1] * vector2[2] - vector1[2] * vector2[1];
			temp2 = -(vector1[0] * vector2[2] - vector1[2] * vector2[0]);
			temp3 = vector1[0] * vector2[1] - vector1[1] * vector2[0];

			cout << "c: <" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << " x " << "<"
				<< vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">"
				<< " = " << "<" << temp1 << ", " << temp2 << ", " << temp3 << "> " << endl;

		}
		else if (ch == 'l')
		{
			double root1;
			double root2;

			root1 = sqrt(vector1[0] * vector1[0] + vector1[1] * vector1[1] + vector1[2] * vector1[2]);
			root2 = sqrt(vector2[0] * vector2[0] + vector2[1] * vector2[1] + vector2[2] * vector2[2]);

			cout << "l: root<" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << " = " << "root"
				<< "<" << root1 << ">" << "root<" << vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">"
				<< " = " << "root" << "<" << root2 << "> " << endl;

		}

	}
}

