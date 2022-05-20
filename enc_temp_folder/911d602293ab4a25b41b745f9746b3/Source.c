#include <stdio.h>
#include <string.h>
#include <stdlib.h>


float parsing(char* equation, char coef, int length);



int main() {
	int num,i,j;
	float** mtrx, *x,*b;
	char** equ;

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

	parsing(equ[0], 'x', strlen(equ[0]));

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
	float co=0.0;
	int i=0;
	char str[81];
	char* dex, * temp;

	temp = malloc(sizeof(char*) * length);
	strcpy(temp, equation);
	puts(temp);

	for (size_t i = 0; i < strlen(equation); i++) {
		str[i] = equation[i];
		// Access each char in the string
	}

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
			puts(temp);
			break;

		default:
			break;
		}
	}

	return co;
}