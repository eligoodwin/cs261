/* CS261- Assignment 1 - Q. 0*/
/* Name: Eli Goodwin
 * Date: 2017.01.10
 * Solution description: prints the values of and addresses of variables and pointers
 */
 
#include <stdio.h>
#include <stdlib.h>
/*Prints the value that is passed, its memory location, and the location of the paramter*/
void fooA(int* iptr){
    printf("\nNow printing from fooA.\n");
    
     /*Print the value pointed to by iptr*/
    printf("\nThe value of x: %i", *iptr);
    
    /*Print the address pointed to by iptr*/
    printf("\nThe address of x: %i", *&iptr);
    
    /*Print the address of iptr itself*/
    printf("\nThe address of iptr: %i\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
    int x  = 25;
    
    /*print the address of x*/
    printf("\nThe address of int x: %i", &x);
    
    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*print the value of x*/
    printf("\nNow out of fooA....");
    printf("\nThe value of x: %i\n", x);
    return 0;
}
