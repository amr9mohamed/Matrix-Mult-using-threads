#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define max_nom_threads 30000

double**A;
int nA,mA;
double**B;
int nB,mB;
double**C1;
double**C2;
double**C3;
int nC,mC;
struct element
{
	int i;//Row Index
	int j;//Column Index
};

struct row
{
	int i;//Row Index
};

void nonThreadedMatMult();//Non Threaded Matrix Multiplication Function

void *runnerthreadedMatMultPerElement(void *param);//Element-Wise Threads Calls This Function
void threadedMatMultPerElement();//Function To Handle The Element Wise Threads

void *runnerthreadedMatMultPerRow(void *param);//Row Wise Threads Call this Function
void threadedMatMultPerRow();//Function to Handle Row Wise Threads
//------------------------------------------------------------------------------------------------------------------------------
//Input From User Partition
void ScanArrayA();//Scan Input Array A from User
void ScanArrayB();//Scan Input Array B from user
void ScanFile(FILE*,char);//Scan File 
void RandomizeArrayA();
void RandomizeArrayB();
int  validateColumnARowBCorrespondency();//to validate that Nom of columns of A equal to Nom of Rows of B
//------------------------------------------------------------------------------------------------------------------------------
//Printing 2-D Arrays Partition
void PrintArrayA();//Print Array A
void PrintArrayB();//Print Array B
void PrintArrayC1();//Print output Array C1 -----> Output of non threaded matrixMult
void PrintArrayC2();//Print output Array C2 -----> Output of Element Wise threaded matrixMult
void PrintArrayC3();//Print output Array C3 -----> Output of Row Wise threaded matrixMult
void WriteFile(char arr[]);//Write Output To file
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//Dynamic Allocation Partition For Array C
void AllocateC();//memmoryAllocate Array C -----> Delegator Function to call Allocate C1 , C2 , C3
void AllocateC1();
void AllocateC2();
void AllocateC3();
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//Main Function
int main(int argc, char *argv[])
{
  int generalize;
  printf("please  choose Mode to test 1-Random Nom 2-Enter I/P  3-Scan From File\n");
  scanf("%d",&generalize);
  if(generalize==1)
  {
	RandomizeArrayA();	
	RandomizeArrayB();
  }
  else if(generalize == 2)
  {
  	ScanArrayA(); 
  	ScanArrayB();
  	PrintArrayA();
  	PrintArrayB();
  }
  else if(generalize==3)
  {
	FILE *f1, *f2;
  	f1 = fopen("A","r");
  	f2 = fopen("B","r");
        //ScanArrayA();
  	ScanFile(f1,'A'); 
  	printf("done scanning from file1\n");
  	//ScanArrayB();
  	ScanFile(f2,'B');
  	printf("done scanning from file2\n");
  }
  /*printf("nA is %d mA is %d\n",nA,mA );
  printf("nB is %d mB is %d\n",nB,mB );*/
  AllocateC();
  nonThreadedMatMult();
  printf("end of non threaded\n");
  WriteFile("C1");
  threadedMatMultPerElement();
  printf("end of element by element threading\n");
  WriteFile("C2");
  printf("begn of row threading\n");
  threadedMatMultPerRow();
  printf("end of row threaded\n");
  WriteFile("C3");
  return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------


void ScanArrayA()
{
	int i,j;
  	printf("Enter Nom of Rows of matrix A ");
  	scanf("%d",&nA);
  	printf("Enter Nom of Columns of matrix A ");
  	scanf("%d",&mA);
  	A  = (double **)malloc(sizeof(double *) * nA);
  	for(i=0;i<nA;i++)
  	{
		A[i] = (double *)malloc(sizeof(double) *mA);
  	}
 	printf("Please Enter Elements of Matrix A\n");
  	for(i=0;i<nA;i++)
  	{
		for(j=0;j<mA;j++)
		{
			printf("Enter Element  A%d%d: ",i+1,j+1);
			scanf("%lf",&A[i][j]);
		}
  	}
}

int  validateColumnARowBCorrespondency()
{
	if(mA==nB)
	{
		return 1;
	}
	return 0;
}

void ScanArrayB()
{
	int i,j;
  	printf("Enter Nom of Rows of matrix B ");
  	scanf("%d",&nB);
	while(!validateColumnARowBCorrespondency())  	
	{
		printf("Error Please Enter Nom of Rows of matrix B Again ");
  		scanf("%d",&nB);	
	}
	printf("Enter Nom of Columns of matrix B ");
  	scanf("%d",&mB);
  	B  = (double **)malloc(sizeof(double *) * nB);
  	for(i=0;i<nB;i++)
  	{
		B[i] = (double *)malloc(sizeof(double) *mB);
  	}
 	printf("Please Enter Elements of Matrix B\n");
  	for(i=0;i<nB;i++)
  	{
		for(j=0;j<mB;j++)
		{
			printf("Enter Element  B%d%d: ",i+1,j+1);
			scanf("%lf",&B[i][j]);
		}
  	}
}

void RandomizeArrayB()
{
	int i,j;
  	printf("Enter Nom of Rows of matrix B ");
  	scanf("%d",&nB);
	while(!validateColumnARowBCorrespondency())  	
	{
		printf("Error Please Enter Nom of Rows of matrix B Again ");
  		scanf("%d",&nB);	
	}
	printf("Enter Nom of Columns of matrix B ");
  	scanf("%d",&mB);
  	B  = (double **)malloc(sizeof(double *) * nB);
  	for(i=0;i<nB;i++)
  	{
		B[i] = (double *)malloc(sizeof(double) *mB);
  	}
  	for(i=0;i<nB;i++)
  	{
		for(j=0;j<mB;j++)
		{
			B[i][j]=i+j;
		}
  	}
}

void RandomizeArrayA()
{
  	int i,j;
	printf("Enter Nom of Rows of matrix A ");
  	scanf("%d",&nA);
  	printf("Enter Nom of Columns of matrix A ");
  	scanf("%d",&mA);
  	A  = (double **)malloc(sizeof(double *) * nA);
  	for(i=0;i<nA;i++)
  	{
		A[i] = (double *)malloc(sizeof(double) *mA);
  	}
  	for(i=0;i<nA;i++)
  	{
		for(j=0;j<mA;j++)
		{
			A[i][j]=i+j;
		}
  	}
}

void PrintArrayA()
{
	int i,j;
	printf("Array A Elements\n");
	for(i=0;i<nA;i++)
	{
		for(j=0;j<mA;j++)
			{
				printf("%lf\t",A[i][j]);
			}
		printf("\n");
	}
}

void PrintArrayB()
{
	int i,j;
	printf("Array B Elements\n");
	for(i=0;i<nB;i++)
	{
		for(j=0;j<mB;j++)
			{
				printf("%lf\t",B[i][j]);
			}
		printf("\n");
	}
}

void PrintArrayC1()
{
	int i,j;
	printf("Array C1 Elements\n");
	for(i=0;i<nC;i++)
	{
		for(j=0;j<mC;j++)
			{
				printf("%lf\t",C1[i][j]);
			}
		printf("\n");
	}
}

void PrintArrayC2()
{
	int i,j;
	printf("Array C2 Elements\n");
	for(i=0;i<nC;i++)
	{
		for(j=0;j<mC;j++)
			{
				printf("%lf\t",C2[i][j]);
			}
		printf("\n");
	}
}

void PrintArrayC3()
{
	int i,j;
	printf("Array C3 Elements\n");
	for(i=0;i<nC;i++)
	{
		for(j=0;j<mC;j++)
			{
				printf("%lf\t",C3[i][j]);
			}
		printf("\n");
	}
}

void AllocateC1()
{
	int i;
	C1  = (double **)malloc(sizeof(double *) * nC);
  	for(i=0;i<nC;i++)
  	{
		C1[i] = (double *)malloc(sizeof(double) *mC);
  	}
}

void AllocateC2()
{
	int i;
	C2  = (double **)malloc(sizeof(double *) * nC);
  	for(i=0;i<nC;i++)
  	{
		C2[i] = (double *)malloc(sizeof(double) *mC);
  	}
}

void AllocateC3()
{
	int i;	
	C3  = (double **)malloc(sizeof(double *) * nC);
  	for(i=0;i<nC;i++)
  	{
		C3[i] = (double *)malloc(sizeof(double) *mC);
  	}
}

void AllocateC()
{
	nC=nA;
	mC=mB;	
	AllocateC1();
	AllocateC2();
	AllocateC3();
}

void nonThreadedMatMult()
{
	int i,j,k;
	double start = (double)(time(NULL)/1.0);	
	for(i=0;i<nA;i++)
	{	
		for(j=0;j<mB;j++)
		{
			C1[i][j]=0;
			for(k=0;k<mA;k++)
			{				
				C1[i][j]+=(A[i][k]*B[k][j]);
			}
		}
	}
	double end = (double)(time(NULL)/1.0);
	double exec_time = (end - start);//CLOCKS_PER_SEC;
	printf("Non threaded execution time is %lf\n",exec_time/1.0 );
	
}

void *runnerthreadedMatMultPerElement(void *param)
{	
	int i;	
	struct element *E = param;//The Structure That Holds Element position
	C2[E->i][E->j] = 0;	
	for(i=0;i<mA;i++)
	{
		C2[E->i][E->j] += (A[E->i][i]*B[i][E->j]);//Row Multiplied by Column and Assigning sum to the corresponding element in matrixC2
	}
	//Exit the thread
	free(param);
	pthread_exit(0); 
}

void threadedMatMultPerElement()//Function To Handle The Element Wise Threads
{
	int i,j,i2=0;
	pthread_t elements[max_nom_threads];
	double start = (double)time(NULL);
	int countelementthread=0;
	int nomdeallocs=0;
	for(i=0;i<nC;i++)
	{
		for(j=0;j<mC;j++)
		{
			if(countelementthread%max_nom_threads==0 && countelementthread!=0)
			{				
				while(i2<countelementthread)
				{
					pthread_join(elements[i2%max_nom_threads],NULL);//Joining nC*mC Threads
					i2++;
				}
				nomdeallocs++;
			}			
			//Assign Row and Column To produce an element for each thread
			struct element*E=(struct element*)malloc(sizeof(struct element));//Dynamically Allocating Element Position For Comming Thread
			E->i = i;
			E->j = j;
                        //printf("%d%d\n",i,j);
			//Creating Thread to pass element position in C as a parameter	
			pthread_attr_t attr;//set of thread attributes
			pthread_attr_init(&attr);//Get Default Attributes
			while(pthread_create(&elements[countelementthread%max_nom_threads],&attr,runnerthreadedMatMultPerElement,E))
				{printf("%d,%d\n",i,j);};//Create Thread C[i][j]
			countelementthread++;
			//free(E);	
		}

	}
		while(i2<countelementthread)
		{
			if(i2%max_nom_threads==0)
			{
				nomdeallocs++;
				//printf("%d\n",nomdeallocs);
			}			
			pthread_join(elements[i2%max_nom_threads],NULL);//Joining nC*mC Threads
			i2++;
		}
	double end = (double)time(NULL);
	double exec_time = (double)(end-start);
	printf("Total Number of Element Threads %d\n",countelementthread);
	printf("total Nom of deallocs %d \n",nomdeallocs);
	printf("thread per element execution time %lf\n",exec_time/1.0 );
	//PrintArrayC2();
}

void *runnerthreadedMatMultPerRow(void *param)//Row Wise Threads Call this Function
{
	int i,j;	
	struct row *R = param;//The Structure That Holds row position
	for(i=0;i<mB;i++)
	{
		C3[R->i][i]=0;		
		for(j=0;j<mA;j++)
		{
			C3[R->i][i]+=(A[R->i][j]*B[j][i]);//Row Multiplied by Column and Assigning sum to the corresponding element in 	matrixC2
		}
	}	
	//Exit the thread
	free(param);
	pthread_exit(0); 

}
void threadedMatMultPerRow()//Function to Handle Row Wise Threads
{

	int i;
	pthread_t rows[max_nom_threads];
	int countrowthread=0;
	int i2=0;
	double start = (double)(time(NULL)/1.0);
	for(i=0;i<nC;i++)
	{
		
		if(countrowthread%max_nom_threads==0 && countrowthread!=0)
		{
			while(i2<countrowthread)
			{
				pthread_join(rows[i2%max_nom_threads],NULL);//Joining nC Threads
				i2++;
			}
		}		
		//Assign Row and Column To produce an element for each thread
		struct row*R=(struct row*)malloc(sizeof(struct row));//Dynamically Allocating Element Position For Comming Thread
		R->i = i;
		//Creating Thread to pass element position in C as a parameter	
		pthread_attr_t attr;//set of thread attributes
		pthread_attr_init(&attr);//Get Default Attributes
		while(pthread_create(&rows[countrowthread%max_nom_threads],&attr,runnerthreadedMatMultPerRow,R))
			{printf("%d\n",i);};//Create Thread row[i]
		countrowthread++;
		//pthread_join(rows[i],NULL);//Joining nC Threads
		//free(R);
	}
	while(i2<countrowthread)
	{
		pthread_join(rows[i2%max_nom_threads],NULL);//Joining nC Threads
		i2++;
	}
	double end = (double)(time(NULL)/1.0);
	double exec_time = (end - start);//CLOCKS_PER_SEC;
	printf("Total Number of row Threads= %d\n",countrowthread);
	printf("thread per row execution time %lf\n",exec_time/1.0 );
	//PrintArrayC3();

}
void ScanFile(FILE *fp,char arr)
{
	char ch,ch2;
	int rows = 0, columns = 0, temp = 0;
	//int counter = 0;
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
					/*printf("temp is %d\n",temp);
					printf("row is %d\n",rows );*/
					return;
				}
			}
			//printf("%d\n",++counter);
			rows++;
			temp = 0;
		}
	}
	printf("number of rows is %d\n",rows);
	if (arr ==  'A')
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
				fscanf(fp,"%lf",&A[i][j]);
			}
		}
	}
	else if (arr == 'B')
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
				fscanf(fp,"%lf",&B[i][j]);
			}
		}
	}
	fclose(fp);
}
void WriteFile(char arr[])
{
	int i,j;	
	FILE *f1;
	if(strcmp(arr,"C1")==0)
	{
		f1 = fopen("C1","w");
		for(i=0;i<nC;i++)
		{
			for(j=0;j<mC;j++)
			{
				fprintf(f1,"%lf",C1[i][j]);
				if(j<mC-1)
				{				
				 	fprintf(f1," ");
				}
			}
			fprintf(f1,"\n");
		}
		printf("done writing in C1 File\n");
	}
	else if(strcmp(arr,"C2")==0)
  	
	{
		f1 = fopen("C2","w");
		for(i=0;i<nC;i++)
		{
			for(j=0;j<mC;j++)
			{
				fprintf(f1,"%lf",C2[i][j]);
				if(j<mC-1)
				{				
				 	fprintf(f1," ");
				}
			}
			fprintf(f1,"\n");
		}
		printf("done writing in C2 File\n");
	}
	else if(strcmp(arr,"C3")==0)
	{
		f1 = fopen("C3","w");
		for(i=0;i<nC;i++)
		{
			for(j=0;j<mC;j++)
			{
				fprintf(f1,"%lf",C3[i][j]);
				if(j<mC-1)
				{				
				 	fprintf(f1," ");
				}
			}
			fprintf(f1,"\n");
		}
		printf("done writing in C3 File\n");
	}
        
	fclose(f1);
}


