#include <stdio.h>
#include <string.h>
#include <stdlib.h>


float parsing(char* equation, char coef, int length);

char order(char* equation, int length);

void cut(char* equation, int length, char coef);

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

	if (mtrx && equ)
	{
		for (i = 0;i < num; i++) {
			for (j = 0; j < num; j++)
			{
				coef = order(equ[i], strlen(equ[i]));
				mtrx[i][j] = parsing(equ[i], coef, strlen(equ[i]));
				cut(equ[i], strlen(equ[i]), coef);
			}
		}
	}


	for (i = 0; i < num; i++)
	{
		//printf("%s\n", equ[i]);
		for ( j = 0; j < num; j++)
		{
			printf("%.2f\n", mtrx[i][j]);
		}
	}

	//// init array
	//for (i = 0;i < num;i++)
	//	for (j = 0;j < num;j++)
	//		mtrx[i][j] = 0;
	//puts("");
	for (i = 0;i < num;i++) {
		for (j = 0;j < num;j++) {
//			mtrx[i][j] = i + j;
			printf_s("%.2f ", mtrx[i][j]);
		}
		printf_s("\n");
	}	



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

	co = atof(temp);


	//free(temp);
	return co;
}


char order(char* equation, int length) {
	int i;
	char coef ='x';
	char* temp;

	temp = malloc(sizeof(char*) * length);

	strcpy_s(temp ,sizeof(char*)*length, equation);
	for (size_t i = 0; i < length; i++)
	{
		if (temp[i] == 'x' || temp[i] == 'y' || temp[i] == 'z') {
			coef = temp[i];
		}

	}

	free(temp);
	return coef;
}



void cut(char* equation, int length, char coef) {
	int j,i = 0;
	char* dex;

	for (i = 0; i < length; i++)
	{
		if (equation[i] == coef);
		{
			printf("\n***%c***\n", equation[i+1]);
			for (j = 0; equation[i]!='\0' ; j++) {
				equation[j] = equation[i+2];
				i++;
			}
			equation[i + 1] = '\0';
		}
	}


	//puts(equation[dex-equation]);

	//equation[i + 1] = '\0';

}