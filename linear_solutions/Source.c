/* Nitai Dan
   207379132*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


double parsing(char* equation, char* temp, char coef, int length);

char order(char* equation, int length, int* col);

void space_handler(char* equation, int length);

void cut(char* equation, int length, char coef);

double determinent(double** mtrx, int num);

double cramer(double** mtrx, double* sol, int num, int col);

int main() {
	int num, i, j, col = 0;
	double** mtrx, * x, * b;
	double det;
	char** equ, *temp;
	char coef;

	printf_s("Number of equations (1-3): ");
	scanf_s("%d", &num);
	getchar();


	// Create dynamic array
	mtrx = malloc(sizeof(double*) * num);
	for (i = 0;i < num;i++)
		mtrx[i] = malloc(sizeof(double) * num);

	for (i = 0;i < num;i++)
		for (j = 0;j < num;j++)
			mtrx[i][j] = 0;

	equ = malloc(sizeof(char*) * num);
	if (equ)
	{
		for (i = 0;i < num;i++)
			equ[i] = malloc(sizeof(char) * 81);
	}

	x = malloc(sizeof(double) * num);
	b = malloc(sizeof(double) * num);
	temp = malloc(sizeof(char*) * 81);


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
			space_handler(equ[i], strlen(equ[i]));
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
					mtrx[i][col] = parsing(equ[i], temp, coef, strlen(equ[i]));
				}

				cut(equ[i], strlen(equ[i]), coef);
			}
			coef = order(equ[i], strlen(equ[i]), &col);
			if (coef == '=')
			{
				b[i] = parsing(equ[i], temp, coef, strlen(equ[i]));
			}
		}
	}


	//Using Cramer's rule to get the solution vector

	det = determinent(mtrx, num);

	//Print Matrix
	printf_s("\nMatrix A = \n");
	for (i = 0;i < num;i++) {
		//putchar('\t');
		for (j = 0;j < num;j++) {
			printf_s("\t%.2lf ", mtrx[i][j]);
		}
		printf_s("\n");
	}

	printf_s("\nMatrix A determinant = %.2lf\n", det);

	printf_s("\nVector B = \n");
	for (i = 0; i < num; i++)
	{
		printf_s("\t%.2lf\n", b[i]);
	}

	if (det != 0) {
		printf_s("\nVector X = ");
		for (i = 0; i < num; i++)
		{
			x[i] = cramer(mtrx, b, num, i);
			if (i == 0)
				printf_s("\n\tx = %.2lf", x[i]);
			if (i == 1)
				printf_s("\n\ty = %.2lf", x[i]);
			if (i == 2)
				printf_s("\n\tz = %.2lf", x[i]);
		}
	}

	if (det == 0)
		printf_s("\nThere is no single solution for that system of equations.");

	printf_s("\nGoodbye.\n");

	for (i = 0;i < num;i++)
		free(mtrx[i]);
	free(mtrx);

	//for (i = 0;i < num;i++)
	//	free(equ[i]);
	free(equ);
	free(temp);
	free(x);
	free(b);


	return 0;
}

//cutting the eaquation to find the coefficient

double parsing(char* equation,char *temp, char coef, int length) {
	double co = 0.0;
	int i = 0;
	char str[81];
	char* dex;
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


	return co;
}


// Finding the first variable x,y,z in the equation to cut the string for, and return the correct variable column #

char order(char* equation, int length, int* col) {
	int i;
	char coef = '\0';

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

	return coef;
}


// shortening the equation according to the variable
void cut(char* equation, int length, char coef) {
	int j, i = 0;
	char* dex;


	dex = strchr(equation, '*'); //Deleting astrix and jointing the coeficient to the variable
	while (dex != NULL)
	{
		equation[dex - equation] = ' ';
		dex = strchr(dex + 1, '*');
	}

	dex = strchr(equation, coef);

	while (i < dex - equation + 1) {
		equation[i] = ' ';
		i++;
		if (equation[i] == '=')
			break;
	}
}



//calculating the determinent
double determinent(double** mtrx, int num) {
	double det;
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
double cramer(double** mtrx, double* sol, int num, int col) {
	int i, j;
	double detmp, det, value;
	double** tmpmtrx;

	tmpmtrx = malloc(sizeof(double*) * num);
	for (i = 0;i < num;i++)
		tmpmtrx[i] = malloc(sizeof(double) * num);

	//Print Matrix
	for (i = 0;i < num;i++) {
		for (j = 0;j < num;j++) {
			tmpmtrx[i][j] = mtrx[i][j];
		}
	}

	for (i = 0; i < num; i++)
	{
		tmpmtrx[i][col] = sol[i];
	}
	det = determinent(mtrx, num);
	detmp = determinent(tmpmtrx, num);

	value = detmp / det;

	return value;
}


//Narrowing down all of the spaces
void space_handler(char* equation, int length) {
	char* dex;
	int i;

	dex = strchr(equation, ' ');
	while (dex != NULL)
	{
		for (i = dex - equation; i < length; i++)
		{
			equation[i] = equation[i + 1];
		}
		equation[i + 1] = '\0';
		dex = strchr(dex, ' ');
	}
}