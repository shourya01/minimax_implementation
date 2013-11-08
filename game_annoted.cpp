//Tic-tac-toe console game (Human vs. AI)
//By Shourya Bose.
//Part of Project, CBSE Board Exams 2014.
//Uses minimax algorithm.
//For more info, read http://www.cs.berkeley.edu/~kamil/teaching/sp03/minimax.pdf
/* Code is fully open source and can be accessed via
https://github.com/shourya01/minimax_implementation/blob/master/game_annoted.cpp 
Feel free to fork the repo, or push fixes and/or improvements,
if the program interests you.*/
//The code is fully annoted and explained to the best possible degree.
#include<iostream.h>
#include<conio.h>
//Entry point.
//Using 3x3 board, larger boards require significant edits to code.
//We define -1 as human, 1 as AI and 0 as unoccupied blocks on the board.
//-----------
//NUMBERING:- [R is Row, C is coloumn]
//R1C1-1
//R1C2-2
//R1C3-3
//R2C1-4
//R2C2-5
//R2C3-6
//R3C1-7
//R3C2-8
//R3C3-9
//-----------
char gridChar(int i)
{
	//Attach board symbols to sign convention.
	if(i==-1)
		return 'X';//Human
	else if(i==0)
		return ' ';//Vacant
	else if(i==1)
		return 'O';//Machine
	else
		return 'N';//Unused, this is only to avoid warnings at build.
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
	//We make a 2-D array to facilitate validation of winning states.
    	unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
	//Variable 'wins' represents all possible victory combinations on the board.
    	int i;//Counter-variable.
    	for(i = 0; i < 8; ++i) 
	{
		//Check winning criteria.
        	if(board[wins[i][0]] != 0 &&
           	board[wins[i][0]] == board[wins[i][1]] &&
           	board[wins[i][0]] == board[wins[i][2]])
            	return board[wins[i][2]];//Return the position which gave the 'winning move'.
    	}
    	return 0;
	/* Another implementation could be to use a 'magic square' whose rows, coloumns and
	diagonals sum up to a particular number, to address the board. Then the sum of block
	addresses could tell us about the state of the system, by checking their actual summation
	against the 'magic number'. */
}
//NOTE- win(board) represents 'state' of the game- won, lost or still playing.
//-----------
//EXAMPLE:-
//-2 represents 1st row victory by human.
//2 represents 1st row victory by machine.
//0 represents game is still continuing or ended in a tie.
//-----------
int minimax(int board[9], int player) 
{
	//--------------------------------------------------------------------------------------
	//A SHORT NOTE ON MINIMAX THEOREM.
	//Minimax theorem is used in game theory to MINimise the MAXimum loss.
	//It builds a 'tree' of possibilities and 'prunes' the improbable branches.
	//Here all possible arrangements of the boards are conceived as 'states'.
	//After ever human entry, all possible future states are considered.
	//The one offering the maximum benefit is chosen and displayed as AI move.
	//Benefit is judged in terms of where and how soon victory can be achieved.
	//The place where human can achieve 'nearest' victory is blocked by computer move.
	//As every victory has a preceding 'nearest' state, every chance of victory is blocked.
	//Thus, no human can win against it. They can only lose or draw.
	//A hypothetical match between two minimax-enabled devices always results in a draw.
	//As extensive processing is done on every step, expect lag of a second or two.
	//Minimax is practical in a 3x3 board, but becomes impractical on larger boards.
	//It was proposed by John von Neumann, and is used in Bruteforce machines.
	//Similar versions can be coded where every game ends in loss of AI or a draw.
	//--------------------------------------------------------------------------------------
	
    	//Function-body.
	//First part of function, which checks and returns when win is detected.
    	int winner = win(board);//Copy state into variable winner.
    	if(winner != 0) return winner*player;//Returns signed value of board-state.
	//Second part of function- make recursive minimax() call until first part is invoked.
	int move = -1;//move can be assigned any arbitrary value less than 0.
    	int score = -2;//Losing moves are preferred to no move. [Default- Win {0,1,2} by human]
	//Above line defaults 'score' variable to worse possible consequence-human victory.
	//Anything better than default value eventually gets updated in score.
    	int i;//Counter-variable.
	/*We will now attempt (currently) every possible move on the board. The move returning
	maximum score (worst for opponent) takes precedence. */
    	for(i = 0; i < 9; ++i) 
	{
		//Simulate all moves,
        	if(board[i] == 0) //Provided the move is legal,
		{
            		board[i] = player;//Attempt the move, and initiate the minimax tree.
            		int thisScore = -minimax(board, player*-1);//Recursive minimax()
            		if(thisScore > score)//Do we have any gains? 
			{
                		score = thisScore;
                		move = i;
            		}//Pick the move that's worst for the opponent.
            		board[i] = 0;//Reset board after try.
        	}
    	}
    	if(move == -1) return 0;//Only used when last move is machine's, and game is tied.
    	return score;
}
void computerMove(int board[9]) 
{
	//Machine move. 
	cout<<"Computer's move."<<endl;
    	int move = -1;//Minimum value less than 0.
    	int score = -2;//Corresponds to human player win as {0,1,2}.
    	int i;//Counter-variable.
    	for(i = 0; i < 9; ++i) 
	{
		//Cycle currently allowed moves for best gain.
        	if(board[i] == 0) 
		{
            		board[i] = 1;//Test every available move on the board.
            		int tempScore = -minimax(board, -1);//MAX damage to opponent.
            		board[i] = 0;//Reset board to former state.
            		if(tempScore > score) 
			{
                		score = tempScore;
                		move = i;
				//Optimal gains.
            		}
        	}
    	}
    	//Returns a score based on minimax tree at a given node.
    	board[move] = 1;//Validate the move.
}
void playerMove(int board[9]) 
{
	//Player input. Section is self-explanatory.
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
	/* Saved as a function so that entire code can be used as
	the part of a bigger, more extensive program. */
    	int board[9] = {0,0,0,0,0,0,0,0,0};
    	//computer squares are 1, player squares are -1. Defaults at 0.
	cout<<"Welcome to tic-tac-toe game. You are pitted against computer AI."<<endl;
    	cout<<"Computer: O, You: X\nPlay (1)st or (2)nd? \n";
    	int player=0;
    	cin>>player;
    	cout<<"\n";
	//Validate input.
	while(!(player==1||player==2))
		cout<<"Illegal entry. Re-enter."<<endl;
    	unsigned turn;//Counter of the turns.
    	for(turn = 0; turn < 9 && win(board) == 0; ++turn) 
	{
		//Cycle the counter through a loop.
        	if((turn+player) % 2 == 0)//Check whether move is 'even' or 'odd'.
            		computerMove(board);
        	else 
		{
            		draw(board);
            		playerMove(board);
        	}
    	}
	//Time for the conclusions.
	//Use final value of win(board) to conclude results of the game.
    	switch(win(board)) 
	{
        	case 0:
			draw(board);
			cout<<"A draw.\n";
            		break;
        	case 1:
            		draw(board);
            		cout<<"You lose.\n";
            		break;
        	case -1:
			//Just included for fun. AI loss theoretically not possible.
			//Read note above on MINIMAX.
			draw(board);
            		cout<<"You win. Inconceivable!\n";
            		break;
    	}
}
void main()
{
	clrscr();
	playGameTTT();//No arguments or return values.
	//No mechanism implemented for catching exceptions, will be done in future.
	getch();
}
/* Heartfelt apologies for increasing the code by almost a hundred lines with 
annotations, but I hope that they will make the code more lucid to those who 
are alien to either the technical (coding) or mathematical (algorithm) aspect 
of it. */
/* Suggestions to make the code more compact are welcome. */
