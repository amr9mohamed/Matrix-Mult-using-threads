#include <stdio.h>
#include <stdlib.h>
#include <string.h>
double**A,**B,**C;
int nA,mA,nB,mB,nC,mC;
void ScanFile(FILE *fp,char arr);//Scan File For Comparison
int Equal(double a,double b,double c);//Compare 3 elements
int main(int argc, char *argv[])
{
  
	int nomOfErrors=0;	
	FILE *f1, *f2, *f3;
  	f1 = fopen("C1","r");
  	f2 = fopen("C2","r");
	f3 = fopen("C3","r");
	int i,j;
        //ScanArrayA();
  	ScanFile(f1,'1'); 
  	printf("done scanning from C1\n");
  	//ScanArrayB();
  	ScanFile(f2,'2');
  	printf("done scanning from C2\n");
	//ScanArrayC();	
	ScanFile(f3,'3');
  	printf("done scanning from C3\n");
	for(i=0;i<nA;i++)
	{
		for(j=0;j<mA;j++)
		{
			if(!Equal(A[i][j],B[i][j],C[i][j]))
			{
				
				nomOfErrors++;
			}
		}
	}
  	if(nomOfErrors==0)
	{
		printf("Outputs are correct\n");
	}
	else
	{
		printf("Not Equal Arrays\n");
	}
  return 0;
}
void ScanFile(FILE *fp,char arr)
{
	char ch;
	int rows = 0, columns = 0, temp = 0;
	while(!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == ' ' && !rows)
		{
			columns++;
		}
		else if (ch == ' ' && rows)
		{
			temp++;
		}
		else if (ch == '\n')
		{
			if (!rows)
			{
				columns++;
				temp = columns;
			}
			else if (rows)
			{
				if (++temp != columns)
				{
					printf("error in format\n");
					break;
				}
			}
			rows++;
			temp = 0;
		}
	}
	if (arr ==  '1')
	{
		nA = rows;
		mA = columns;
		A = (double**)malloc(rows*sizeof(double*));
		for (int i = 0; i < rows; ++i)
		{
			*(A+i) = (double*)malloc(columns*sizeof(double));
		}
		rewind(fp);//to return to the start of the file
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				fscanf(fp,"%lf ",&A[i][j]);
			}
		}
	}
	else if (arr == '2')
	{
		nB = rows;
		mB = columns;
		B = (double**)malloc(rows*sizeof(double*));
		for (int i = 0; i < rows; ++i)
		{
			*(B+i) = (double*)malloc(columns*sizeof(double));
		}
		rewind(fp);//to return to the start of the file
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				fscanf(fp,"%lf ",&B[i][j]);
			}
		}
	}
	else if (arr == '3')
	{
		nC = rows;
		mC = columns;
		C = (double**)malloc(rows*sizeof(double*));
		for (int i = 0; i < rows; ++i)
		{
			*(C+i) = (double*)malloc(columns*sizeof(double));
		}
		rewind(fp);//to return to the start of the file
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				fscanf(fp,"%lf ",&C[i][j]);
			}
		}
	}
	fclose(fp);
}
int Equal(double a,double b,double c)
{
	if(a!=b)
	{
		return 0;
	}
	if(a!=c)
	{
		return 0;
	}
	if(b!=c)
	{
		return 0;
	}
	
	return 1;	
}
