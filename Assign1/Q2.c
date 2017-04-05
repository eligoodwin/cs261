/* CS261- Assignment 1 - Q.2*/
/* Name: Eli Goodwin
 * Date: 2016.01.19
 * Solution description: Simple program shows what happens when values are passed by reference/pointer and manipulated along with function scope.
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = 2 * (*a);
    
    /*Set b to half its original value*/
    *b = (*b) / 2;
    
    /*Assign a+b to c*/
    c = (*a) + (*b);
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    
    int returnOfFoo = 0; //stores the return of foo for comparison
    
    /*Print the values of x, y and z*/
    printf("\nx: %i, y: %i, z: %i\n", x, y, z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    returnOfFoo = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
    printf("\nValue returned from foo: %i\n", returnOfFoo);
    
    /*Print the values of x, y and z again*/
    printf("\nx: %i, y: %i, z: %i\n", x, y, z);
    
    /*Is the return value different than the value of z?  Why?*/
    printf("The value of z is not different because a copy of z was passed to foo, not the memory address of z. The other values, x and y, had their memory direclty accessed and modified hence why their values differed.\n");
    
    return 0;
}
    
    
