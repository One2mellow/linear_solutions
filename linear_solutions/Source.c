#include <stdio.h>
#include <string.h>
#include <stdlib.h>


float parsing(char* equation, char coef, int length);

char order(char* equation, int length);

int main() {
	int num, i, j;
	float** mtrx, * x, * b;
	char** equ;
	char coef;

	printf_s("Number of equations (1-3): ");
	scanf_s("%d", &num);
	getchar();
	// Create dynamic array
	mtrx = malloc(sizeof(float*) * num);
	for (i = 0;i < num;i++)
		mtrx[i] = malloc(sizeof(float) * num);

	equ = malloc(sizeof(char*) * num);
	if (equ)
	{
		for (i = 0;i < num;i++)
			equ[i] = malloc(sizeof(char) * 81);
	}

	x = malloc(sizeof(float) * num);
	b = malloc(sizeof(float) * num);


	if (equ)
	{
		for (i = 0; i < num; i++) {
			printf_s("Enter equation %d: ", i + 1);
			gets_s(equ[i], 80);
		}
	}

	coef = order(equ[0], strlen(equ[0]));

	mtrx[0][0] = parsing(equ[0], coef, strlen(equ[0]));


	//// init array
	//for (i = 0;i < num;i++)
	//	for (j = 0;j < num;j++)
	//		mtrx[i][j] = 0;
	//puts("");
	//for (i = 0;i < num;i++) {
	//	for (j = 0;j < num;j++) {
	//		mtrx[i][j] = i + j;
	//		printf_s("%.2f ", mtrx[i][j]);
	//	}
	//	printf_s("\n");
	//}	



	for (i = 0;i < num;i++)
		free(mtrx[i]);
	free(mtrx);

	for (i = 0;i < num;i++)
		free(equ[i]);
	free(equ);

	free(x);
	free(b);


	return 0;
}


float parsing(char* equation, char coef, int length) {
	float co = 0.0;
	int i = 0;
	char str[81];
	char* dex, * temp;

	temp = malloc(sizeof(char*) * length);
	strcpy(str, equation);

	if (str[0] != '\0') {

		switch (coef)
		{
		case ' ':
			temp = strtok(str, " ");
			break;
		case 'x':
			temp = strtok(str, "x");
			break;
		case'y':
			temp = strtok(str, "y");
			break;
		case 'z':
			temp = strtok(str, "z");
			break;

		default:
			break;
		}
	}

	puts(temp);

	co = atof(temp);


	free(temp);
	return co;
}


char order(char* equation, int length) {
	int i;
	char coef;
	char* temp;

	temp = malloc(sizeof(char*) * length);

	strcpy(temp, equation);

	for (size_t i = 0; i < length; i++)
	{
		if (temp[i] == 'x' || temp[i] == 'y' || temp[i] == 'z') {
			coef = temp[i];
		}

	}

	free(temp);
	return coef;
}