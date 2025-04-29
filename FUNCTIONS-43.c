/*
	LASTNAME1, FIRSTNAME1: KAWACHI, HIDEKI SECTION1: S13
	LASTNAME2, FIRSTNAME2: FURIGAY, RALPH ANGELO SECTION2: S13
	LASTNAME2, FIRSTNAME2: ERMITANO, KATE JUSTINE SECTION2: S17
	DATE SUBMITTED: 24/05/2021

	Note that if you compile JUST this file only, you will get an error that says "undefined reference to WinMain" (for DEVCPP users).
	You'll have to include this file first in MP-43.c via #include, and then it is the MP-43.c that you you should compile to produce MP-43.exe file.
*/

#include <stdio.h>

/*
	DESCRIPTION: Sets inputs back to zero in case there is a misinput
	PARAMETERS: pos[4][4] - the board/matrix
	RETURN TYPE: not applicable
*/

void Reset(int pos[4][4]){
	// declare rows and columns
	int row, col;

	for(row = 0; row<4; row++)
	{
		for(col = 0; col<4; col++)
		{
			pos[row][col] = 0;
		}
	}
}

/*
	DESCRIPTION: Function that puts all inputs of both players to the board
	PARAMETERS: pos[4][4] - the board/matrix
	H[5][2] - H set
	Free[4][4] - array containing untouched spaces
	Cha[4][4] - Cha's board
	Ord[4][4] - Ord's board
	*turn - turn switch
	size - size of row and column
	RETURN TYPE: Not applicable
*/
void NextPlayerMove(int pos[4][4], int H[5][2], int Free[4][4], int Cha[4][4], int Ord[4][4], int *turn, int size){
	//NOTE: HState = 1 = TRUE
	// define variables
	int HState = 0, FreeState = 0, OrdState = 0, row, col, Hrow = 0, OrdCard = 0;
	// go around the board
	for(row = 0; row<size; row++)
	{
		for(col = 0; col<size; col++)
		{
			// if the position is taken
			if(pos[row][col] == 1)
			{
				while(Hrow<5)
				{
					if(row == H[Hrow][0]-1 && col == H[Hrow][1]-1)
					{
						// the position is inside set H
						HState = 1;
					}
					// inrement
					Hrow++;
				}
			}
		}
	}

	// checking of FreeState
	for(row = 0; row<size; row++){
		for(col = 0; col<size; col++){
			if(pos[row][col] == Free[row][col]){
				//pos is inside Free
				FreeState = 1;
			}
		}
	}

	// checking of Ordstate
	for(row = 0; row<size; row++)
	{
		for(col = 0; col<size; col++)
		{
			if(pos[row][col] == Ord[row][col])
			{
				//pos is inside Ord
				OrdState = 1;
			}
		}
	}

	//checking of cardinality of Ord
	for(row = 0; row<size; row++)
	{
		for(col = 0; col<size; col++)
		{
			if(Ord[row][col] == 1)
			{
				//pos is inside Ord
				OrdCard++;
			}
		}
	}

	// condition if it is Cha's turn
	if(*turn == 1 && HState == 0 && FreeState == 1)
	{
		//transfering of Pos to Cha
		for(row = 0; row<size; row++)
		{
			for(col = 0; col<size; col++)
			{
				//if Pos has value, fill Cha
				if(pos[row][col] == 1)
				{
					Cha[row][col] = 1;
				}
			}
		}
		// switch to Ord
		*turn = 0;
	}

	// condition if it is Ord's turn
	else if(*turn == 0 && FreeState == 1 && OrdCard < 4)
	{
		//transfering of Pos to Ord
		for(row = 0; row<size; row++)
		{
			for(col = 0; col<size; col++)
			{
				//if Pos has value, fill Ord
				if(pos[row][col] == 1)
				{
					Ord[row][col] = 1;
				}
			}
		}
		// switch to Cha
		*turn = 1;
	}

	// condition if it is Ord's turn
	else if(*turn == 0 && OrdCard == 4 && OrdState == 1)
	{
		//transfering of Pos to Ord
		for(row = 0; row<size; row++)
		{
			for(col = 0; col<size; col++)
			{
				//if Pos has value, clear Ord
				if(pos[row][col] == 1)
				{
					Ord[row][col] = 0;
				}
			}
		}
	}

	// condition for the wrong input
	else{
		// call the reset function
		Reset(pos);
		printf("\nPlease Enter Correct Value\n");
	}
}

