/*  Introduction Paragraph: 

		This program implements the Game of Life and has 3 functions, countLiveNeighbor, updateBoard, and aliveStable. The first function, 
	countLiveNeighbor keeps track of the number of alive neighbor cells to a specific cell. The updateBoard function creates another 1-D array, new_board. The function
	then calls the countLiveNeighbor function and determines the live/dead cells in new_board based on the specific conditions and updates the entire board using 
	new_board. Lastly, the aliveStable function checks whether or not the current board will be updated for the next step and returns 1 if it does not, and 0 if it does. 
*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int liveneighbor = 0; 										// initialize liveneighbor counter and set to 0
int i, j; 
	for(i = (row-1); i <= (row+1); i++){
		if ((i < boardRowSize) && (i >= 0)){
			for( j = (col-1); j <= (col+1); j++){
				if ((j< boardColSize) && (j >= 0)){ 		// loop through rows and columns, while making sure that it is within the boundaries of the array
					if (!((i == row) && (j == col))){ 		// check that you are not checking the current cell itself
						if (board[i*boardColSize+j] == 1){	
							liveneighbor++; }				// if 1 is found, increment the liveneighbor counter by 1
					}
				}
			}
		}
	}
return liveneighbor; 


}
/*
 * Update the game board to the next step
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */

/* updates the board based on the following alive(1)/dead(0) conditions: 
		1.) live cell stays alive if it has 2 or 3 alive neighbors or else it dies
		2.) dead cells turns alive if it has exactly 3 live neighbors 
*/
void updateBoard(int* board, int boardRowSize, int boardColSize) {	
	int size = boardRowSize * boardColSize; 										
	int new_board[size];															// create new array new_board
	int i, j, count = 0;
	for (i = 0; i < boardRowSize; i++){	
		for (j = 0; j < boardColSize; j++){											// loop through rows and cols 
			count = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); 	// call countLiveNeighbor function and set the return value to the variable count
			if(board[i * boardColSize + j] == 0){									// check for next update values based on alive/dead conditions and put values into new_board
				if (count == 3)
					new_board[i * boardColSize + j] = 1; 
				else
					new_board[i * boardColSize + j] = 0; 
			}
			if(board[i * boardColSize + j] == 1){
				if ((count == 2) || (count ==3))
					new_board[i * boardColSize + j] = 1; 
				else
					new_board[i * boardColSize + j] = 0; 
			}
		}
	}
		
	for (i = 0; i < boardRowSize; i++){
		for (j = 0; j < boardColSize; j++){
			board[i * boardColSize + j] = new_board[i * boardColSize + j];			// update the entire board with new_board
		}
	}
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 

int aliveStable(int* board, int boardRowSize, int boardColSize){
int size = boardRowSize * boardColSize; 
int before_board[size];   														// create a new array before_board
int i, j; 

for (i = 0; i < boardRowSize; i++){
	for (j = 0; j < boardColSize; j++){
		before_board[i * boardColSize + j] = board[i * boardColSize + j];		// copy values from each cell of board into before_board
	}
}

updateBoard(before_board, boardRowSize, boardColSize);							// call updateBoard function to update board 

for (i = 0; i < boardRowSize; i++){
	for (j = 0; j < boardColSize; j++){
		if (board[i * boardColSize + j] != before_board[i * boardColSize + j]) 	// check if updates occurred in each cell throughout the entire board & compare it to each cell of the before_board
			return 0; 															// if updated, return 0
	}
}
return 1; 																		// otherwise return 1

}

				
				
			

