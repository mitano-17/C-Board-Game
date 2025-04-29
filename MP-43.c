/*
	LASTNAME1, FIRSTNAME1: KAWACHI, HIDEKI SECTION1: S13
	LASTNAME2, FIRSTNAME2: FURIGAY, RALPH ANGELO SECTION2: S13
	LASTNAME2, FIRSTNAME2: ERMITANO, KATE JUSTINE SECTION2: S17
	DATE SUBMITTED: 24/05/2021
*/

#include <stdio.h>

/*
	TO DO: change the #include below to your own file/solution. You are not allowed to include other files.
*/

#include "FUNCTIONS-43.c"

/*
	This is the main() function for testing your solution.
*/

int main(){

	// 3D int array for the win conditions
	int W[4][3][2] = {
		{{1,4},{2,4},{3,4}},
		{{2,2},{3,3},{4,4}},
		{{2,3},{3,2},{4,1}},
		{{4,2},{4,3},{4,4}}
	};

	// 2D int array for the lose conditions
	int H[5][2] = {{1, 1},{1, 2},{1, 3},{2, 1},{3, 1}};

	// 2D array board of moves for Ord
	int Ord[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	// 2D array board of moves for Cha
	int Cha[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	// 2D array containing free spots
	int Free[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	// 2D containing all inputs of the players
	int PInput[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	// declare variables
	int turn =1, size = 4, result = -1, accept = 0;

	// perform the game until either Cha or Ord wins
	while(result == -1){
		// get result if there is a winning layer or not
		result = GameOver(Cha,Ord,W,H,Free,size);

		// call the function to display the board
		Display(Cha,Ord,size);

		if(result == -1){
			// get the input by calling the function and store the result
			accept = Input(turn,PInput,Free,Ord);
		}

		// if there is input
		if(accept == 1){
			// switch players
			NextPlayerMove(PInput,H,Free,Cha,Ord,&turn,size);
			// get result if there is a winning layer or not
			result = GameOver(Cha,Ord,W,H,Free,size);
		}

		// update how many spaces do not contain any input
		UpdateFree(Free,Ord,Cha);

		// reset the board
		Reset(PInput);
	}

	// call the function to display the board
	Display(Cha,Ord,size);

	// condition for Cha winning
	if(result == 1){
		printf("\n\nPlayer Cha Wins!!\n");
	}

	// condition for Ord winning
	else if(result == 0){
		printf("\n\nPlayer Ord Wins!!\n");
	}
	
	return 0;
}