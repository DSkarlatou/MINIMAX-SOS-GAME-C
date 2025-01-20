#include <stdio.h>
#include <ctype.h>  // for toupper
#include <stdlib.h> //for random generator
#include <time.h>   //for random generator

#include <conio.h>

//prototypes
void displayBoard(); 
int player1Moves();
int player2Moves(); 
int boardFull();    //0-> not Full, 1-> Full
int checkWin();
int minimax(int player, int depth);
int squaresLeft();

//global variables
char cellValue[3][3];
char letter;
int resI = -1; 	    //resulting row
int resJ = -1;        //resulting column
char resLetter = ' '; //resulting letter

int main(){
	printf("\n________________________READ ME________________________\n\n");
	printf("Welcome Human! \nTo play the game you have to input the position number\nAnd then your choice 'S' or 'O'\n");
	printf("Correct input looks like this 1 2 S\nWhere 1->row, 2->column, S->choice\n");
	printf("_______________________________________________________\n");
	int flag = 0;
	int i,j;
	//start game exe loop
	while(flag == 0){
		srand(time(NULL)); 			//to generate a random number, uses the computer's internal clock, to generate a number each time we run the program
		int randomNumber = rand() % 2;	//random number is either 1 or 0
		
		//initialize entire array to space
		for (i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				cellValue[i][j] = ' ';
			}
		}
		if(randomNumber == 0){ 
			cellValue[1][0] = 'O';
		}
		else{ //randomNumber == 1
			cellValue[1][2] = 'O';
		}

		displayBoard();

		printf("\n\nLET'S BEGIN!\n");

		while(boardFull() == 0){
			//computer plays now
			printf("\nCOMPUTER PLAYS \n");
			player2Moves();
			displayBoard();
			if (checkWin() == 10){
				printf("\n --------- d(=^w^=)b ---! COMPUTER WINS !---  d(=^w^=)b ---------\n");
				printf("\n I aM ToO SmArT FoR YoU HuMaN \n");
				break;
				//return 0;
			}
			//human plays
			int res = player1Moves();
			while(res == -1){ //if move is invalid, keep taking input
				res = player1Moves();
			}
			displayBoard();
			if (checkWin() == -10){
				printf("\n d(=^w^=)b  ---------! ! ! HUMAN WINS ! ! !---------  d(=^w^=)b \n");
				printf("\n WELL DONE HUMAN, YOU HAVE DEFEATED ME\n");
				break;
				//return 0;
			}

		}


		if(boardFull() == 1 && checkWin() == 0){
			printf("\n! ! ! ! ! - - - - DRAW - - - - ! ! ! !\n");
		}

        printf("\nWanna go again? Type 0 to start over, anything else to exit:   ");
        scanf("%d",&flag);
        printf("\n");
        system("CLS"); //clear screen
	}
	//end exe
	printf("\n 	 LEAVING SO SOON? I'm blue da ba dee da ba daa d(= T _ T =)b\n");
	printf("\n 		   Well, then, type any button to exit! \n");
	printf("\n\n");
	printf("              			|`-.._____..-'|\n");
	printf("          		    	:  > .  ,  <  :\n");
	printf("         		     	`./ __`' __ \\,'\n");
	printf("        		         | (|_) (|_) |\n");
	printf("        		         ; _  .  __  :\n");
	printf("        		         `.,' - `-. ,'\n");
	printf("        		           `, `_  .'\n");
	printf("        		           /       \\ \n");
	printf("        		          /         :\n");
	printf("        		         :          |_\n");
	printf("        		        ,|  .    .  | \\ \n");
	printf("         		      : :   \\   |  |  :\n");
	printf("           		      |  \\   :`-;  ;  |\n");
	printf("         		      :   :  | /  /   ;\n");
	printf("        		       :-.'  ;'  / _,'`------.\n");
	printf("         		       `'`''-`'''-'-''--.---  )\n");
	printf("          		                        `----'\n\n");
	
    getch();



}

void displayBoard(){

	//first line
	printf(" _______ _______ _______ \n");
	printf("|       |       |       | \n");
	printf("|   %c   |   %c   |   %c   | \n", cellValue[0][0],cellValue[0][1],cellValue[0][2]);
	printf("|_______|_______|_______| \n");

	//second line
	printf("|       |       |       | \n");
	printf("|   %c   |   %c   |   %c   | \n", cellValue[1][0],cellValue[1][1],cellValue[1][2]);
	printf("|_______|_______|_______| \n");

	//third line
	printf("|       |       |       | \n");
	printf("|   %c   |   %c   |   %c   | \n", cellValue[2][0],cellValue[2][1],cellValue[2][2]);
	printf("|_______|_______|_______| \n");
}

