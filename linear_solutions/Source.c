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
	int i;
	char str[81];
	char * dex, *temp;

	temp = malloc(sizeof(char*) * length);
	strcpy_s(str, sizeof(str), equation);
	dex = strchr(str, coef);

	if (dex != NULL)
	{
		for (i = 0; i < length; i++)
		{
			if ((str[dex - str - i] > 47 && str[dex - str - i] < 58)/* || str[dex - str - i] == '.'*/)
			{
				temp[i] = str[dex - str - i];
				printf("\n%c\n", str[dex - str - i]);
			}
		}
		temp[i + 1] = '\0';
	}
	puts(str);
	printf("string %s\n lentgh: %d\n first char: %c\n", temp, strlen(temp), temp[0]);

	free(temp);
	return co;
}