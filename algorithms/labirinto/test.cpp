#include<stdio.h>
#include<stdlib.h>
#define N 9
 
int validPath(int maze[][N],int row,int col)
{
    if(maze[row][col])
        return 1;
 
return 0;
}
void printSolution(int path[][N])
{
int i,j;
 
        for(i=0;i<N;i++)
        {
                for(j=0;j<N;j++)
                {
                        printf("%d ",path[i][j]);
                }
                printf("\n");
        }
}
 
int searchUtil(int maze[][N],int sol[][N],int row,int col)
{
 
if(row==N-1 && col==N-1)
{
    sol[row][col]=1;
    return 1;
}
 
if(row >= N || col >= N || row < 0 || col < 0)
{
        return 0;
}
    if(validPath(maze,row,col)==1)
    {
        if(sol[row][col]==0)
        {
            sol[row][col]=1;
             
                if(searchUtil(maze,sol,row,col+1)==1)
                    return 1;
         
                if(searchUtil(maze,sol,row+1,col)==1)
                    return 1;
 
                        if(searchUtil(maze,sol,row,col-1)==1)
                    return 1;
 
                if(searchUtil(maze,sol,row-1,col)==1)
                                        return 1;
                 
         
            //sol[row][col]=0;
 
        }
    }
 
return 0;
}
 
 
void searchPath(int maze[][N])
{
    int path[N][N];
    int i,j;
 
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            path[i][j]=0;
 
    if(searchUtil(maze,path,0,0)==0)
    {
        printf("\n\nPath does not exist\n\n");
    }
    else
    {
        printf("\n\nSolution\n\n");
        printSolution(path);
    }   
 
}
 
int main()
{
 
int maze[N][N]  =  {
        {1, 1, 1, 1,1,1,1,0,0},
        {0, 0, 1, 0,0,1,0,0,0},
        {0, 0, 0, 1,1,1,0,0,1},
        {1, 1, 0, 0,1,0,0,0,0},
        {0, 0, 1, 1,1,0,0,0,1},
        {1, 1, 1, 0,0,0,0,0,0},
    {0, 1, 0, 0,1,1,1,0,0},
    {0, 1, 1, 1,1,0,1,1,0},
    {0, 0, 0, 0,0,0,0,1,1},
    };
 
/*
modify #define N accordingly for below test case..or it wont give correct output. 
 
int maze[N][N]  =  {
        {1, 1, 1, 1,1,1},
        {0, 0, 1, 0,0,1},
        {0, 0, 0, 1,1,1},
        {1, 1, 0, 0,1,0},
    {0, 0, 1, 1,1,1},
    {0, 0, 0, 0,0,1}
    };
*/
/*
int maze[N][N]  =  { {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };
*/
searchPath(maze);
printf("\n");
return 1;
}