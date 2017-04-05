/*
 * CS 261 Assignment 5
 * Name: Eli Goodwin
 * Date: 3.01.17
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
    
    char fileName[TASK_NAME_SIZE] = "\0"; //filename being used
    struct Task* tempTask = NULL;
    FILE* theFile = NULL;
    
    char taskName[TASK_NAME_SIZE] = "\0"; //task name
    int priority = 0; //priority
    int ch = 0; //used to clear the buffer, because c
    int lengthOfName = 0; //used to store the lenght of the task name

    switch(command){
        //loads the file into a heap, tests to make sure it works and then returns to the main menu
        case 'l' :
    
            printf("What is the name of th file you wish to load? : ");
            fgets(fileName, TASK_NAME_SIZE, stdin);
            lengthOfName = strlen(fileName); //get the length of the task name
            //get rid of newline because it's c
            if(lengthOfName > 0 && taskName[lengthOfName -1] == '\n'){
                taskName[lengthOfName -1] = '\0';
            }
            //make sure a priority in range is enetered
            theFile = fopen(fileName, "r"); //open the file
            
            //if the file was loaded successfully
            if(theFile != NULL){
                printf("Loading File...\n");
                listLoad(list, theFile); //get the contents of the file into memory for manipulation
                //did the file load?
                if(theFile == NULL){
                    printf("file failed to load, what did you do?...\n");
                }
                else{
                    printf("file loaded...\n");
                }
                fclose(theFile); //close out the file
            }
            //there is no file to load
            else{
                printf("Looks like there is no file to load by the name of \"%s\" :(\n"
                       "Try making a new list and saving it. Then you'll be able to open it at a later time :)\n", fileName);
            }

            break;
        
        //save the list
        case 's' :
            printf("What do you want to save the file as? : ");
            fgets(fileName, TASK_NAME_SIZE, stdin);
            lengthOfName = strlen(fileName); //get the length of the task name
            //get rid of newline because it's c
            if(lengthOfName > 0 && taskName[lengthOfName -1] == '\n'){
                taskName[lengthOfName -1] = '\0';
            }
            
            //save the file using the name
            printf("Saving file as: %s\n", fileName);
            theFile = fopen(fileName, "w"); //write the file to the working directory
            listSave(list, theFile); //save the contents of the list into the file in question
            fclose(theFile); //close the list
            
            break;
            
        //get a task name and then get the priority
        case 'a' :
            
            //get the task name from the user
            printf("What is the name of the task in question?: ");
            fgets(taskName, TASK_NAME_SIZE, stdin);
            lengthOfName = strlen(taskName); //get the length of the task name
            //get rid of newline because it's c
            if(lengthOfName > 0 && taskName[lengthOfName -1] == '\n'){
                taskName[lengthOfName -1] = '\0';
            }
            //make sure a priority in range is enetered
            do{
                printf("What is the priority of the task in question, range is 0 ... 100? ");
                scanf("%d", &priority);
            }while(!(priority >= 0 && priority <= 100));
            
            while ((ch = getchar()) != '\n' && ch != EOF); //clear out the buffer because it's c
            printf("task is being added... \n");
            //creating task
            tempTask = taskNew(priority, taskName);
            //adding task
            dyHeapAdd(list, tempTask, taskCompare);
            
            break;
        
        //get the first item in the list
        case 'g' :
            //test to make sure there is something to print
            if(list == NULL || dySize(list) == 0){
                printf("Either the to-do list is is empty or you haven't loaded a file to manipulate.\n");
            }
            else{
                printf("Getting the first task...\n");
                tempTask = dyHeapGetMin(list);
                printf("The first task you have is: %s\n", tempTask->name);
            }
            break;
        
        //remove the first item in the list
        case 'r' :
            //if the list is greater than 0 we can delete something
            if(dySize(list) >0){
                printf("removing the first task...\n");
                taskDelete(dyHeapGetMin(list)); //get the task
                dyHeapRemoveMin(list, taskCompare); //remove it from the heap and then heapify
            }
            else{
                printf("List is empty can't remove anything else :(\n");
            }

            break;
        
        //print all the stuff in the list
        case 'p' :
            //test to make sure the list is not empty
            if(dySize(list) >0){
                printf("Printing the list...\n");
                listPrint(list);
            }

            else
                printf("Nothing to print, list is empty :(\n");
            
            break;
        //get out of the program
        case 'e' :
          free(tempTask);
            break;
            
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
 /* free dynamically allocated List pointers in array to avoid memory leaks */
         /* Fix it */

    //destroy the list
    while(dySize(list) > 0){
        taskDelete(dyHeapGetMin(list));
        dyHeapRemoveMin(list, taskCompare);
    }

    //taskDelete(dyHeapGetMin(list));
    dyDelete(list);
    printf("Bye bye. See you never.");
    
    return 0;
}
