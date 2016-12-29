#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/////////////////////////////////////////////////////////////////////////////////////
int tile_id=1;
void tile(int size,int x_hole,int y_hole,int actual_size,int board[][actual_size],int x,int y)
//parameters:modified size of board,coordinates of hole,the board and its actual size,start coordinates of subboard
{
	if(size==2)//trivial case
	{
		int i,j;
		for (i=x;i<(x+size); ++i)
			for (j=y;j<(y+size);++j)
				if(!(i==x_hole && j==y_hole))
					board[i][j]=tile_id;
    		tile_id++; 
	}
  else
  {
	int x11,y11,x12,y12,x21,y21,x22,y22;
	if(x_hole<x+size/2 && y_hole< y+size/2)
	{
 //place tile
		board[x+size/2-1][y+size/2]=tile_id;
    		board[x+size/2][y+size/2-1]=tile_id;
    		board[x+size/2][y+size/2]=tile_id++;
		x11=x_hole;
    		y11=y_hole;
		x12=x+size/2-1;
    		y12=y+size/2;
		x21=x+size/2;
    		y21=y+size/2-1;
		x22=x+size/2;
    		y22=y+size/2;
	}
  	else if(x_hole<x+size/2 && y_hole>=y+size/2)
	{
 //place tile
		board[x+size/2-1][y+size/2-1]=tile_id;
    		board[x+size/2][y+size/2-1]=tile_id;
    		board[x+size/2][y+size/2]=tile_id++;
    		x12=x_hole; 
    		y12=y_hole;
		x11=x+size/2-1; 
    		y11=y+size/2-1;
		x21=x+size/2; 
    		y21=y+size/2-1;
		x22=x+size/2; 
    		y22=y+size/2;
	}
  	else if(x_hole>=x+size/2 && y_hole<y+size/2)
	{
   //place tile
		board[x+size/2-1][y+size/2-1]=tile_id;
    		board[x+size/2-1][y+size/2]=tile_id;
    		board[x+size/2][y+size/2]=tile_id++;
    		x21=x_hole; 
    		y21=y_hole;
		x11=x+size/2-1;
    		y11=y+size/2-1;
		x12=x+size/2-1; 
    		y12=y+size/2;
		x22=x+size/2; 
    		y22=y+size/2;
	}
  	else if(x_hole>=x+size/2 && y_hole>=y+size/2)
    	{
    //place tile
		board[x+size/2-1][y+size/2-1]=tile_id;
    		board[x+size/2-1][y+size/2]=tile_id;
    		board[x+size/2][y+size/2-1]=tile_id++;
    		x22=x_hole; 
    		y22=y_hole;
		x11=x+size/2-1;
    		y11=y+size/2-1;
		x12=x+size/2-1; 
    		y12=y+size/2;
		x21=x+size/2; 
    		y21=y+size/2-1;
	}
   //recursive calls
	tile(size/2,x11,y11,actual_size,board,x,y);
	tile(size/2,x12,y12,actual_size,board,x ,y+size/2);
	tile(size/2,x21,y21,actual_size,board,x+size/2,y);
	tile(size/2,x22,y22,actual_size,board,x+size/2,y+size/2);
}
}
int main(int argc, char *argv[])
{
	int missing_x,missing_y;
	int i,j;
  	//define board parameters
	int k = atoi(argv[1]);
	int size = pow(2, k);

	srand(time(NULL));
	missing_x = rand() % size;
	missing_y = rand() % size;
	printf("CO-ORDINATES OF MISSING TILE: [%d,%d]\n", missing_x, missing_y);
 	int board[size][size];
  	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			board[i][j] = -1;
	board[missing_x][missing_y] = 0;

	tile(size,missing_x,missing_y,size,board, 0, 0);
	printf("SOLVED TROMINO BOARD :\n");

	for(i=0;i<size;i++)
        {

		for(j=0;j<size;j++)
		{
			if(board[i][j]==0)
				printf("    X");
			else
				printf("%5d",board[i][j]);
		}
                printf("\n");
        }
	return 0;
}





