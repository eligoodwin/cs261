/* CS261- Assignment 1 - Q.3*/
/* Name: Eli Goodwin
 * Date: 1/19/2017
 * Solution description: an array of size 20 is dynamically allocated and then filled with random integers which are then sorted using a bubble sort. 
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
    /*Sort the given array number , of length n*/
    /*Sort is implemented using a bubble sort*/
    
    int temp = 0; //stores array value temporarily for swapping
    
    for(int i = 0; i < n - 1; ++i){
        
        for(int j = 0; j < n - i - 1; ++j){
            
            if(number[j] > number[j + 1]){
                temp = number[j];
                number[j] = number[j + 1];
                number[j + 1] = temp;
            }
        }
    }
    
    return;
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int* array = malloc(n * sizeof(int));
    
    /*Fill this array with random numbers, using rand().*/
    srand(time(NULL));
    
    for(int i = 0; i < n; ++i){
        array[i] = rand() % 50;
    }
    
    /*Print the contents of the array.*/
    printf("\nContents of the array: \n");
    for(int i = 0; i < n; ++i){
        printf("%i ", array[i]);
    }
    printf("\n");
    
    /*Pass this array along with n to the sort() function of part a.*/
    sort(array, n);
    
    /*Print the contents of the array.*/
    printf("\nContents of the sorted array: \n");
    for(int i = 0; i < n; ++i){
        printf("%i ", array[i]);
    }
    
    
    return 0;
}
