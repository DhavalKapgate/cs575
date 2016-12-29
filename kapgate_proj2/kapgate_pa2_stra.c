#include<stdio.h>
#include<stdlib.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
int n;
int check_two(int n)
{
	int r;
	if(n==0)
		return 0;
	while(n!=1)
	{
		if(n%2!=0)
			return 0;
		n=n/2;
	}
	return 1;
}
void display(int n,int A[][n])
{
	int i,j;                                //counter for for loops that only initialize
        for(i=0;i<n;i++)
        {
                for(j=0;j<n;j++)
                {
                        printf("\t%d",A[i][j]);
                }
		printf("\n");
        }
	printf("\n");
}
void stra_matrix(int n,int A[][n],int B[][n],int C[][n])
{
	if(n==1)
	{C[0][0]=A[0][0]*B[0][0];}
	else
	{
		int a11[n/2][n/2],a12[n/2][n/2],a21[n/2][n/2],a22[n/2][n/2],b11[n/2][n/2],b12[n/2][n/2],b21[n/2][n/2],b22[n/2][n/2];
		int i,j;
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				a11[i][j]=A[i][j];
				b11[i][j]=B[i][j];

				a21[i][j]=A[i+n/2][j];
				b21[i][j]=B[i+n/2][j];

				a12[i][j]=A[i][j+n/2];
                	        b12[i][j]=B[i][j+n/2];

                	        a22[i][j]=A[i+n/2][j+n/2];
                        	b22[i][j]=B[i+n/2][j+n/2];
							}
		}
		//M1
		int m1_a[n/2][n/2],m1_b[n/2][n/2],m1[n/2][n/2];
		for(i=0;i<n/2;i++)
                {
                        for(j=0;j<n/2;j++)
                        {
                             	m1_a[i][j]=a11[i][j]+a22[i][j];
				m1_b[i][j]=b11[i][j]+b22[i][j];
				m1[i][j]=0;
                        }
                }
		stra_matrix(n/2,m1_a,m1_b,m1);
		//M2
		int m2_a[n/2][n/2],m2[n/2][n/2];
                for(i=0;i<n/2;i++)
                {
                        for(j=0;j<n/2;j++)
                        {
                                m2_a[i][j]=a21[i][j]+a22[i][j];
                                m2[i][j]=0;
                        }
                }
                stra_matrix(n/2,m2_a,b11,m2);
		//M3
		int m3_b[n/2][n/2],m3[n/2][n/2];
                for(i=0;i<n/2;i++)
                {
                        for(j=0;j<n/2;j++)
                        {
                                m3_b[i][j]=b12[i][j]-b22[i][j];
                                m3[i][j]=0;
                        }
                }
                stra_matrix(n/2,a11,m3_b,m3);
		//M4
		int m4_b[n/2][n/2],m4[n/2][n/2];
                for(i=0;i<n/2;i++)
                {
                        for(j=0;j<n/2;j++)
                        {
                                m4_b[i][j]=b21[i][j]-b11[i][j];
                                m4[i][j]=0;
                        }
                }
                stra_matrix(n/2,a22,m4_b,m4);
		//M5
		int m5_a[n/2][n/2],m5[n/2][n/2];
                for(i=0;i<n/2;i++)
                {
                        for(j=0;j<n/2;j++)
                        {
                                m5_a[i][j]=a11[i][j]+a12[i][j];
                                m5[i][j]=0;
                        }
                }
                stra_matrix(n/2,m5_a,b22,m5);
		//M6
		int m6_a[n/2][n/2],m6_b[n/2][n/2],m6[n/2][n/2];
                for(i=0;i<n/2;i++)
                {
                        for(j=0;j<n/2;j++)
                        {
                                m6_a[i][j]=a21[i][j]-a11[i][j];
                                m6_b[i][j]=b11[i][j]+b12[i][j];
                                m6[i][j]=0;
                        }
                }
                stra_matrix(n/2,m6_a,m6_b,m6);
		//M7
		int m7_a[n/2][n/2],m7_b[n/2][n/2],m7[n/2][n/2];
                for(i=0;i<n/2;i++)
                {
                        for(j=0;j<n/2;j++)
                        {
                                m7_a[i][j]=a12[i][j]-a22[i][j];
                                m7_b[i][j]=b21[i][j]+b22[i][j];
                                m7[i][j]=0;
                        }
                }
                stra_matrix(n/2,m7_a,m7_b,m7);
		//C1
		int c1[n/2][n/2],c2[n/2][n/2],c3[n/2][n/2],c4[n/2][n/2];
		for(i=0;i<n/2;i++)
                {
                        for(j=0;j<n/2;j++)
                        {
                                c1[i][j]=m1[i][j]+m4[i][j]-m5[i][j]+m7[i][j];
				c2[i][j]=m3[i][j]+m5[i][j];
				c3[i][j]=m2[i][j]+m4[i][j];
				c4[i][j]=m1[i][j]+m3[i][j]-m2[i][j]+m6[i][j];
                        }
                }
		for(i=0;i<n/2;i++)
			for(j=0;j<n/2;j++)
			{
				C[i][j]=c1[i][j];
				C[i+n/2][j]=c3[i][j];
				C[i][j+n/2]=c2[i][j];
				C[i+n/2][j+n/2]=c4[i][j];
			}
	}
}
void normal_mul(int n,int A[][n],int B[][n], int C[][n])
{
	int i,j,k;
	for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                        for(k=0;k<n;k++)
				C[i][j]+=A[i][k]*B[k][j];
	printf("Normal Multiplication:\n");
	display(n,C);
}
int main(int argc,char *argv[])
{
	srand(time(NULL));
	n=atoi(argv[1]);
	while(!check_two(n))
	{
		printf("Please RE-Enter the no of rows (in powers of 2) : ");
		scanf("%d",&n);
	}
	int A[n][n],B[n][n],C[n][n];
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			A[i][j]=(rand()%20)-10;
			B[i][j]=(rand()%20)-10;
			C[i][j]=0;
		}
	}
	printf("Matrix A:\n");
	display(n,A);
	printf("Matrix B :\n");
	display(n,B);
	stra_matrix(n,A,B,C);
	printf("Strassen\n");
	display(n,C);
	for(i=0;i<n;i++)
        {
                for(j=0;j<n;j++)
                {
                        C[i][j]=0;
                }
        }
	normal_mul(n,A,B,C);
	return 0;
}
