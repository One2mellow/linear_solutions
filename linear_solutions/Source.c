#include <stdio.h>
#include <string.h>
#include <stdlib.h>


float parsing(char* equation, char coef, int length);

char order(char* equation, int length, int* col);

void cut(char* equation, int length, char coef);

float determinent(float** mtrx, int num);

float cramer(float** mtrx, float* sol, int num, int col);

int main() {
	int num, i, j, col = 0;
	float** mtrx, * x, * b;
	float det;
	char** equ;
	char coef;

	printf_s("Number of equations (1-3): ");
	scanf_s("%d", &num);
	getchar();


	// Create dynamic array
	mtrx = malloc(sizeof(float*) * num);
	for (i = 0;i < num;i++)
		mtrx[i] = malloc(sizeof(float) * num);

	for (i = 0;i < num;i++)
		for (j = 0;j < num;j++)
			mtrx[i][j] = 0;

	equ = malloc(sizeof(char*) * num);
	if (equ)
	{
		for (i = 0;i < num;i++)
			equ[i] = malloc(sizeof(char) * 81);
	}

	x = malloc(sizeof(float) * num);
	b = malloc(sizeof(float) * num);


	// initiating vectors as 0
	for (i = 0;i < num; i++) {
		x[i] = 0;
		b[i] = 0;
	}


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
				coef = order(equ[i], strlen(equ[i]), &col);
				if (coef != '\0' && coef != '=')
				{
					mtrx[i][col] = parsing(equ[i], coef, strlen(equ[i]));
				}
				
				cut(equ[i], strlen(equ[i]), coef);
			}
			coef = order(equ[i], strlen(equ[i]), &col);
			//cut(equ[i], strlen(equ[i]), coef);
			if (coef == '=')
			{
				b[i] = parsing(equ[i], coef, strlen(equ[i]));
			}
		}
	}


	//Using Cramer's rule to get the solution vector
	printf_s("\n\nCRAMER'S RULE\n\n");
	for ( i = 0; i < num; i++)
	{
		x[i] = cramer(mtrx, b, num, i);
		printf_s("\n%.2f", x[i]);
	}
	det = determinent(mtrx, num);
	
	printf_s("\nDETERMINENT\n\t%.2f", det);

	putchar('\n');

	//Print Matrix
	printf_s("\nMATRIX\n");
	for (i = 0;i < num;i++) {
		for (j = 0;j < num;j++) {
			printf_s("%.2f ", mtrx[i][j]);
		}
		printf_s("\n");
	}

	printf_s("Solution vector\n");
	for ( i = 0; i < num; i++)
	{
		printf_s("%.2f\n", b[i]);
	}



	for (i = 0;i < num;i++)
		free(mtrx[i]);
	free(mtrx);

	//for (i = 0;i < num;i++)
	//	free(equ[i]);
	free(equ);

	free(x);
	free(b);


	return 0;
}

//cutting the eaquation to find the coefficient

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
		case '=':
			dex = strchr(str, '=');
			str[dex - str] = ' ';
			strcpy(temp, str);
			break;
		case '\0':
			return 0.0;
			break;
		default:
			break;
		}
	}


	co = atof(temp);


	//free(temp);
	return co;
}


// Finding the first variable x,y,z in the equation to cut the string for, and return the correct variable column #

char order(char* equation, int length, int* col) {
	int i;
	char coef = '\0';
	char* temp;

	//temp = malloc(sizeof(char*) * length);

	//strcpy_s(temp ,sizeof(char*)*length, equation);
	for (i = 0; i < length; i++)
	{
		if (equation[i] == 'x' || equation[i] == 'y' || equation[i] == 'z' || equation[i] == '=') {
			coef = equation[i];
			break;
		}
	}

	switch (coef)
	{
	case 'x':
		*col = 0;
		break;
	case 'y':
		*col = 1;
		break;
	case 'z':
		*col = 2;
		break;
	default:
		break;
	}

	//free(temp);
	return coef;
}


// shortening the equation according to the variable
void cut(char* equation, int length, char coef) {
	int j, i = 0;
	char* dex;

	dex = strchr(equation, coef);

	while (i < dex - equation + 1) {
		equation[i] = ' ';
		i++;
		if (equation[i] == '=')
			break;
	}
}



//calculating the determinent
float determinent(float** mtrx, int num) {
	float det;
	int i;

	if (num == 2)
	{
		det = mtrx[0][0] * mtrx[1][1] - mtrx[0][1] * mtrx[1][0];
	}
	else if (num == 3)
	{
		det = mtrx[0][0] * ((mtrx[1][1] * mtrx[2][2]) - (mtrx[2][1] * mtrx[1][2])) - mtrx[0][1] * (mtrx[1][0]
			* mtrx[2][2] - mtrx[2][0] * mtrx[1][2]) + mtrx[0][2] * (mtrx[1][0] * mtrx[2][1] - mtrx[2][0] * mtrx[1][1]);
	}
	else
	{
		det = mtrx[0][0];
	}

	return det;
}



//Cramer's rule
float cramer(float** mtrx, float* sol, int num, int col) {
	int i, j;
	float detmp, det, value;
	float** tmpmtrx;

	tmpmtrx = malloc(sizeof(float*) * num);
	for (i = 0;i < num;i++)
		tmpmtrx[i] = malloc(sizeof(float) * num);

	//Print Matrix
	for (i = 0;i < num;i++) {
		for (j = 0;j < num;j++) {
			tmpmtrx[i][j] = mtrx[i][j];
		}
	}

	for ( i = 0; i < num; i++)
	{
		tmpmtrx[i][col] = sol[i];
	}
	det = determinent(mtrx, num);
	detmp = determinent(tmpmtrx, num);

	value = detmp / det;

	return value;
}