#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <ctype.h>  
#include <string.h> 


#define SIZE 4
int board[SIZE][SIZE]={0};
int score=0;

void instruction(void);
void initboard();
void drawboard(int score);
void addrand(); 
int nullcount();
int moveleft();
int moveright();
int moveup();
int movedown();
int pair();
void judgegame();


int main()
{
	
	char ch,c;

	instruction();
	initboard();
	c=getchar();//按下任意一个字符，chuxianqipan 
	
	addrand();
	addrand();
	drawboard(score);
	printf("Enter'w','s','a','d'(q to quit)\n");
	while(1)
	{
		ch=getchar();
		if(ch!='\n')
		{
		
		switch(ch)
		{
		case'a':moveleft();break;
		case'd':moveright();break;
		case'w':moveup();break;
		case's':movedown();break;
		case'q':initboard();break;
		}
		
		
		drawboard(score);	
		judgegame();}	
	}
	return 0;
}

void instruction()
{
	printf("Instruction\n");
	printf("MOVEUP：w\n");
	printf("MOVEDOWN：s\n");
	printf("MOVELEFT：a\n");
	printf("MOVERIGHT：d\n");
	printf("Enter 'w','s','a','d' to play the game!\n");
	printf("Enter any key to start the game!\n");
}

//clear the board
void initboard()
{
	int x,y;
	for(x=0;x<SIZE;x++)
	{for(y=0;y<SIZE;y++)
		board[x][y]==0;}
		
}

//print the board
void drawboard(int score)
{
	system("cls");
	printf("          GAME 2048         \n");
	printf("SCORE:%d\n",score);
	int i,j;
	for(i=0;i<SIZE;i++)
	{	printf("|—————|—————|—————|—————|\n");
	printf("|          |          |          |          |\n|");
		for(j=0;j<SIZE;j++)
		{
		
			
			if(board[i][j]==0)
				printf("          |");
			else
				printf("  %4d    |",board[i][j]);
			
		}printf("\n");
	}
 printf("|—————|—————|—————|—————|\n");
	

}

//数空的格子 
int nullcount()
{
	int i,j,n;
	n=0;
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if(board[i][j]==0)
			n+=1;
		}
	}
	return n;
}

//add random number
void addrand()
{
    srand(time(0));
    int i,j; 
	int n = rand() % nullcount();/* 确定在何处空位置生成随机数 */
	for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (board[i][j] == 0 && n == 0) /* 定位待生成的位置 */
            {	
                board[i][j] = (rand() % 3 ? 2 : 4);/* 确定生成何值，设定生成2的概率是4的概率的两倍 */
               return;
            }
			else if (board[i][j] == 0)
			 n--;
			
        }
    }
}



int moveleft()
{
	int i,j,flag=0;
	for(i=0;i<SIZE;i++)      //先把所有的0排除移走 
	{
		for(j=2;j>=0;j--)  
        {
        	if(board[i][j]==0)
        	{
        		int k;
        		for(k=j;k<SIZE-1;k++)
        		{
					board[i][k]=board[i][k+1];
        			flag=1;
        			board[i][k+1]=0;
        		}
        	}
        }
        for(j=0;j<SIZE-1;j++)     //如果有相同的就相加 
        {
        	if(board[i][j]==board[i][j+1])
        	{
        		board[i][j]+=board[i][j+1];
        		score+=board[i][j];
        		board[i][j+1]=0;
        		flag=1;
			}
		}
		for(j=2;j>=0;j--)  
        {
        	if(board[i][j]==0)
        	{
        		int k;
        		for(k=j;k<SIZE-1;k++)
        		{
					board[i][k]=board[i][k+1];
        			flag=1;
        			board[i][k+1]=0;
        		}
        	}
        }
   	}
	if(flag)         //每一次有效移动后加一个随机数 
	addrand();
}  

//let the board move right
int moveright()
{
	int i,j,flag=0;  
    for(i=0;i<SIZE;i++)  
    {  
        for(j=1;j<SIZE;j++)  
        {  
            if(board[i][j]==0)
            {
            	int k;
            	for(k=j;k>0;k--)
            	{
            		board[i][k]=board[i][k-1];
            		flag=1;
            		board[i][k-1]=0;
				}
			}
        }  
        for(j=3;j>0;j--)
        {
        	if(board[i][j]==board[i][j-1])
        	{
        		board[i][j]+=board[i][j-1];
        		score+=board[i][j];
        		flag=1;
        		board[i][j-1]=0;
			}
		}
		for(j=1;j<SIZE;j++)  
        {  
            if(board[i][j]==0)
            {
            	int k;
            	for(k=j;k>0;k--)
            	{
            		board[i][k]=board[i][k-1];
            		flag=1;
            		board[i][k-1]=0;
				}
			}
        }  
    }  
    if(flag)  
        addrand();
}


//let the board move up
int moveup()
{
	int i,j,flag=0;  
    for(j=0;j<SIZE;j++)  
    {
    	for(i=2;i>0;i--)
    	{
    		if(board[i][j]==0)
    		{
    			int k;
    			for(k=i;k<SIZE-1;k++)
    			{
    				board[k][j]=board[k+1][j];
    				flag=1;
    				board[k+1][j]=0;
				}
			}
		}
		for(i=0;i<SIZE-1;i++)
		{
			if(board[i][j]==board[i+1][j])
			{
				board[i][j]+=board[i+1][j];
				score+=board[i][j];
				flag=1;
				board[i+1][j]=0;
			}
		}
		//printf("flag=%d ",flag);
		for(i=2;i>=0;i--)
    	{
    		if(board[i][j]==0)
    		{
    			int k;
    			for(k=i;k<SIZE-1;k++)
    			{
    				board[k][j]=board[k+1][j];
    				flag=1;
    				board[k+1][j]=0;
				}
			}
		}   
	}  
  printf("flag=%d ",flag);
    if(flag)  
        addrand(); 
}


//let the board move down
int movedown()
{
    int i,j,flag=0;  
    for(j=0;j<SIZE;j++)
    {
    	for(i=1;i<SIZE;i++)
    	{
    		if(board[i][j]==0)
    		{
				int k;
    			for(k=i;k>0;k--)
    			{
    				board[k][j]=board[k-1][j];
    				flag=1;
    				board[k-1][j]=0;
				}
			}
		}
		for(i=3;i>0;i--)
		{
			if(board[i][j]==board[i-1][j])
			{
				board[i][j]+=board[i-1][j];
				score+=board[i][j];
				flag=1;
				board[i-1][j]=0;
			}
		}
		for(i=1;i<SIZE;i++)
    	{
    		if(board[i][j]==0)
    		{
				int k;
    			for(k=i;k>0;k--)
    			{
    				board[k][j]=board[k-1][j];
    				flag=1;
    				board[k-1][j]=0;
				}
			}
		}
	}
    if(flag)  
        addrand();
}

int pair()
{
	int i,j;
	for(i=0;i<SIZE-1;i++)
	{
		for(j=0;j<SIZE-1;j++)
		{
			if(board[i][j]==board[i][j+1]||board[i][j]==board[i+1][j])
				return 1;		
		}
	}
	return 0;
}


// judge the game end or not
void judgegame()
{
	int x,y;
	
	for(x=0;x<SIZE;x++)
		{for(y=0;y<SIZE;y++)
			{
			if(board[x][y]==2048)
				{
					system("cls");
					printf("YOU WIN!\n");
					break;
				}
			else
				
					if(!nullcount()&&!pair())
					{
						printf("YOU LOST!\n");
					}
		    	break;		
			}
			
		}
}