/*
	DESCRIPTION: Displays the board
	PARAMETERS: Cha[4][4] - Cha's board
	Ord[4][4] - Ord's board
	size - size of row and column
	RETURN TYPE: Not applicable
*/
void Display(int Cha[4][4], int Ord[4][4], int size){
	// declare row and column
	int row, col;

	// print the legend before the board
	printf("\nLegend: \n");
	printf("Cha - X\n");
	printf("Ord - O\n\n");
	printf(" 1 2 3 4");

	// print the board
	for(row = 0; row<size; row++)
	{
		// print the lines
		printf("\n -----------------\n");
		printf(" %d ",row+1);
		printf("|");

		for(col = 0; col<size; col++){
			// condition if the space is empty
			if(Cha[row][col] == 0 && Ord[row][col] == 0)
			{
				printf(" |");
				//printf("%d %d",Cha[row][col], Ord[row][col]);
			}

			// condition if Cha is in this position
			else if(Cha[row][col] == 1)
			{
				printf(" X |");
			}

			// condition if Ord is in this position
			else
			{
				printf(" O |");
			}
		}
	}
}

/*
	DESCRIPTION: Function to determine if there is a win
	PARAMETERS: Cha[4][4] - Cha's board
	Ord[4][4] - Ord's board
	W[4][3][2] - W set
	H[5][2] - H set
	Free[4][4] - array containing untouched spaces
	size - size of row and column
	RETURN TYPE: Return 0 if Ord wins.
	Return 1 if Cha wins.
	Return -1 otherwise.
*/
int GameOver(int Cha[4][4], int Ord[4][4], int W[4][3][2], int H[5][2], int Free[4][4], int size){
	// define variables
	int row=0, col, Wrow = 0, Wcol = 0, ChaWin = 0, OrdWin = 1;

	// loop to determine if Cha inputs the right values for winning
	while(row<4 && ChaWin != 3){

		// reset value of ChaWin for every set of W combinations
		ChaWin = 0;

		for(col = 0; col<3; col++){
			Wrow = W[row][col][0]-1;
			Wcol = W[row][col][1]-1;

			//if Cha has a value in all of the locations in one set of W combinations
			if(Cha[Wrow][Wcol] == 1){
				// increment number of wins
				ChaWin++;
			}
		}
		// increment rows
		row++;
	}

	// return a value if Cha wins
	if(ChaWin == 3)
	{
		return 1;
	}

	// set al variables back to the old values
	row = 0;
	col = 0;
	OrdWin = 1;

	// loop to determine if Ord inputs the right values for winning
	while(row<size && OrdWin == 1){
		while(col<3 && OrdWin == 1){
			Wrow = W[row][col][0] -1;
			Wcol = W[row][col][1] -1;

			// losing condition for Ord if there are no more free spots
			if(Free[Wrow][Wcol] == 0){
				// set winning count to 0
				OrdWin = 0;
			}
			col++;
		}
		col = 0;
		row++;
	}

	// return a value if Ord wins
	if(OrdWin == 1)
	{
		return 0;
	}

	// return a value if neither won
	else
	{
		return -1;
	}
}

