#include <stdio.h>
#include <stdlib.h>

// This program takes calculates and prints the user inputted row of a
// Pascal's triangle. It first prompts a user input for the row index and
// will then iterate through two loops in order to determine and print 
// each coefficient for the row. 

int main()
{
  int row;
  int i, k;  
  unsigned long x;
  printf("Enter a row index: ");
  scanf("%d",&row);	// takes user input for row

  // Write your code here
 
 // The first loop goes through all coefficients and prints 1 when looking at the 
 // first coefficient value, otherwise the second loop executes which 
 // determines each coefficient and then prints for the inputted row
 
  for(k = 0; k <=row; k++) // loops through each coefficient
     {
	x = 1;
	if (k == 0)
		printf("1 "); // prints 1 at the beginning of each row 
	else 
	{for (i = 1; i <= k; i++)
	{
	  x = ((row+1-i)*x)/i; // calculate coefficient value
	
	}
	printf("%ld ", x); // print coefficient
	}
	
     }

  return 0;
}
