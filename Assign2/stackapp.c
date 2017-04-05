/*	stack.c: Stack application. */
/* CS261- Assignment 2*/
/* Name: Eli Goodwin
 * Date: 2017.01.24
 * Solution description: tests if a string containing brackets is balanced/closed or not
 */


#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
    param: 	s pointer to a string 	
    pre: s is not null		
*/
char nextChar(char* s)
{
    static int i = -1;	
    char c;
    ++i;	
    c = *(s+i);			
    if ( c == '\0' )
        return '\0';	
    else 
        return c;
}

/* Checks whether the (), {}, and [] are balanced or not
    param: 	s pointer to a string 	
    pre: s is not null	
    post:	
*/
int isBalanced(char* s)
{
    /* FIXME: You will write this function */
    
    if(s == NULL){
        return 0;
    }
    
    //init the array
    struct DynArr *stringArray = newDynArr(25); //acts as stack to store the brackets etc in
    char testChar; //stores the character that will be tested from argV
    
    //while the string != null terminator, test all the chars to see if they are balanced
    while((testChar = nextChar(s)) != '0'){
        //if it is one of the bracket characters stuff it into the stack
        switch(testChar){
                //if a leftHanded bracket shove into the stack
                case '{':
                case '(':
                case '[':
                    pushDynArr(stringArray, testChar);
                    break;
                
                //if a right handed bracket test against whatever is in the top of the stack
                //if left and right are a closing pair, pop the top item on the stack, otherwise return false and end test
                case '}':
                if(topDynArr(stringArray) == '{'){
                    popDynArr(stringArray);
                    break;
                }
                return 0;
                
                case ')':
                if(topDynArr(stringArray) == '('){
                    popDynArr(stringArray);
                    break;
                }
                return 0;
            
                case ']':
                if(topDynArr(stringArray) == '['){
                    popDynArr(stringArray);
                    break;
                }
                return 0;
        }
    }
    //is there stuff left in the array?
    if(isEmptyDynArr(stringArray) == 0){
        return 0;
    }
    
    //deallocate array
    deleteDynArr(stringArray);
          
    return 1;
}

int main(int argc, char* argv[]){
    
    char* s=argv[1];	
    int res;
    
    
    
    
    printf("Assignment 2\n");
    res = isBalanced(s);

    if (res)
        printf("The string %s is balanced\n",s);
    else 
        printf("The string %s is not balanced\n",s);
    
    return 0;	
}

