#include<iostream>
#include<vector>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
using namespace std;
char board[21][81];
int length=4;
class Snake
{
	public:
		int x,y;
		char value;
		void update(int x1,int y1,char val)
		{
			x=x1;
			y=y1;
			value=val;
		}
		void push_Snake(vector<Snake> s)
		{
			for(int i=0;i<length;i++)
			{
				board[s[i].x][s[i].y]=s[i].value;
			}
		}
};
vector<Snake> s;
class Food
{
   public:	
		int x,y;
		char value;
		void placeFood()
		{
			x=rand()%20;
			y=rand()%80;
			value='@';
			push_Food();
		}
		void push_Food()
		{
			board[x][y]='@';
		}
};
void printBoard()
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<80;j++)
		{
			cout<<board[i][j];
		}
		cout<<endl;
	}
	
}
void makeBoundary()
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<80;j++)
		{
			if(i==0 || i==19)
			{
				board[i][j]='*';
			}
			if(j==0||j==79)
			{
				board[i][j]='*';
			}
		}
	}
}
void modifySnake()
{
	s[length-1].value='#';
	Snake s1;
	s1.x=s[length-1].x;
	s1.y=s[length-1].y;
	s1.value='T';
	s.push_back(s1);
	length++;
}
void takeInput(char &c)
{
	cin>>c;
}
char moveSnake(char c)
{
	char z;
	Snake temp;
	for(int i=length-2;i>=0;i--)
	{
		s[i+1].x=s[i].x;
		s[i+1].y=s[i].y;
	}
	if(c=='w')
	{
		s[0].x-=1;
		z='s';
	}
	else if(c=='a')
	{
		s[0].y-=1;
		z='d';
	}
	else if(c=='s')
	{
		s[0].x+=1;
		z='w';
	}
	else if(c=='d')
	{
		s[0].y+=1;
		z='a';
	}
	return z;
}
void checkCorners()
{
	if(s[0].x==0)
	{
		s[0].x=19;
	}
	else if(s[0].x==19)
	{
		s[0].x=1;
	}
	else if(s[0].y==79)
	{
		s[0].y=1;
	}
	else if(s[0].y==0)
	{
		s[0].y=78;
	}
}
void makeBoardNull()
{
	for(int i=1;i<19;i++)
	{
		for(int j=1;j<79;j++)
		{
			board[i][j]='\0';
		}
	}
}
int checkValidity()
{
	if(board[s[0].x][s[0].y]=='#'|| board[s[0].x][s[0].y]=='T' )
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
void makeBoardFromFile(Food &f)
{
	ifstream in("SaveFile.txt");
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<80;j++)
		{
			in>>board[i][j];
			if(board[i][j]=='@')
			{	
				f.x=i;
				f.y=j;
			}
		}
	}
	int c;
	char val,val1;
	length=0;
	Snake s1;
	while(s1.value!='T')
	{
		s1.x=in.get()-48;
		val1=in.get();
		val=in.get();
		if(val>=48 && val<=57)
		{
			s1.y=(val1-48)*10 + (val-48);
			s1.value=in.get();
		}
		else
		{
			s1.value=val;
		}
		s.push_back(s1);
		length++;
	}
	//print(s);
}

int main()
{
	int i;
	Food f;
	Snake s1;
	cout<<"WELCOME :";
	cout<<"(a) New Game \t (b)Continue From Previous Game : ";
	char choice;
	cin>>choice;
	cout<<"Press '-' Sign to Save the Game"<<endl;
	if(choice=='a')
	{
		makeBoardNull();
			for(i=0;i<4;i++)
			{
			 if(i==0)
			 {
			 s1.update(4,4+i,'H');
			 }
			 else if(i==3)
			 {
			 s1.update(4,4+i,'T');
			 }
			 else
			 {
			 s1.update(4,4+i,'#');
			 }
			 s.push_back(s1);
			 }
			 s1.push_Snake(s);
			 	makeBoundary();
			 	f.placeFood(); 
	}
	else if(choice=='b')
	{
		makeBoardFromFile(f);
		f.push_Food();
	}
	int k=0;
	char c;
	printBoard();
	takeInput(c);
	char z;
	while(c!='-')
	{
		printBoard();
		if(!kbhit())
		{
			system("cls");
			z=moveSnake(c);
			checkCorners();
			k=checkValidity();
			if(k==-1)
			{
				break;
			}
			makeBoundary();
			makeBoardNull();
			f.push_Food();
			if(f.x==s[0].x && f.y==s[0].y)
			{
				modifySnake();
				f.placeFood();
			}
			s1.push_Snake(s);
		}
		else
			takeInput(c);		
	}
	if(c=='-')
	{
		ofstream out("SaveFile.txt");//save the game into file
		out<<endl;
		for(int i=0;i<20;i++)
		{
			for(int j=0;j<80;j++)
			{
				out<<board[i][j];
			}
		}
		for(int i=0;i<s.size();i++)
		{
			out<<s[i].x<<s[i].y<<s[i].value;
		}
	}
	else if(k==-1)
	{
		cout<<"You Lose"<<endl;
	}
	cout<<"Thanks for playing the game";
 
    return 0;
}