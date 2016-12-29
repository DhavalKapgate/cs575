#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct edges
{
	int vertex[2];
	int wt;
};
/////////////////////////////////Randomised Quicksort on edges/////////////////////////////////////////////////////////////////////////
void swap(struct edges *first,struct edges *second)
{
	struct edges temp;
        temp = *first;
        *first = *second;
        *second = temp;
}
int Q_partition(int start,int end,struct edges input[],int input_size)
{
 	int pivot = start+rand()%(end-start+1);
 	swap(&input[end],&input[pivot]);
 	struct edges temp = input[end];
 	int i = start-1,j;
 	for (j = start; j < end ;j++)
	{
  		if ( input[j].wt < temp.wt )
		{
   			i++;
   			swap (&input[i],&input[j]);
  		}
 	}
	i++;
 	swap (&input[end],&input[i]);

 	return i;
}
void RandomQuickSort(int left,int right,struct edges input[],int input_size)
{
	if (left < right)
 	{
  		int pivot = Q_partition(left,right,input,input_size);
  		RandomQuickSort(left,pivot-1,input,input_size);
  		RandomQuickSort(pivot+1,right,input,input_size);
 	}
}
///////////////////////////////////////////////////find3/////////////////////////////////////////////////////////////////////////////
int find3(int x,int set[],int n)
{
	//printf("Enter find3 x=%d\n",x);
	int root=x;
	while(set[root]!=root)
		root=set[root];

	int node=x;
	while(node!=root)
	{
		int parent=set[node];
		set[node]=root;
		node=parent;
	}
	return root;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char* argv[])
{
	FILE *fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("ERROR : INVALID FILENAME : ABORT\n");
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
	printf("\n");
	fclose(fp);
	int total_edges=0;
	//printf("ADJENCENCY MATRIX:\n");
        for(j=0;j<n;j++)			//W Matrix
        {
                for(i=0;i<n;i++)
                {
			//printf("%5d",W[j][i]);
			if(W[j][i]>0&&W[j][i]<999)
				total_edges++;
                }
		//printf("\n");
        }
	int iter=0;
	struct edges E[total_edges];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(W[i][j]>0&&W[i][j]<999)
                        {
			        E[iter].vertex[0]=i;
				E[iter].vertex[1]=j;
 				E[iter].wt=W[i][j];
				iter++;
			}
		}
	//now sort the edges
	RandomQuickSort(0,total_edges-1,E,total_edges);

	//create Set[n] and height[n]
	int set[n],height[n];
	for(i=0;i<n;i++)
	{
		set[i]=i;
		height[i]=0;
	}
	int no_of_edges=0;
	iter=0;
	struct edges T[n-1];
	for(i=0;i<n-1;i++)
		T[i].wt=999;
	/*	for(i=0;i<n;i++)
		printf("%d ",set[i]);*/
	while((no_of_edges<total_edges) && iter<n-1)
	{
		int ucomp=find3(E[no_of_edges].vertex[0],set,n);
		int vcomp=find3(E[no_of_edges].vertex[1],set,n);
		if(ucomp!=vcomp)
		{
			T[iter++]=E[no_of_edges];
			//union3 here->repx=ucomp and repy=vcomp
			if(height[ucomp]==height[vcomp])
		        {
                		height[ucomp]++;
                		set[vcomp]=ucomp;
        		}
        		else if(height[ucomp]>height[vcomp])
                		set[vcomp]=ucomp;
        		else
                		set[ucomp]=vcomp;
		}
     		no_of_edges++;
	}
	for(i=0;i<n-1&&T[i].wt!=999;i++)
                printf("Edge between %d and %d of wt : %d\n", T[i].vertex[0]+1,T[i].vertex[1]+1,T[i].wt);
	printf("\n");
	return 0;
}

