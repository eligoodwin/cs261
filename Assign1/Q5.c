/* CS261- Assignment 1 - Q.5*/
/* Name: Eli Goodwin
 * Date: 1/18/2016
 * Solution description: A simple program that takes a simple single word string and switches the case of the characters.
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
    int count = 0; //count for the while loop
    
    //while word count is not a null terminating character swtich the cases of the characters contained in the string.
    while(word[count] != '\0'){
        
        if(word[count] >= 'A' && word[count] <= 'Z'){
            word[count] = toLowerCase(word[count]);
        }
        else{
            word[count] = toUpperCase(word[count]);
        }
        ++count;
    }
}

int main(){
    char wordIn[100];
    /*Read word from the keyboard using scanf*/
    printf("\nEnter a string for conversion (must be less than 100 characters): ");
    scanf("%[^\n]s", wordIn);
    
    /*Call sticky*/
    sticky(wordIn);
    
    /*Print the new word*/
    
    printf("Here is the new word: %s\n", wordIn);
    return 0;
}
