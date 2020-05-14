#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* Introduction Paragraph: 
	This program solves for a valid solution of a maze by utilizing the recursive depth-first-search algorithm. Each step towards finding
the solution is marked with a * until it runs into a wall, then the program backtracks to where another possible solution option is available and changes the cells that were previously visited to a ~. This is executed in a recursive manner until a solution is founding from 'S' (start) to 'E' (end). 
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
	maze_t *maze = (maze_t*)malloc(sizeof(maze_t));			// allocate memory according to maze size 	
	int i, j, width, height; 
	char character; 
    	FILE *file; 
	file = fopen(fileName, "r"); 					// open and the read file
	fscanf(file, "%d %d\n", &width, &height);  			
	
	maze->width = width; 						// store the height and width of the maze
	maze->height = height;
	maze->cells = (char**)malloc(height * sizeof(char*)); 		// allocate memory for the array

 	for(i = 0; i < height; i++){					// increment through rows and columns 
		maze->cells[i] = (char*)malloc(width * sizeof(char)); 	// allocate memory for the cells
		for(j = 0; j <= width; j++){
			fscanf(file, "%c", &character);
			if(character != '\n')				// check if the scanned character is not a newline
				maze->cells[i][j] = character; 		// set the cell to that character
			//else
			//	continue;			
			if(character == 'S'){				// check if the scanned character is a S
					maze->startRow = i; 
					maze->startColumn = j;		// set startRow and startColumn to i and j respectively 
			}
			if(character == 'E'){				// check if the scanned character is an E
				maze-> endRow = i; 
				maze-> endColumn = j;			// set the endRow and endColumn to i and j respectively 
			}
		}
	}
	fclose(file); 							// close the file
	return maze;							// return pointer
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
	int i;
	for(i = 0; i < maze->height; i++){			// increment through all the rows of the maze
		free(maze->cells[i]);				// free the memory for every cell
	}
	free(maze->cells); 					// free the memory in the array
	free(maze); 						// free the entire struct
		
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
	int i, j; 
	for(i = 0; i < maze->height; i++){
		for(j = 0; j < maze-> width; j++){		// increment through the maze's bounds
			printf("%c", maze->cells[i][j]); 	// print out each character in each cell
		}
		printf("\n"); 					// print newline
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

	if(row < 0 || row > (maze->height)-1 || col < 0 || col > (maze->width)-1)				// check if the cell is outside of bounds, return 0
		return 0;
	if(maze->cells[row][col]== '%' || maze->cells[row][col] == '~' || maze->cells[row][col] == '*')		// check if the cell is not empty, return 0
		return 0;
	if(row==maze->endRow && col==maze->endColumn){								// check if the cell is the end of the maze, return 1
		maze->cells[maze->startRow][maze->startColumn] = 'S';						// fill the cell at startRow and startColumn with 'S'
		return 1; 
	}
	if(maze->cells[row][col] == ' ' || maze->cells[row][col] == 'S')					// set the cell as part of the solution path
		maze->cells[row][col] = '*'; 
	if(solveMazeDFS(maze, col-1, row) == 1)									// recursively check and solve
		return 1; 
	if(solveMazeDFS(maze, col+1, row) == 1)
		return 1; 
	if(solveMazeDFS(maze, col, row-1) == 1)
		return 1; 
	if(solveMazeDFS(maze, col, row+1) == 1)
		return 1;
 
	if(maze->cells[row][col] == '*' && maze->cells[row][col] != 'S')					// unmark cell as part of the solution and mark visited with ~
		maze->cells[row][col] = '~'; 
	
	
    return 0;													// return 0
}
