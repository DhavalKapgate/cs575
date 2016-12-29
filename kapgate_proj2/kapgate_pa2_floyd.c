#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc,char* argv[])
{
	FILE *fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("ERROR : INVALID FILENAME : QUITTING\n");
		exit(0);
	}
 
	char buff[255];
	fscanf(fp,"%s",buff);
	int n=0,i,j;
	for(i=0;i<strlen(buff);i++)
		if(buff[i]==',')
			n++;
	n++;				//so now we know there are n vertices/nodes
	int W[n][n],number=0,pos=0;

	for(i=0;i<n;i++)		//clearing all values in W
		for(j=0;j<n;j++)
			W[i][j]=0;

	char *value=strtok(buff,",");
	for(i=0;i<strlen(value);i++)
		W[0][0]=(10*W[0][0])+((int)value[i]-48);

	for(j=1;j<n;j++)
	{
		value=strtok(NULL,",");
		for(i=0;i<strlen(value);i++)
			if(!(i==0&&value[0]=='-'))
		             W[0][j]=(10*W[0][j])+((int)value[i]-48);
		if(value[0]=='-')
			W[0][j]=-W[0][j];
	}
	int k;
	for(k=1;k<n;k++)
	{
		fscanf(fp,"%s",buff);
		value=strtok(buff,",");
	        for(i=0;i<strlen(value);i++)
			 if(!(i==0&&value[0]=='-'))
	        	        W[k][0]=(10*W[k][0])+((int)value[i]-48);
		if(value[0]=='-')
                        W[k][j]=-W[k][j];

	        for(j=1;j<n;j++)
        	{
        	        value=strtok(NULL,",");
        	        for(i=0;i<strlen(value);i++)
				 if(!(i==0&&value[0]=='-'))
			                W[k][j]=(10*W[k][j])+((int)value[i]-48);
        		if(value[0]=='-')
                        W[k][j]=-W[k][j];
		}
	}
	printf("\n\n");

	//SINCE WE NOW HAVE THE ADJENCENCY MATRIX WE PERFORM FLOYDS ALGO
	printf("ADJENCENCY MATRIX:\n");
        for(j=0;j<n;j++)			//W Matrix
        {
                for(i=0;i<n;i++)
                	printf("%5d",W[j][i]);
                printf("\n");
        }
	int D[n][n];
	for(i=0;i<n;i++)			//D matrix
		for(j=0;j<n;j++)
			D[i][j]=W[i][j];
	int P[n][n];
        for(i=0;i<n;i++)                        //P matrix
                for(j=0;j<n;j++)
                        P[i][j]=0;
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{
				if(i==j&&D[i][j]!=0)//since diagonal element values should always be 0
							//(assuming a node doesnt have a edge to itself)
                                {
                                        printf("ERROR : INVALID GRAPH");
                                        exit(0);
                                }
				if(D[i][j]>(D[i][k]+D[k][j]))
				{
					D[i][j]=D[i][k]+D[k][j];
					if(i==j&&D[i][j]!=0)
					{
						if(D[i][j]<0)
							printf("ERROR : NEGATIVE CYCLE DETECTED : QUITTING\n");
						exit(EXIT_FAILURE);
					}
					P[i][j]=k+1;		//considering vertices/nodes start from 1
				}
			}
	printf("\nThe Distance matrix After applying Floyds Algo:\n");
	for(j=0;j<n;j++)                        //D Matrix
        {
                for(i=0;i<n;i++)
                	printf("%5d",D[j][i]);
                printf("\n");
        }
	printf("\nThe Path Matrix:\n");
	for(j=0;j<n;j++)                        //P Matrix
        {
                for(i=0;i<n;i++)
                        printf("%3d",P[j][i]);
                printf("\n");
        }
	fclose(fp);
	return 0;
}

