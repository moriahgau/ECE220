#include "sudoku.h"

/* Introduction Paragraph: 
	This program uses several functions in order to recursively solve a sudoku puzzle. The is_val_in_row function checks whether 
or not the value already exists in the same row. The is_val_in col function checks whether or not the value already exists in the same column. The 
is_val_in_3x3_zone function then also checks if it already exists in the same zone. The is_val_valid function calls the previous three functions and checks whether or not it is legal
to fill a cell with the given number. Finally, the solve_sudoku function solves a sudoku by utilizing recursion. It fills a cell with a number and recursively backtracks to check its validity. 
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
	int col; 
	for (col = 0; col <= 8; col++){		// increment through columns to check if the value already exists in the row
		if(val == sudoku[i][col])		
			return 1; 					// if value is found to already exist, return 1
	}
	
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
	int row; 
	for (row = 0; row <= 8; row++){		// increment through rows to check if the value already exists in the column
		if(val == sudoku[row][j])
			return 1; 					// if value is found to already exist, return 1
	}
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i >= 0 && i < 9);

  // BEG TODO
	int row, col, x, y, w, z; 

	x = i/3;		// divide i by 3 to find the zone's (zone with (i, j)) row location (0-2)
	y = j/3;		// divide j by 3 to find the zone's column location (0-2)
	w = 3*x; 		// multiply x by 3 to find the starting row of the zone
	z = 3*y; 		// multiply y by 3 to find the starting column of the zone
	
	for (row = w; row <= w + 2; row++){
		for (col = z; col <= z + 2; col++){		// increment through the zone's rows and columns
			if (val == sudoku[row][col])		
				return 1;			// if value is found to already exist in the zone, return 1
		}
	}		
				
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
	int rowcheck, colcheck, zonecheck; 
	rowcheck = is_val_in_row(val, i, sudoku); 			
	colcheck = is_val_in_col(val, j, sudoku); 
	zonecheck = is_val_in_3x3_zone(val, i, j, sudoku);		// call functions and set variables equal to their return value

	if( (rowcheck == 0) && (colcheck == 0) && (zonecheck == 0))	// check if the return values of all the functions are 0

		return 1;						// if valid, return 1
	else
  		return 0;	
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
// backtracking, recursive code
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
	int i, j, row, col, valid, number, flag = 1;			// declare all variables
	for(i = 0; i < 9; i++){
		for(j=0; j < 9; j++){					// increment through each row and column to check all values in the sudoku
			if(sudoku[i][j] == 0)				// check if cell is filled
				flag = 0;			
		}
	}
	if(flag == 1)							// if cell is filled, return 1
		return 1;
	else{							
		for(i = 0; i < 9; i++){
			for(j=0; j < 9; j++){			
				if(sudoku[i][j] == 0){			// cell is not filled, so increment through i and j to find the location of the unfilled cell
					row = i; 			// set cell i location to row
					col = j;			// set cell j location col
				}
			}
		}
	}
	
	for(number = 1; number <= 9; number++){				// increment through numbers 1 through 9
		valid = is_val_valid(number, row, col, sudoku);		// call is_val_valid function to check for number's validity and set variable valid to its return value
		if( valid == 1){
			sudoku[row][col] = number;			// if number is valid, put number into location of unfilled cell
			if(solve_sudoku(sudoku)){			// recursively check if solutions for all blanks are found
				return 1;}
			sudoku[row][col] = 0;				// if solution not found, set cell to 0 and try another number			 
		}
	}
  return 0;								// no solution found
  // END TODO.
}
// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





