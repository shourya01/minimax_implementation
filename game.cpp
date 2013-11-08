#include<iostream.h>
#include<conio.h>
//Entry point.
char gridChar(int i)
{
	//Define sign convention.
	if(i==-1)
		return 'X';
	else if(i==0)
		return ' ';
	else if(i==1)
		return 'O';
	else
		return 'N';//To avoid warnings at build.
}
void draw(int b[9]) 
{
	//Draw the board.
    cout<<" "<<gridChar(b[0])<<" | "<<gridChar(b[1])<<" | "<<gridChar(b[2])<<endl;
    cout<<"---+---+---\n";
    cout<<" "<<gridChar(b[3])<<" | "<<gridChar(b[4])<<" | "<<gridChar(b[5])<<endl;
    cout<<"---+---+---\n";
    cout<<" "<<gridChar(b[6])<<" | "<<gridChar(b[7])<<" | "<<gridChar(b[8])<<endl;
}
int win(const int board[9]) 
{
    //Determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
	//Variable 'wins' represent all possible victory combinations on the board.
    int i;
    for(i = 0; i < 8; ++i) 
	{
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];//Return the position which was the 'winning move'.
    }
    return 0;
}
int minimax(int board[9], int player) 
{
    //How is the position like for the player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;
 
    int move = -1;
    int score = -2;//Losing moves are preferred to no move.
    int i;
    for(i = 0; i < 9; ++i) 
	{
		//For all moves,
        if(board[i] == 0) //If legal
		{
            board[i] = player;//Try the move.
            int thisScore = -minimax(board, player*-1);//Recursive minimax()
            if(thisScore > score)//Do we have any gains? 
			{
                score = thisScore;
                move = i;
            }//Pick the move that's worst for the opponent.
            board[i] = 0;//Reset board after try.
        }
    }
    if(move == -1) return 0;//Only in use for second last move before draw.
    return score;
}
void computerMove(int board[9]) 
{
	cout<<"Computer's move."<<endl;
    int move = -1;//Minimum value less than 0.
    int score = -2;//Corresponds to human player win as {0,1,2}.
    int i;
    for(i = 0; i < 9; ++i) 
	{
        if(board[i] == 0) 
		{
            board[i] = 1;//Test every available move on the board.
            int tempScore = -minimax(board, -1);
            board[i] = 0;//Validate the move.
            if(tempScore > score) 
			{
                score = tempScore;
                move = i;
				//Optimal gains.
            }
        }
    }
    //Returns a score based on minimax tree at a given node.
    board[move] = 1;
}
void playerMove(int board[9]) 
{
	cout<<"Your move."<<endl;
	//Accept move from player within legal limits.
    	int t = 0;
	cout<<"Enter your move position from 1-9."<<endl;
	cin>>t;
	int move=t-1;//Compromise for 0 begin of array.
    	while (move >= 9 || move < 0 || board[move] != 0)
	{
		cout<<"Illegal entry. Re-enter."<<endl;
		cin>>t;
		move=t-1;
	}
    board[move] = -1;
    clrscr();
}
void playGameTTT(void) 
{
    int board[9] = {0,0,0,0,0,0,0,0,0};
    //computer squares are 1, player squares are -1.
	cout<<"Welcome to tic-tac-toe game. You are pitted against computer AI."<<endl;
    cout<<"Computer: O, You: X\nPlay (1)st or (2)nd? \n";
    int player=0;
    cin>>player;
    cout<<"\n";
	while(!(player==1||player==2))
		cout<<"Illegal entry. Re-enter."<<endl;
    unsigned turn;
    for(turn = 0; turn < 9 && win(board) == 0; ++turn) 
	{
        if((turn+player) % 2 == 0)
            computerMove(board);
        else 
		{
            draw(board);
            playerMove(board);
        }
    }
    switch(win(board)) 
	{
        case 0:
			cout<<"A draw.\n";
            break;
        case 1:
            draw(board);
            cout<<"You lose.\n";
            break;
        case -1:
            cout<<"You win. Inconceivable!\n";
            break;
    }
}
void main()
{
	clrscr();
	playGameTTT();
	getch();
}
	
