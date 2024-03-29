/* CS261- Assignment 1 - Q.1*/
/* Name: Eli Goodwin
 * Date: 2017.01.10
 * Solution description: Simple program generates a struct array of students with randomized scores and IDs which are then printed to screen.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

/* allocates a dynmaic array of 10 students  */
struct student* allocate(){
    int numberOfStudents = 10; //number of students
    
    /*Allocate memory for ten students*/
    struct student *myStudents = malloc(numberOfStudents * sizeof(struct student));
    
    /*return the pointer*/
    
    return myStudents;
}

void generate(struct student* students){
    int numberOfStudents = 10; //number of students
    int randomID = 0; //ID generated by random
    int randomScore = 0; //Score generated by random
    int foundScore  = 0; //flag for score
    int foundID = 0;    //flag for id
    int uniqueID = 0; //flag for unique id
    int uniqueScore = 0; //flag for if a unique score is created or not
    int count = 0; //counter for the while loops
    //initialize the random stuff
    srand(time(NULL));
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    for(int i = 0; i < numberOfStudents; ++i){
        
        //keep generating IDs until one is made that is not used
        while(uniqueID == 0){
            randomID = rand() % numberOfStudents + 1; //create a student id ranging from 1 - 10
            //test if the randomID is in the struct array
            while(count < numberOfStudents && foundID == 0){
                if(randomID == students[count].id){
                    foundID = 1;
                }
                ++count;
            }
            
            //was the id unique? if yes, store it
            if(foundID == 0){
                uniqueID = 1;
                students[i].id = randomID;
            }
            count = 0; //reset count
            foundID = 0; //reset found flag
        }
        uniqueID = 0;
        
        //keep generating scores until one is made that is not used
        while(uniqueScore == 0){
            randomScore = rand() % 101; //score range is 0 - 100
            
            //test if the randomScore is in the struct array
            while(count < numberOfStudents && foundScore == 0){
                if(randomScore == students[count].score){
                    foundScore = 1;
                }
                ++count;
            }
            //was the score unique? if yes store it
            if(foundScore == 0){
                uniqueScore = 1;
                students[i].score = randomScore;
            }
            count = 0; //reset count
            foundScore = 0; //reset found flag
        }
        
        uniqueScore = 0;
        
    }
}

/*Prints the contents of the student struct array*/
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    
    int numberOfStudents = 10; //number of students in the struct array
    printf("\nPrinting student IDs and scores:\n");
    //print contents of struct array
    for(int i = 0; i < numberOfStudents; ++i){
        printf("\n%i %i", students[i].id, students[i].score);
        
    }
    printf("\n");
}


/*Prints the low, high, and average scores of the students*/
void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
    
    int numberOfStudents = 10; //number of students in the struct array
    int maxScore = 0; //max score contained in the array
    int minScore = 0; //min score contained in the array
    int totalScore = 0; //total score used for calculating average
    float averageScore = 0; //average score of the students
    
    //set max and min scores to the first student score
    maxScore = students[0].score;
    minScore = students[0].score;
    
    //find min and max values
    for(int i = 0; i < numberOfStudents; ++i){
        totalScore += students[i].score;
        
        if(students[i].score > maxScore){
            maxScore = students[i].score;
        }
        if(students[i].score < minScore){
            minScore = students[i].score;
        }
    }
    
    //calculate average score
    averageScore = (float)totalScore / (float)numberOfStudents; //cast ints to float and get average
    
    //print score stuff
    printf("\nMin score: %i, Max Score: %i, Average Score: %f\n", minScore, maxScore, averageScore);
    
}

/*Destroy the struct array*/
void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    if(stud != NULL){
        free(stud);
    }
    else{
        printf("\nNothing to free\n");
    }
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate(stud);
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);
    
    /*call deallocate*/
    deallocate(stud);
    return 0;
}
