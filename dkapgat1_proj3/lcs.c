#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char* argv[])
{
	FILE *file=fopen(argv[1],"r");
	if(file==NULL)
	{
		printf("Invalid file\nABORT\n");
		exit(0);
	}
	char x[255],y[255];	//the 2 strings x and y
	fscanf(file,"%s\n%s",x,y);
	fclose(file);		//end of file operation

	printf("x=%s\ny=%s\n",x,y);
	//create and initialise c matrix for computing LCS
	int x_length=strlen(x),y_length=strlen(y);
	int c[x_length+1][y_length+1],i,j;
	//int lcs_length=0;
	char b[x_length+1][y_length+1];
	for(i=0;i<=y_length;i++)
	{
		c[0][i]=0;
		b[0][i]='E';	//E->end of backtrack
	}
	for(i=0;i<=x_length;i++)
	{
                c[i][0]=0;
		b[i][0]='E';	//E->end of backtrack
	}
	for(i=1;i<=x_length;i++)
		for(j=1;j<=y_length;j++)
		{
			if(x[i-1]==y[j-1])
			{
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]='D';//D->diagonal arrow
				//printf("D>> %c and %c\n",x[i-1],y[j-1]);
				//lcs_length++;
			}
			else
			{
				if(c[i-1][j]>=c[i][j-1])
				{
					c[i][j]=c[i-1][j];
					b[i][j]='U';//U->upward arrow
					//printf("U>> %c and %c\n",x[i-1],y[j-1]);
				}
				else
				{
					c[i][j]=c[i][j-1];
					b[i][j]='L';//L->left arrow
					//printf("L>> %c and %c\n",x[i-1],y[j-1]);
				}
			}
		}
/*	for(i=0;i<=x_length;i++)
	{
		for(j=0;j<=y_length;j++)
			printf("%d ",c[i][j]);
		printf("\n");
	}
	printf("\n    ");
	for(i=0;i<=x_length;i++)
		printf("%c ",y[i]);

*/	printf("\n");
/*	for(i=0;i<=x_length;i++)
        {
		if(i!=0)
			printf("%c ",x[i-1]);
		else
			printf("  ");
                for(j=0;j<=y_length;j++)
                        printf("%c ",b[i][j]);
                printf("\n");
        }*/
	int lcs_pos=c[x_length][y_length];
	if(lcs_pos!=0)
	{
		char lcs[lcs_pos];
		char current=b[x_length][y_length];

		i=x_length,j=y_length;
		//printf("%d %d %s\n",lcs_pos,i,x);
		while(current!='E')
		{
			if(current=='D')
			{
				lcs[lcs_pos-1]=x[i-1];
				i--;
				j--;
				lcs_pos--;
				//printf("added : %c ",x[i-1]);
			}
			else if(current=='U')
				i--;
			else if(current=='L')
				j--;
			current=b[i][j];
		}
		printf("LCS of the two strings: %s\n",lcs);
	}
	else
	printf("No LCS between the two strings\n");
	printf("Length of LCS: %d\n",c[x_length][y_length]);
	return 0;
}
