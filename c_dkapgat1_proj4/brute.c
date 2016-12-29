#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int max_profit=0;
int iter=0;
int *Knap(int item,int AddOrNot,int weight,int prof,int W[],int profit[],int capacity,int Sack[],int max_Sack[],int n)
{
	if(AddOrNot==1)
	{
		Sack[item]=1;
		weight=weight+W[item];
		prof=prof+profit[item];
	}
	else
	{
		Sack[item]=0;
	}
	if(weight<=capacity && prof>max_profit)
        {
        	max_profit=prof;
                int i;
                for(i=0;i<n;i++)
                	max_Sack[i]=Sack[i];
       	}
	iter++;
	if(item+1!=n)
	{
		max_Sack=Knap(item+1,1,weight,prof,W,profit,capacity,Sack,max_Sack,n);
		max_Sack=Knap(item+1,0,weight,prof,W,profit,capacity,Sack,max_Sack,n);
	}
	return max_Sack;
}
int main(int argc,char* argv[])
{
	FILE *fp=fopen(argv[1],"r");
	char str[255];
	int n=0,i;
	//NUMBER OF ITEMS////////////////////////////////////////////////////
	fscanf(fp,"%s",str);
	for(i=0;i<strlen(str);i++)
		n=(10*n)+((int)str[i]-48);
	//printf("no of items : %d\n",n);
	//WEIGHT OF EACH ITEM///////////////////////////////////////////////
	int W[n],profit[n];
	for(i=0;i<n;i++)
	{
		W[i]=0;
		profit[i]=0;
	}
	fscanf(fp,"%s",str);
	//printf("%s\n",str);
	char *value=strtok(str,",");
	for(i=0;i<strlen(value);i++)
		W[0]=(10*W[0])+((int)value[i]-48);
	int j;
	for(j=1;j<n;j++)
	{
		fscanf(fp,"%s",str);
		value=strtok(str,",");
		for(i=0;i<strlen(value);i++)
	       		W[j]=(10*W[j])+((int)value[i]-48);
	}
	//for(i=0;i<n;i++)
	//	printf("%d ",W[i]);
	//printf("\n");
	//PROFIT OF EACH ITEM///////////////////////////////////////////////
	fscanf(fp,"%s",str);
        value=strtok(str,",");
        for(i=0;i<strlen(value);i++)
                profit[0]=(10*profit[0])+((int)value[i]-48);
        for(j=1;j<n;j++)
        {
                fscanf(fp,"%s",str);
                value=strtok(str,",");
                for(i=0;i<strlen(value);i++)
                	profit[j]=(10*profit[j])+((int)value[i]-48);
        }
	//for(i=0;i<n;i++)
	//	printf("item %d) wt : %d profit : %d\n",i+1,W[i],profit[i]);
	//CAPACITY//////////////////////////////////////////////////////////
	fscanf(fp,"%s",str);
	int capacity=0;
	for(i=0;i<strlen(str);i++)
                capacity=(10*capacity)+((int)str[i]-48);
        //printf("CAPACITY : %d\n",capacity);

	fclose(fp);
	//FILE OPERATION COMPLETE
	int Sack[n],max_Sack[n];
	for(i=0;i<n;i++)
	{
		Sack[i]=0;
		max_Sack[i]=0;
	}
	int *solution,wt=0;
	solution=Knap(0,1,0,0,W,profit,capacity,Sack,max_Sack,n);
	solution=Knap(0,0,0,0,W,profit,capacity,Sack,max_Sack,n);
	//printf("max_profit : %d\n",max_profit);
	for(i=0;i<n;i++)
		if(solution[i]==1)
			wt=wt+W[i];
	//printf("\n%d\n",wt);
	//printf("%s\n",value);
	//WRITING INTO OUTPUT FILE////////////////////////////////////////////////////
	fp=fopen("brute_output.txt","w");
	fprintf(fp,"%d\n%d\n",wt,max_profit);
	for(i=0;i<n;i++)
	{
		if(solution[i]==1)
		{
			fprintf(fp,"%d",i);
			i++;
			break;
		}
	}
	for(;i<n;i++)
		if(solution[i]==1)
			fprintf(fp,", %d",i);
	fclose(fp);
	return 0;
}