/*
	DESCRIPTION: Function that retrieves all player inputs
	PARAMETERS: turn - turn switch
	pos[4][4] - the board/matrix
	Free[4][4] - array containing untouched spaces
	Ord[4][4] - Ord's board
	RETURN TYPE: Return 1 for successful inputs.
	Return 0 otherwise.
*/
int Input(int turn, int pos[4][4], int Free[4][4], int Ord[4][4])
{
	// define and define values
	int row=0,col=0, Orow, Ocol, OrdSize=0;

	// count how many spots have been taken
	for(Orow=0;Orow<4;Orow++)
	{
		for(Ocol=0;Ocol<4;Ocol++)
		{
			if(Ord[Orow][Ocol]==1)
			{
				OrdSize++;
			}
		}
	}

	// it is Cha's turn to input
	if(turn == 1)
	{
		printf("\n\nTurn : Player Cha\n");

		// ask for row number
		printf("Enter row number: ");
		scanf("%d",&row);

		// ask for column number
		printf("Enter column number: ");
		scanf("%d",&col);
		printf("\n");

		// corect input
		if(row<5 && col<5 && row>0 && col>0 && Free[row-1][col-1] == 0)
		{
			// decrement row and col
			row--;
			col--;
			// take the spot
			pos[row][col] = 1;
			return 1;
		}

		// misinput
		else
		{
			printf("\nError, please enter correct input\n");

			// reset the board
			Reset(pos);
			return 0;
		}
	}

	// it is Ord's turn to input
	else if(OrdSize < 4 && turn == 0)
	{
		printf("\n\nTurn : Player Ord\n");
		// ask for row number
		printf("Enter row number: ");
		scanf("%d",&row);
		// ask for column number
		printf("Enter column number: ");
		scanf("%d",&col);

		// corect input
		if(row<5 && col<5 && row>0 && col>0)
		{
			// corect input
			if(Free[row-1][col-1] == 0)
			{
				// decrement row and col
				row--;
				col--;
				// take the spot
				pos[row][col] = 1;
				return 1;
			}

			// misinput
			else
			{
				printf("\nError, please enter correct input\n");
				// reset the board
				Reset(pos);
				return 0;
			}
		}

		// misinput
		else
		{
			printf("\nError, please enter correct input\n");
			// reset the board
			Reset(pos);
			return 0;
		}
	}

	// it is Ord's turn to delete some values on the board
	else if(turn == 0 && OrdSize == 4)
	{
		// print the message
		printf("\n-------------------------\n");
		printf("Delete one of your tiles!\n");
		printf("-------------------------\n");
		// ask for row number
		printf("Enter row number: ");
		scanf("%d",&row);
		// ask for column number
		printf("Enter column number: ");
		scanf("%d",&col);

		// corect input
		if(row<5 && col<5 && row>0 && col>0 && Ord[row-1][col-1] == 1)
		{
			// decrement the row and col
			row--;
			col--;
			// take the spot
			pos[row][col] = 1;
			return 1;
		}

		// misinput
		else
		{
			printf("\nError, please enter correct input\n");
			// reset the board
			Reset(pos);
			return 0;
		}
	}
	return 0;
}

/*
	DESCRIPTION: Function that will update how many spots are untouched
	PARAMETERS: Free[4][4] - array containing untouched spaces
	Ord[4][4] - Ord's board
	Cha[4][4] - Cha's board
	RETURN TYPE: Not applicable
*/
void UpdateFree(int Free[4][4], int Ord[4][4], int Cha[4][4]){
	// declare row and column
	int row, col;

	// go around the board
	for(row = 0; row<4; row++)
	{
		for(col = 0; col<4; col++)
		{
			// if the spot has been taken
			if(Ord[row][col] == 1 || Cha[row][col] == 1)
			{
				Free[row][col] = 1;
			}

			// otherwise
			else
			{
				Free[row][col] = 0;
			}
		}
	}
}
/*******************************************************************************
WARNING!!! WARNING!!! WARNING!!!
YOU ARE NOT ALLOWED TO DEFINE the main() function in this file.
********************************************************************************/