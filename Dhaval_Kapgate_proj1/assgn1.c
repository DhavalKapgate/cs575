#include<stdio.h>
#include<stdlib.h>
//////////////////////////////common functions for all sort////////////////////////////////////////////////////////////////////////////////
void swap(int *first,int *second)
{
	int temp;
        temp = *first;
        *first = *second;
        *second = temp;
}
void star_display(int no_of_input,int input[])
{
	int counter1,counter2;
	printf("\n");
	for(counter1=0;counter1<no_of_input;counter1++)
	{//if statements for the alignment
		if(counter1>=10)
		{
		if(input[counter1]<10)
                        printf("input[%d] : <%d > : ",counter1,input[counter1]);
                else
                        printf("input[%d] : <%d> : ",counter1,input[counter1]);
                for(counter2=0;counter2<input[counter1];counter2++)
                        printf("*");

		}
		else
		{
		if(input[counter1]<10)
			printf("input[%d ] : <%d > : ",counter1,input[counter1]);
		else
			printf("input[%d ] : <%d> : ",counter1,input[counter1]);
		for(counter2=0;counter2<input[counter1];counter2++)
			printf("*");
		}
		printf("\n");
	}
}
//////////////////////////////CASE 1 : INSERTION SORT/////////////////////////////////////////////////////////////////////////////
void InsertionSort(int no_of_input,int input[])
{
	int counter1,counter2;
	for (counter1 = 1 ; counter1 < no_of_input; counter1++)
	{
    		counter2 = counter1;
    		while (input[counter2] < input[counter2-1] && counter2>0)
		{
			swap(&input[counter2],&input[counter2-1]);
      			counter2--;
			if(no_of_input<=20)
				star_display(no_of_input,input);
    		}
  	}
}
/////////////////////////////////CASE 2 : COUNT SORT/////////////////////////////////////////////////////////////////////////////
void CountSort(int no_of_input,int input[])
{
	int count[100],counter;	//count[] keeps track of no of occurance of element in list
	for(counter=0;counter<100;counter++)
		count[counter]=0;
	for(counter=0;counter<no_of_input;counter++)
		count[input[counter]]++;
	int current=0;
	printf("\n");
	if(no_of_input<=20)
		for(counter=0;counter<=15;counter++)
		{
			if(counter<10)
				printf("count[%d] : %d\t",counter,count[counter]);
			else
				printf("count[%d]: %d\t",counter,count[counter]);
			if((counter+1)%5==0)
				printf("\n");
		}
	for(counter=0;counter<=99;counter++)
	{
		while(count[counter]!=0)
		{
			input[current++]=counter;
			count[counter]--;
		}
	}
}
////////////////////////////CASE 3: MERGE SORT///////////////////////////////////////////////////////////////////////////////////
void Merge(int low,int middle,int high,int input[],int input_size)
{
	int temp[1000];

    	int lo=low;
    	int current=low;
    	int mid=middle+1;

    	for(;(lo<=middle)&&(mid<=high);current++)
	{
         	if(input[lo]<=input[mid])
             		temp[current]=input[lo++];
         	else
             		temp[current]=input[mid++];
    	}
	int k;
    	if(lo>middle)
	{
         	for(k=mid;k<=high;k++)
             		temp[current++]=input[k];
    	}
    	else
	{
         	for(k=lo;k<=middle;k++)
             		temp[current++]=input[k];
    	}
    	for(k=low;k<=high;k++)
         	input[k]=temp[k];

	//In merge sort the actual work of sorting happens in merge stage
	if(input_size<=20)
               star_display(input_size,input);
}
void partition(int low,int high,int input[],int input_size)
{
    	int middle;
    	if(low<high)
	{
         	middle=(low+high)/2;
         	partition(low,middle,input,input_size);
         	partition(middle+1,high,input,input_size);
         	Merge(low,middle,high,input,input_size);
	}
}
void MergeSort(int no_of_input,int input[])
{
	partition(0,no_of_input-1,input,no_of_input);//the fourth parameter is used to decide whether to do textual visualisation
								//and is a constant throughout the sort
}
///////////////////////////CASE 4 : RANDOMISED QUICK SORT///////////////////////////////////////////////////////////////////////////////////
int Q_partition(int start,int end,int input[],int input_size)
{
 	int pivot = start+rand()%(end-start+1);
	if(input_size<=20)
		printf("PIVOT Position in the above list was : %d (i.e. %d)\n",pivot,input[pivot]);
 	swap(&input[end],&input[pivot]);
 	int temp = input[end];
 	int i = start-1,j;
 	for (j = start; j < end ;j++)
	{
  		if ( input[j] < temp )
		{
   			i++;
   			swap (&input[i],&input[j]);
  		}
 	}
	i++;
 	swap (&input[end],&input[i]);
	//In quick sort the actual work of sorting happens in partition stage
        if(input_size<=20)
               star_display(input_size,input);

 	return i;
}
void RandomQuickSort(int left,int right,int input[],int input_size)
{
	if (left < right)
 	{
  		int pivot = Q_partition(left,right,input,input_size);
  		RandomQuickSort(left,pivot-1,input,input_size);
  		RandomQuickSort(pivot+1,right,input,input_size);
 	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	int input[1000];
	int no_of_input;
	srand(time(NULL));
	printf("Enter number of input data : ");
	do
	{
		scanf("%d",&no_of_input);
		if(no_of_input>1000||no_of_input<1)
			printf("Enter again (between 1 and 1000): ");
	}while(no_of_input>1000 || no_of_input<1);
	int i;			//counter for for loop only
	int choice;
	printf("\nEnter the sorting algorithm of choice:\n1)Insertion Sort \n2)Counting Sort \n3)Merge Sort \n4)Randomised QuickSort\n");
	do
	{
		scanf("%d",&choice);
		if(choice>4||choice<1)
                        printf("Enter again (between 1 and 4): ");
	}while(choice>4||choice<1);
	switch(choice)
	{
		case 1:
			printf("Insertion Sort\nThe unsorted list:\n");
			if(no_of_input<=20)
				for(i=0;i<no_of_input;i++)
			                input[i]=rand()%15;
			else
				for(i=0;i<no_of_input;i++)
                			input[i]=rand();
			for(i=0;i<no_of_input;i++)
				printf("%d ",input[i]);
			 if(no_of_input<=20)
                               star_display(no_of_input,input);
			InsertionSort(no_of_input,input);
			break;
		case 2:
			printf("Counting Sort\nThe unsorted list:\n");
			if(no_of_input<=20)
                                for(i=0;i<no_of_input;i++)
                                        input[i]=rand()%16;
                        else
                                for(i=0;i<no_of_input;i++)
                                        input[i]=rand()%100;
			for(i=0;i<no_of_input;i++)
                                printf("%d ",input[i]);
			CountSort(no_of_input,input);
			break;
		case 3:
			printf("Merge Sort\nThe unsorted list:\n");
			if(no_of_input<=20)
                                for(i=0;i<no_of_input;i++)
                                        input[i]=rand()%15;
                        else
                                for(i=0;i<no_of_input;i++)
                                        input[i]=rand();
			for(i=0;i<no_of_input;i++)
                                printf("%d ",input[i]);
			if(no_of_input<=20)
                               star_display(no_of_input,input);
			MergeSort(no_of_input,input);
			break;
		case 4:
			printf("Randomised QuickSort\nThe unsorted list :\n");
			if(no_of_input<=20)
                                for(i=0;i<no_of_input;i++)
                                        input[i]=rand()%15;
                        else
                                for(i=0;i<no_of_input;i++)
                                        input[i]=rand();
			for(i=0;i<no_of_input;i++)
                                printf("%d ",input[i]);
			if(no_of_input<=20)
                               star_display(no_of_input,input);
			RandomQuickSort(0,no_of_input-1,input,no_of_input);
			break;
	}
	printf("\nThe sorted list of %d integers:\n",no_of_input);
        for(i=0;i<no_of_input;i++)
                printf("%d ",input[i]);
	printf("\n");
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
