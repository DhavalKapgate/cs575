#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	int profit,weight,itemno;
};
int maxprofit=0;
////////////////////////////////SORT THE TABLE//////////////////////////////////////////////
/////////////////////////////////Randomised Quicksort on edges/////////////////////////////////////////////////////////////////////////
void swap(struct node *first,struct node *second)
{
	struct node temp;
        temp = *first;
        *first = *second;
        *second = temp;
}
int Q_partition(int start,int end,struct node input[],int input_size)
{
 	int pivot = start+rand()%(end-start+1);
 	swap(&input[end],&input[pivot]);
 	struct node temp = input[end];
 	int i = start-1,j;
 	for (j = start; j < end ;j++)
	{
		float PW1=(float)input[j].profit/(float)input[j].weight,PW2=(float)temp.profit/(float)temp.weight;
  		if (PW1>PW2)
		{
   			i++;
   			swap (&input[i],&input[j]);
  		}
 	}
	i++;
 	swap (&input[end],&input[i]);
 	return i;
}
void RandomQuickSort(int left,int right,struct node input[],int input_size)
{
	if (left < right)
 	{
  		int pivot = Q_partition(left,right,input,input_size);
  		RandomQuickSort(left,pivot-1,input,input_size);
  		RandomQuickSort(pivot+1,right,input,input_size);
 	}
}
////////////////////////////////////////////////////////////////////////////////////////////
int KWF(int i,int weight,int profit,struct node Node[],int C,int n)
{
	int j=i;
	int bound=profit;
	float x[n];
	for(;j<n;j++)
		x[j]=0;
	j=i;
	while(weight<C && j<n)
	{
		if(weight+Node[j].weight<=C)
		{
			x[j]=1;
			weight=weight+Node[j].weight;
			bound=bound+Node[j].profit;
		}
		else
		{
			x[j]=(C-weight);
			x[j]=x[j]/Node[j].weight;
			weight=C;
			bound=bound+x[j]*Node[j].profit;
		}
		j++;
	}
	return bound;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int promising(int i,int weight,int profit,struct node Node[],int C,int n)
{
	if(weight>=C)
		return 0;
	int bound=KWF(i,weight,profit,Node,C,n);
	//printf("Item %d weight: %d profit: %d bound: %d\n",i,weight,profit,bound);
	if(bound>maxprofit)
		return 1;
	else return 0;
}
int *knapsack(int i,int profit,int weight,int C,struct node Node[],int n,int include[],int bestset[])
{
  	if(i>n)	return bestset;
	if(weight<=C && profit>maxprofit)
	{
		maxprofit=profit;
		int j=0;
		for(;j<n+1;j++)
			bestset[j]=include[j];
	}
	if(promising(i,weight,profit,Node,C,n))
	{
		include[i+1]=1;
		bestset=knapsack(i+1,profit+Node[i].profit,weight+Node[i].weight,C,Node,n,include,bestset);
		include[i+1]=0;
               	bestset=knapsack(i+1,profit,weight,C,Node,n,include,bestset);
	}
	return bestset;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char* argv[])
{
	FILE *fp=fopen(argv[1],"r");
	char str[255];
	int n=0,i;
	//NUMBER OF ITEMS////////////////////////////////////////////////////
	fscanf(fp,"%s",str);
	for(i=0;i<strlen(str);i++)
		n=(10*n)+((int)str[i]-48);
	//WEIGHT OF EACH ITEM///////////////////////////////////////////////
	struct node Node[n];
	for(i=0;i<n;i++)
	{
		Node[i].weight=0;
		Node[i].profit=0;
		Node[i].itemno=i;
	}
	fscanf(fp,"%s",str);
	char *value=strtok(str,",");
	for(i=0;i<strlen(value);i++)
		Node[0].weight=(10*Node[0].weight)+((int)value[i]-48);
	int j;
	for(j=1;j<n;j++)
	{
		fscanf(fp,"%s",str);
                value=strtok(str,",");
		for(i=0;i<strlen(value);i++)
			if(value[i]!=',')
		             Node[j].weight=(10*Node[j].weight)+((int)value[i]-48);
	}
	//PROFIT OF EACH ITEM///////////////////////////////////////////////
	fscanf(fp,"%s",str);
        value=strtok(str,",");
        for(i=0;i<strlen(value);i++)
                Node[0].profit=(10*Node[0].profit)+((int)value[i]-48);
        for(j=1;j<n;j++)
        {
                fscanf(fp,"%s",str);
                value=strtok(str,",");
                for(i=0;i<strlen(value);i++)
			if(value[i]!=',')
	                     Node[j].profit=(10*Node[j].profit)+((int)value[i]-48);
        }
	//CAPACITY//////////////////////////////////////////////////////////
	fscanf(fp,"%s",str);
	int capacity=0;
	for(i=0;i<strlen(str);i++)
                capacity=(10*capacity)+((int)str[i]-48);
	fclose(fp);
	//FILE OPERATION COMPLETE
	//Sort table//////////////////////////////////////////////////////////
	RandomQuickSort(0,n-1,Node,n);
	//printf("AFTER SORT\n");
	//for(i=0;i<n;i++)
	//{
	//	float x=(float)Node[i].profit/(float)Node[i].weight;
        //        printf("item %d) wt : %d profit : %d %f\n",i+1,Node[i].weight,Node[i].profit,x);
	//}
	/////////////////////////////////////////////////////////////////////
	int include[n+1],bestset[n+1];
	int *best;
	best=bestset;
	for(i=0;i<n+1;i++)
		include[i]=bestset[i]=0;
	best=knapsack(0,0,0,capacity,Node,n,include,bestset);
	//printf("Maxprofit : %d\n",maxprofit);

	//WRITING INTO OUTPUT FILE////////////////////////////////////////////////////
  	fp=fopen("backtrack_output.txt","w");
	int weight=0;
	for(i=0;i<n;i++)
		if(bestset[i+1]==1)
			weight=weight+Node[i].weight;
        fprintf(fp,"%d\n%d\n",weight,maxprofit);
	int inc[n];
        for(i=0;i<n;i++)
	//itemno stores the order of items in original list(i.e. before sort)
                if(best[i+1]==1)
                        inc[Node[i].itemno]=1;
                else
                        inc[Node[i].itemno]=0;
	int added=0;	//to check if first element is printed or not
        for(i=0;i<n;i++)
        {	if(inc[i]==1 && added==0)
		{
                        fprintf(fp,"%d",i);
			added=1;
		}
	        else if(inc[i]==1 && added!=0)
                        fprintf(fp,", %d",i);
        }
	fclose(fp);
	return 0;
}


