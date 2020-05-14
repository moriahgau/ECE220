#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>

/*Introduction Paragraph: 
	This program, using linked lists, stores sparse matricies, writes the data in a sparse matrix to a text file, adds sparse matricies, multiplies sparse matrices, and frees all the memory associated with a given matrix. 
*/

void delete(sp_tuples *mat_t, int row, int col);		// declare the delete helper function
sp_tuples * load_tuples(char* input_file)
{
	sp_tuples * matrix = (sp_tuples*)malloc(sizeof(sp_tuples));		// allocate memory according to sp_tuples size 	
	matrix->tuples_head = NULL; 									// initialize matrix values
	matrix->nz = 0;

	int row, col, totalrows, totalcols;					// initialize variables		
	double value; 
	FILE *file; 
	file = fopen(input_file, "r"); 						// open and read file for rows and cols
	if(file == NULL)									// make sure file is found
		return NULL; 
	fscanf(file, "%d %d\n", &totalrows, &totalcols); 	// scan for the totalrows and totalcols

	matrix->m = totalrows; 								// initialize matrix values
	matrix->n = totalcols; 
	

	while(!feof(file)){									// while the end of the file is not yet reached
		fscanf(file, "%d %d %lf\n", &row, &col, &value);// scan for row, col, and value
		set_tuples(matrix, row, col, value); 			// call set_tuples function
	}

	fclose(file); 				// close the file

    return matrix;				// return the matrix
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
	sp_tuples_node *currentnode = mat_t->tuples_head; 			// set pointer currentnode = mat_t->tuples_head
	while(currentnode != NULL){									// check that the curretnode is not NULL
		if(currentnode->row == row){
			if(currentnode->col == col)
				return currentnode->value;  					// check for the same row and col as in the matrix and return its value if found
		}
		currentnode = currentnode->next;						// iterate through to check next node
	}
    return 0;		
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{		
	// when list is empty, allocate memory and insert node to linked list
	if(mat_t->tuples_head == NULL){
	sp_tuples_node *node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
	node->row = row; 
	node->col = col;
	node->value = value; 
	mat_t->tuples_head = node;
	node->next = NULL;
	mat_t->nz++;												//increment mat_t->nz
    return;}
	sp_tuples_node *currentnode = mat_t->tuples_head;			// set pointer currentnode = mat_t->tuples_head
	
	if(value ==0){												// check if value is 0
		delete(mat_t, row, col); 								// call delete helper function
		return;	
	}
	currentnode = mat_t->tuples_head;														// set pointer currentnode = mat_t->tuples_head
	if ((row *mat_t->n + col) < (currentnode->row * mat_t->n + currentnode->col)){			// find correct location when at the beginning of linked list
				if(currentnode->row == row && currentnode->col == col)						// if node at row and col exist, replace its value
					currentnode->value = value;
				else{
					sp_tuples_node *node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));	// allocate memory for node and insert to correct location in linked list 
					node->row = row; 
					node->col = col;
					node->value = value; 
					node->next = currentnode;
					mat_t->tuples_head = node;
					mat_t->nz++;															//increment nz count
					return; 	
				}		
	}
	while(currentnode != NULL)
		{if ((row * mat_t->n + col) == (currentnode->row * mat_t->n + currentnode->col)){	// check if elements already exist
				currentnode->value = value;													// replace its value
				return; }	
		currentnode = currentnode->next;													//traverse through 
	}	

	currentnode = mat_t->tuples_head;	
	while(currentnode->next != NULL && ((currentnode->next->row * mat_t->n + currentnode->next->col) < (row * mat_t->n + col)))		// find correct location when in the middle or at the end of list 
		currentnode = currentnode->next;
	if(currentnode->next == NULL){														// insertion of node at the end of the list 																								
		sp_tuples_node *node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
		node->row = row; 
		node->col = col;
		node->value = value; 
		currentnode->next = node;
		node->next = NULL; 
		mat_t->nz++;																	//increment mat_t->nz	
		return;
	}
	sp_tuples_node * node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));			// insertion of node in the middle of the list
	node->row = row; 
	node->col = col;
	node->value = value; 
	node->next = currentnode->next;
	currentnode->next = node; 
	mat_t->nz++;																		//increment nz count
	return; 	
	}			



