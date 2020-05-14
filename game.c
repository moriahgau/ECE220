#include "game.h"
/* Introduction Paragraph
	The popular game "2048" is created in this program. The user inputs the dimensions of the board and a game is initialized using a pointer that points to the board. The first function is the make_game function which creates a game structure with the user inputted dimensions and initializes all the elements to -1 and returns a pointer. My second function is the remake_game function that performs the same actions as make_game but frees the allocated memory from the last game, while making sure that it will not be lost. Then, the get_cell function makes sure that the cells are within the bounds of the board and are valid, otherwise it returns NULL. Afterwards, we have the up, down, right, and left shift functions which allow the values to move along the board and merges the cells and updates the score if its conditions are met. The last function I had to create is the legal_move_check function that checks if there are still any valid moves that can be made within the boundaries that are set and returns 1 if true, otherwise 0. 

*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	int i, j; 
	
	mygame->score = 0; 		// initialize rows, cols, and score
	mygame->rows = rows; 
	mygame->cols = cols; 
	for(i = 0; i < rows; i++){
		for(j= 0; j < cols; j++){
			mygame->cells[i*cols+j] = -1; // increments through all cells and initializes all values to -1 to indicate empty spaces
		}
	} 
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	int i, j; 
	
	(*_cur_game_ptr)->score = 0; 		//re-initializes rows, cols, and score for current game 
	(*_cur_game_ptr)->rows = new_rows; 
	(*_cur_game_ptr)->cols = new_cols; 
	for(i = 0; i < new_rows; i++){
		for(j= 0; j < new_cols; j++){
			(*_cur_game_ptr)->cells[i*new_cols+j] = -1; // increments through all cells and initializes all values to -1 to indicate empty spaces
		}
	} 
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	if((row >= 0) && (row < cur_game->rows)){					// makes sure that rows and cols are within the bounds of the current game 
		if((col >= 0) && (col< cur_game->cols)){
			return &(cur_game->cells[row * (cur_game->cols) + col]);	// returns the address of the index's pointer
		}
	}
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
	// combine only if k-1 != combined
	int i, j, k, rows, cols, combined, flag = 0, target_row;		// initialize variables, rows to the # of current game's rows, and cols to the # of current game's col
	rows = cur_game->rows;
	cols = cur_game->cols; 
	for(i = 0; i <cols; i++){						// increment through all cols then rows, except for the first row since it cannot shift up
		combined = -1;							// set combined to -1
		for(j= 1; j < rows; j++){					
			if (cur_game->cells[cols * j +i] != -1){		// check if the cell is empty				
				for (k= 0; k < j; k++){				
				target_row = j;					// set target_row to current row 
					
					if(cur_game->cells[cols * k + i] == -1)	// new possible target_ row is found
						break;
				}
				if (k < j){								// check that k is less than j
				cur_game->cells[k * cols + i] = cur_game->cells[j * cols + i];		// shift the value from the original cell to the cell in the same column but row k
				cur_game->cells[j * cols + i] = -1;					// set the original cell value to -1
				target_row = k;								// set target_row to k
				flag = 1;								// set flag to 1 to indicate a successful move 

				} 
			} 
			
							
				if (target_row-1 != combined){						// check if target_row - 1 is not equal to the value in combined
					if ((cur_game->cells[(target_row-1) * cols + i] == cur_game->cells[(target_row) * cols + i]) && (cur_game->cells[(target_row) * cols+i] != -1)){ //check if the value in the cell of target_row above is the same as of the target_row and the value in the cell of target_row is not -1

						cur_game->cells[(target_row-1) * cols + i] = cur_game->cells[target_row * cols + i] * 2;	// double the value in the cell of target_row above
						cur_game->score = cur_game->score + (cur_game->cells[target_row * cols + i] * 2);		// set score to the sum of the score and the merged value
						cur_game->cells[target_row * cols + i] = -1;							// set cell of the target_row to -1
						combined = target_row-1;									// set combined equal to the target_row -1
						flag = 1;											// set flag to 1 to indicate successful move 
					}
				}
			
		}
	}
    return flag;																// return the value of the flag
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
	int i, j, k, rows, cols, combined, flag = 0, target_row;		// initialize variables, rows to the # of current game's rows, and cols to the # of current game's col
	rows = cur_game->rows;
	cols = cur_game->cols; 
	for(i = 0; i <cols; i++){						// increment through all cols then rows with rows starting at the bottom of the game board
		combined = -1;							// set combined to -1
		for(j= rows-1; j >= 0; j--){
			if (cur_game->cells[cols * j +i] != -1){		// check if the cell is empty	
				target_row = j;					// set target_row to j
				for (k= rows-1; k > j; k--){
					
					if(cur_game->cells[cols * k + i] == -1) // found potential new target_row
						break;
				}
				if (k > j){					// check that k is less than j
				cur_game->cells[k * cols + i] = cur_game->cells[j * cols + i];	// shift the value from the original cell to the cell in the same column but row k
				cur_game->cells[j * cols + i] = -1;		// set the original cell value to -1
				target_row = k;					// set target_row to k
				flag = 1;					// set flag to 1 to indicate a successful move 
				} 
			}			
				if (target_row+1 != combined){			// check if target_row + 1 is not equal to the value in combined
					if ((cur_game->cells[(target_row+1) * cols + i] == cur_game->cells[(target_row) * cols + i]) && (cur_game->cells[(target_row) * cols+i] != -1)){ //check if the value in the cell of target_row below is the same as of the target_row and the value in the cell of target_row is not -1
						cur_game->cells[(target_row+1) * cols + i] = cur_game->cells[target_row * cols + i] * 2;	// double the value in the cell of target_row below
						cur_game->score = cur_game->score + (cur_game->cells[target_row * cols + i] * 2);		// set score to the sum of the score and the merged value
						cur_game->cells[target_row * cols + i] = -1;							// set cell of the target_row to -1
						combined = target_row+1;									// set combined equal to the target_row + 1
						flag = 1;											// set flag to 1 to indicate successful move 
					}
				}
			
		}
	}
    return flag;			// return the value of the flag
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
	int i, j, k, rows, cols, combined, flag = 0, target_col;		// initialize variables, rows to the # of current game's rows, and cols to the # of current game's col
	rows = cur_game->rows;
	cols = cur_game->cols; 
	for(i = 0; i <rows; i++){						// increment through all rows then cols except for the first col because it cannot be shifted to the left
		combined = -1;							// set combined to -1
		for(j= 1; j < cols; j++){
			if (cur_game->cells[i * cols +j] != -1){		// check if the cell is empty	
				
				target_col = j;					// set target_col to j
				for (k= 0; k < j; k++){
					
					if(cur_game->cells[i * cols + k] == -1) // found potential new target_col
						break;
				}
				if (k < j){					// check if k < j
				cur_game->cells[i * cols + k] = cur_game->cells[i * cols + j];	// shift the value from the original cell to the cell in the same row but col k
				cur_game->cells[i * cols + j] = -1;		// set the original cell value to -1
				target_col = k;					// set target_col to k
				flag = 1;					// set flag to 1 to indicate a successful move 
				} 
			}
			if (target_col-1 != combined){			// check if target_col - 1 is not equal to the value in combined
					if ((cur_game->cells[(target_col-1) + cols * i] == cur_game->cells[(target_col) + cols * i]) && (cur_game->cells[(target_col) + cols*i] != -1)){ //check if the value in the cell of the col before target_col is the same as of the target_col and the value in the cell of target_col is not -1
						cur_game->cells[(target_col-1) + cols * i] = cur_game->cells[target_col + cols * i] * 2;	// double the value in the cell of the col before target_col
						cur_game->score = cur_game->score + (cur_game->cells[target_col + cols * i] * 2);		// set score to the sum of the score and the merged value
						cur_game->cells[target_col + cols * i] = -1;							// set cell of the target_col to -1
						combined = target_col-1;									// set combined equal to the target_col - 1
						flag = 1;											// set flag to 1 to indicate successful move 
					}
				}
			
		}
	}
    return flag;			// return value of the flag
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
	int i, j, k, rows, cols, combined, flag = 0, target_col;		// initialize variables, rows to the # of current game's rows, and cols to the # of current game's col
	rows = cur_game->rows;
	cols = cur_game->cols; 
	for(i = 0; i <rows; i++){						// increment through all rows then cols with cols starting at the rightmost side of the gameboard
		combined = -1;				// set combined to -1
		for(j= cols -1; j >= 0; j--){
			if (cur_game->cells[cols * i +j] != -1){		// check if the cell is empty
				
				target_col = j;					// set the target_col to j
				for (k= cols-1; k > j; k--){
					
					if(cur_game->cells[cols * i + k] == -1) // found potential new target_col
						break;
				}
				if (k > j){		// check if k > j
				cur_game->cells[cols * i + k] = cur_game->cells[cols * i + j];	// shift the value from the original cell to the cell in the same row but col k
				cur_game->cells[cols * i + j] = -1;				// set the original cell value to -1	
				target_col = k;							// set target_col to k
				flag = 1;							// set flag to 1 to indicate successful move
				} 
			}
			if (target_col+1 != combined){				// check if target_col + 1 is not equal to the value in combined
					if ((cur_game->cells[(target_col+1) + cols * i] == cur_game->cells[(target_col) + cols * i]) && (cur_game->cells[(target_col) + cols*i] != -1)){ //check if the value in the cell of the col after target_col is the same as of the target_col and the value in the cell of target_col is not -1
						cur_game->cells[(target_col+1) + cols * i] = cur_game->cells[target_col + cols * i] * 2;	// double the value in the cell of the col after target_col	
						cur_game->score = cur_game->score + (cur_game->cells[target_col + cols * i] * 2);		// set score to the sum of the score and the merged value
						cur_game->cells[target_col + cols * i] = -1;							// set cell of the target_col to -1
						combined = target_col+1;									// set the combined value to target_col + 1
						flag = 1;											// set flag to 1 to indicate successful move
					}
				}
			
		}
	}
    return flag;			// return the value of the flag
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
	int i, j, rows, cols, flag = 0, *c;				// initialize variables, rows to the # of current game's rows, and cols to the # of current game's col
	rows = cur_game->rows;
	cols = cur_game->cols; 
	for(i = 0; i< rows; i++){					// increment through every cell
		for(j= 0; j <cols; j++){
			if (cur_game->cells[i * cols + j] == -1)	// check if there are any empty cells
				flag = 1;				// set flag to 1 if there are any empty cells
		}
	}
	for(i = 0; i < rows; i++){					// increment through all rows then all cols
		for(j = 0; j < cols; j++){
			c = get_cell(cur_game, i+1, j);			// call get_cell with parameters cur_game, i+1, and j and set c to its return value
			if (c != NULL){					// check if c is NULL
				if( (cur_game->cells[(i+1)*cols + j] == cur_game->cells[i*cols+j]) || (cur_game->cells[(i+1)*cols + j] == -1)) // check if value in the cell of the same col but the row after the current row is the same as in the current row OR if the value in the cell in the same col but the row after is -1
					flag = 1;			// if true, set flag to 1
			}
			c = get_cell(cur_game, i-1, j);			// call get_cell with parameters cur_game, i-1, and j and set c to its return value
			if (c != NULL){					// check if c is NULL
				if( (cur_game->cells[(i-1)*cols + j] == cur_game->cells[i*cols+j]) || (cur_game->cells[(i-1)*cols + j] == -1)) // check if value in the cell of the same col but the row before the current row is the same as in the current row OR if the value in the cell in the same col but the row before is -1
					flag = 1;			// if true, set flag to 1
			}
		}
	}

	for(j = 0; j < cols; j++){					// increment through all cols then all rows
		for(i = 0; i < rows; i++){
			c = get_cell(cur_game, i, j+1);			// call get_cell with parameters cur_game, i, and j+1 and set c to its return value
			if (c != NULL){					// check if c is NULL
				if( (cur_game->cells[i*cols + (j+1)] == cur_game->cells[i*cols+j]) || (cur_game->cells[i*cols + (j+1)] == -1)) // check if value in the cell of the same row but the col to the right of the current col is the same as in the current col OR if the value in the cell in the same row but the col to the right is -1
					flag = 1;			// if true, set flag to 1
			}
			c = get_cell(cur_game, i, j-1);			// call get_cell with parameters cur_game, i, and j-1 and set c to its return value
			if (c != NULL){					// check if c is NULL
				if( (cur_game->cells[i*cols + (j-1)] == cur_game->cells[i*cols+j]) || (cur_game->cells[i*cols + (j-1)] == -1))		 // check if value in the cell of the same row but the col to the left of the current col is the same as in the current col OR if the value in the cell in the same row but the col to the left is -1
					flag = 1;			// if true, set flag to 1
			}
		}
	}
	return flag;		// return the value of the flag
}

/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
