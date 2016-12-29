#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int deleteMin(int cost[],int n,int q[],int n1)
{
	int min_node,i,min=999;
	for(i=0;i<n;i++)
		if(cost[i]<min && q[i]!=-1)
		{
			min=cost[i];
			min_node=i;
		}
	return min_node;
}
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
	//printf("\n\n");
	fclose(fp);
/*	printf("ADJENCENCY MATRIX:\n");
        for(j=0;j<n;j++)			//W Matrix
        {
                for(i=0;i<n;i++)
                	printf("%5d",W[j][i]);
                printf("\n");
        }
*/	//////////////////////////////////////////W[][] aqiured now start prim///////////////////////////////////////////////
	int priority_queue[n];
	for(i=0;i<n;i++)
                priority_queue[i]=-1;
	//cost array and prev array
	int cost[n],prev[n];	//cost<->key
	for(i=0;i<n;i++)
	{
		cost[i]=999;
		prev[i]=-1;	//-1 for nil
	}

	//lets pick the first node (i.e. node 1) as initial node
	cost[0]=0;
	int queue_count=n;
	for(i=0;i<n;i++)
		priority_queue[i]=i;
	printf("\n");
	while(queue_count>0)	//if queue is not empty
	{
		int v=deleteMin(cost,n,priority_queue,n);
		queue_count--;
		int z=0;
		priority_queue[v]=-1;			//-1 means ts poped out
		for(z=0;z<n;z++)			//for each vertex 
			if(W[v][z]>0 && W[v][z]<999)	//if an edge exists
			{
				if(cost[z]>W[v][z] && priority_queue[z]!=-1)
				{
					cost[z]=W[v][z];
					prev[z]=v;
				}
			}
	}
	for(i=1;i<n && cost[i]!=999;i++)
		printf("Edge between %d and %d of wt: %d\n",prev[i]+1,i+1,cost[i]);
	return 0;
}