void save_tuples(char * file_name, sp_tuples * mat_t) 
{
	int therow, thecol; 								// initialize rows, cols, and thevalue
	double thevalue; 
	FILE *file; 
	file = fopen(file_name, "w"); 						// open and write to file
	if(file == NULL)									// make sure file is found
		return; 
	fprintf(file, "%d %d\n", mat_t->m, mat_t->n);		// print to file mat_t->row and mat_t->col

	sp_tuples_node *currentnode = mat_t->tuples_head;	// set pointer currentnode = mat_t->tuples_head
	while(currentnode != NULL){							// check if currentnode is not equal to NULL
		therow = currentnode->row; 						// set values for therow, thecol, and thevalue
		thecol = currentnode->col; 
		thevalue = currentnode->value;
		fprintf(file, "%d %d %lf\n", therow, thecol, thevalue);		// print therow, thecol, thevalue to the file
		currentnode = currentnode->next;							// traverse through nodes
	}

	fclose(file); 				// close the file

}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
	double c; 
	sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples));	// allocate memory for a matrix matC according to sp_tuples size 
	sp_tuples_node *currentnode = matA->tuples_head;			// set pointer currentnode = matA->tuples_head	
	matC->tuples_head = NULL;									// initialize matC values 
	matC->m = matA->m;
	matC->n = matA->n;	
	matC->nz = 0; 

	if(matA->m != matB->m || matA->n != matB->n)			// check that matA addition with matB is possible
		return NULL; 
	while(currentnode != NULL){								// while currentnode is not NULL
		int i = currentnode->row; 							// initialize i and j
		int j = currentnode->col; 
		c = gv_tuples(matA, i, j); 							// find value of matC by calling gv_tuples function on matA with row i and col j
		set_tuples(matC, i, j, c);							// call set_tuples function for matC with row i, col j, and value c
		currentnode = currentnode->next;					// traverse 
	}

	currentnode = matB->tuples_head;						// set pointer currentnode = matB-> tuples_head
	while(currentnode != NULL){								// while currentnode is not NULL
		int i = currentnode->row; 							// initialize i and j
		int j = currentnode->col; 
		c = gv_tuples(matB, i, j) + gv_tuples(matC, i, j);	// find value of matC by calling gv_tuples function on matB and matC with row i and col j
		set_tuples(matC, i, j, c);							// call set_tuples function for matC with row i, col j, and value c
		currentnode = currentnode->next;					// traverse
	}
	return matC;											// return matC

	
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
	double c; 														// initialize c
	sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples));		// allocate memory for matC according to sp_tuples size 
	sp_tuples_node *currentnode = matA->tuples_head;				// set pointer currentnode = mat_A->tuples_head	
	matC->tuples_head = NULL;										//initialize matC values
	matC->m = matA->m;
	matC->n = matB->n;	
	matC->nz = 0; 

	if(matA->n != matB->m)											// check that matA can be multiplied with matB
		return NULL; 
	
	while(currentnode != NULL){										// while currentnode is not NULL
		int iA = currentnode->row; 									// initialize iA and jA
		int jA = currentnode->col;
		sp_tuples_node *currentnode2 = matB->tuples_head;			// set pointer currentnode = mat_B->tuples_head
		while(currentnode2 != NULL){								// while currentnode is not NULL
			int iB = currentnode2->row; 							// initialize iB and jB
			int jB = currentnode2->col;
			if(iB == jA){											// check if iB and jA are equal
				c = gv_tuples(matC, iA, jB)+gv_tuples(matA, iA, jA) * gv_tuples(matB, iB, jB);	// find value of matC by calling gv_tuples function on matA, matB, and matC with row iA, row iB, col jA, and col jB
				set_tuples(matC, iA, jB, c);						// call set_tuples function for matC with row iA, col jB, and value c	
			}
			currentnode2 = currentnode2->next;						// traverse
		}
		currentnode = currentnode->next;
		
	}

	return matC; 												// return matC
}


	
void destroy_tuples(sp_tuples * mat_t){ 
	sp_tuples_node *currentnode = mat_t->tuples_head; 			// initialize and set pointer currentnode = mat_t->tuples_head
	sp_tuples_node *temp = currentnode;							// initialize a temperary node to currentnode;
	while(currentnode != NULL){									// check that currentnode is not NULL
		temp = temp->next;		
		free(currentnode);										// free all the memory in the currentnode
		currentnode = temp; 									// set currentnode to temp->next 
	}
	free(mat_t); 												// free the entire struct
    return;
}  

void delete(sp_tuples * mat_t, int row, int col){		

	sp_tuples_node *prev = NULL; 								// initialize previous pointer to NULL 
	sp_tuples_node *currentnode = mat_t->tuples_head; 			// set pointer currentnode = mat_t->tuples_head
	if(currentnode->row == row && currentnode->col == col){		// check for the same row and col and delete if found by freeing memory and updating pointers
			mat_t->tuples_head = currentnode->next;				// set mat_t->tuples_head pointer to currentnode->next
			free(currentnode);									// free currentnode
			mat_t->nz--;										//decrement nz count
			return; 
	}					  		
	while(currentnode != NULL){									// check that the currentnode is not NULL		
		if(currentnode->row == row && currentnode->col == col){	// check for the same row and col and delete if found by freeing memory and updating pointers
			prev->next = currentnode->next; 
			free(currentnode);				//free currentnode
			mat_t->nz--;					//decrement nz count
			return; 
		}					  		
		else{								// if same row and col not found, iterate to next node
		prev = currentnode;
		currentnode = currentnode->next;	
		}							
	}	
}