int player1Moves(){ //return 0 for success, -1 for failure
	int i = -1; //initialize these, to values that do not exist in the grid
	int j = -1; //in order to check for input
	char choice = ' ';

	//get input
	printf("\nInput move: ");
	scanf( "%i %i %c", &i, &j, &choice);

	i -= 1; //because 1-3 is 0-2 in array
	j -= 1; //because 1-3 is 0-2 in array
	choice = toupper(choice); //CAPITALIZE

	if(i > 2 || i < 0 || j > 2 || j < 0 || (choice != 'S' && choice != 'O')){
		printf("INVALID MOVE !\n");
		return -1;
	}//check if move is valid

	if(cellValue[i][j] != ' '){
		printf("SPACE IS TAKEN !\n");
		return -1;
	}//check if input space is empty

		
	cellValue[i][j] = choice; //input move
	return 0;
}

int player2Moves(){ //calls minimax for computer player, a.k.a. player 2
	int x = minimax(2, 0); // <-- 2 : player 2, depth: 0
	//printf("computer chooses 0: %d  --  %d -- %c\n", resI, resJ,resLetter);
	
	cellValue[resI][resJ] = resLetter;
	return 0;
}

int boardFull(){
	for (int i = 0; i < 3; i++){      //if you find at least one blank, then it is not full
		for(int j = 0; j < 3; j++){ //return 0;
			if (cellValue[i][j] == ' ')
				return 0;
		}
	}
	return 1; //return 1 if board is full
}

int squaresLeft(){ //counts how many squares there are left
	int sqrsLeft = 0;

	for (int i = 0; i < 3; i++){      
		for(int j = 0; j < 3; j++){ 
			if (cellValue[i][j] == ' ')
				sqrsLeft += 1;
		}
	}
	return sqrsLeft;
}

int checkWin(){ //+10 if pc wins, -10 if human wins

	int sqrsleft = squaresLeft();
	//row wins
	if ((cellValue[0][0] == 'S' && cellValue[0][1] == 'O' && cellValue[0][2] == 'S') || (cellValue[1][0] == 'S' && cellValue[1][1] == 'O' && cellValue[1][2] == 'S') || (cellValue[2][0] == 'S' && cellValue[2][1] == 'O' && cellValue[2][2] == 'S'))
		if (sqrsleft%2 == 0)
			return -10;
		else if(sqrsleft%2 != 0)
			return +10;

	//column wins
	if ((cellValue[0][0] == 'S' && cellValue[1][0] == 'O' && cellValue[2][0] == 'S') || (cellValue[0][1] == 'S' && cellValue[1][1] == 'O' && cellValue[2][1] == 'S') || (cellValue[0][2] == 'S' && cellValue[1][2] == 'O' && cellValue[2][2] == 'S'))
		if (sqrsleft%2 == 0)
			return -10;
		else if(sqrsleft % 2 != 0)
			return +10;

	//diagonal wins
	if ((cellValue[0][0] == 'S' && cellValue[1][1] == 'O' && cellValue[2][2] == 'S') || (cellValue[2][0] == 'S' && cellValue[1][1] == 'O' && cellValue[0][2] == 'S'))
		if (sqrsleft%2 == 0)
			return -10;
		else if(sqrsleft%2 != 0)
			return +10;

	return 0; //returns 0 if no one has won
}

int minimax(int player, int depth){ //maxplayer = 2, minplayer = 1
	int score = checkWin(); 
	
	if(score == 10){
		return score;
	}

	if(score == -10){   
		return score;
	}

	if(boardFull() == 1){ //then board is Full
		score = 0;
		return score;
	}

	if(player == 2){ //
		int i,j;
		int best = -1000; //negative value for maximizer
		int bestPos = -9999;
		char letter = 'O'; //these are for the following loop 
		int k = 0;

		while(k < 2){
			for(i = 0; i < 3; i++){
				for(j = 0; j < 3; j++){
					if (cellValue[i][j] == ' '){

						cellValue[i][j] = letter; 
		                        int tmp = minimax(1, depth+1);
		                        
		                        if(best < tmp){
		                            best = tmp;
		                        }
		                        //if (depth == 0) we start at root, and then examine its children
		                        if(depth==0){
		                            if(bestPos<best){
		                                bestPos = best;
		                                resI = i;
		                                resJ = j;
		                                resLetter = letter;
		                                
		                            }
		                        }
						cellValue[i][j] = ' ';
					}
				}
			}
			
			letter = 'S'; 
			k += 1;
		}
		return best;

	}else{ //here starts the minimizer a.k.a. player 1
		int i,j;
		int best = 1000; //positive value for minimizer
	
		char letter = 'O'; //these are for the following loop 
		int k = 0;

		while(k < 2){
			for(i = 0; i < 3; i++){
				for(j = 0; j < 3; j++){
					if (cellValue[i][j] == ' '){

						cellValue[i][j] = letter; 
						
		                        int tmp = minimax(2, depth+1);
		                        if(best > tmp){
		                            best = tmp;	    
		                        }
		               
						//undo move
						cellValue[i][j] = ' ';

					}
				}
			}
				
			letter = 'S'; 
			k += 1;
		}
		return best; 
	}
}