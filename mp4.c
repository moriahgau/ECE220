// This program asks for two input numbers and calculates and prints the 
// semiprimes that are present between the two numbers. In order to calculate the 
// semiprimes, the program uses a function which checks whether numbers are prime
// and another function that checks for the prime factors and prints all
// semiprimes between the two inputs. If semiprimes are found, returns 1, otherwise returns 0.  

#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);		//Declare the functions
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   print_semiprimes(a, b); // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number) 
{
  int i; 
  for (i = 2; i <= number/2 ; i++)
    {
	if (number % i == 0)  // check if there is no remainder; 
	   return 0; 
	
    }
   return 1; 
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int n, k, x, z; 
  int y = 0; 
  
  for (n = a; n <= b; n++){
    for (k = 2; k <= n-1; k++){
	x = is_prime(n/k); // call is_prime to check that n/k is prime
	z = is_prime(k);   // call is_prime to check that k is prime
	if ((n % k == 0) && (x == 1)&& (z == 1)){ 
	  printf("%d ", n); // print semiprime 
	  y = 1; 
	  break;} // break out of loop if semiprime was printed
	}
  }
  if (y == 1)		// check if semiprimes were found
    return 1; 

  return 0; 
  
}



