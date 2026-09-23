#include <stdlib.h>
#include <stdio.h>
#include <argp.h>
#include <string.h>


// Linked list sturct element:
typedef struct row {
    char *ptrRowData;
    struct row *ptrNextRow;
} ROW;

// Function Declarations
ROW* readRows(ROW* pFirstListElement, FILE*);
void printText(ROW* pFirstListElement);
void clearLinkedList(ROW* pFirstListElement);

    int main(int argc, char *argv[]) {

        printf("! Welcome to a Very Useful Text Reversing Program !\n");

        // Data stream types for file input and output:
        FILE *ptrInputFileHandle;
        FILE *ptrOutputFileHandle;

        // char* pTextInput = NULL;
        char* pInputFilename = NULL;
        char* pOutputFilename = NULL;

        // Linked list pointers:
        ROW *pFirstListElement = NULL;

        int args = argc -1;
    
        // Check if too many arguments are given:
        if(args>2){
            fprintf(stderr, "usage: reverse <input> <output>\n");
            exit(1);
        }

        // Main Logic Structure:
        switch (args){
        case 0:

            // Read User Input
            // Take in user input from stdin:
            printf("Type in your input: \n");
            pFirstListElement = readRows(pFirstListElement, stdin);
            // output = reverseText(input)
            printf("Reversed Contents: \n");
            printText(pFirstListElement);
            break;

        case 1:
            
            // Take input file from first argument
            pInputFilename = argv[1];
            printf("Reading a file '%s'\n",pInputFilename);

            // Source for file handling: https://www.geeksforgeeks.org/c/basics-file-handling-c/            
            ptrInputFileHandle = fopen(pInputFilename, "r");
            if (ptrInputFileHandle == NULL) {
                fprintf(stderr, "error: cannot open file '%s'\n", pInputFilename);
                exit(1);
            }
            pFirstListElement = readRows(pFirstListElement, ptrInputFileHandle);
            printf("Reading complete!\n");
            
            printf("Reversed File Contents: \n");
            printText(pFirstListElement);
            fclose(ptrInputFileHandle);
            break;

        case 2: 

            pInputFilename = argv[1];
            pOutputFilename = argv[2];

            // Source: https://www.geeksforgeeks.org/c/strcmp-in-c/
            if(!strcmp(pInputFilename, pOutputFilename)){
                fprintf(stderr, "Input and output file must differ\n");
                exit(1);
            }

            // Source for file handling: https://www.geeksforgeeks.org/c/basics-file-handling-c/            
            ptrInputFileHandle = fopen(pInputFilename, "r");
            if (ptrInputFileHandle == NULL) {
                fprintf(stderr, "error: cannot open file '%s'\n", pInputFilename);
                exit(1);
            }

            printf("Reading a file '%s'\n",pInputFilename);
            pFirstListElement = readRows(pFirstListElement, ptrInputFileHandle);
            
            fclose(ptrInputFileHandle);
            printf("Reading complete!\n");
            
            ptrOutputFileHandle = fopen(pOutputFilename, "w");
            if (ptrInputFileHandle == NULL) {
                fprintf(stderr, "error: cannot open file '%s'\n", pInputFilename);
                exit(1);
            }

            ROW* pNextListElement = pFirstListElement;

            printf("Writing to a file '%s'\n",pOutputFilename);
            while(pNextListElement != NULL){
                fputs(pNextListElement->ptrRowData, ptrOutputFileHandle);
                pNextListElement = pNextListElement->ptrNextRow;
            }

            printf("Writing complete!\n");

            // printf("Reversed File Contents: \n");
            // printText(pFirstListElement);

            fclose(ptrOutputFileHandle);

            break;

        default:
            break;
        }

        // Free the LinkedList
        clearLinkedList(pFirstListElement);

        // printf("Kiitos ohjelman käytöstä!\n");
        return(0);
    }

// Sources for Reading the Rows: 
// this blogpost: https://c-for-dummies.com/blog/?p=1112
// This forum post: https://stackoverflow.com/questions/58667971/c-store-strings-created-by-getline-in-a-linked-list
// C-programming manual by Uolevi Nikula for implementing the linked list: https://urn.fi/URN:ISBN:978-952-335-685-6 
// and man getline

ROW* readRows(ROW *pFirstListElement, FILE *type){
    
    ROW *pNewListElement, *pSecondListElement;

    char *rowTextBuffer = NULL;
    size_t bufferSize = 0;
    size_t readCharacters;

    // Each new loop calls the getline()-function which automatically dynamically allocates data for the row and provides a pointer to the data.
    // This pointer is stored to the linked list as a new element.
    while((readCharacters = getline(&rowTextBuffer, &bufferSize, type)) != (size_t)-1){
        
        // Source: Uolevi Nikula (link above), I implemented the Uolevi's Example but in an inverted manner where I reverse the list element order for reversed plottign etc.
        // Allocating memory for New Linked List element type of ROW struct:
        if ((pNewListElement = (ROW*)malloc(sizeof(ROW))) == NULL ){
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        // Putting the read Row Data to the new Element data pointer:
        pNewListElement -> ptrRowData = rowTextBuffer;
        
        // Putting the New Row Element to the beginning of the Linked List:

        /* In case there is No Elements yet in the List */
        if(pFirstListElement == NULL){
            pFirstListElement = pNewListElement;
            // pLastListElement = pNewListElement; // Not needed!
        
        /* Put the New Element to First position of the Linked List */
        /* Linked List Life cycle */
        /* 1: A (F/L)               */
        /* 2: A (F), B(L)           */
        /* 3: A (F), B, C(L)        */
        /* 3: A (F), B, C, D(L)     */
        /* List is easily printed from F -> L */
        /* To automatically order list "backwards"  we have to inject the new element to the first position always */
        } else {
            // Store the current first element to second position (temporary pointer):
            pSecondListElement = pFirstListElement;

            // Put the new row to first position:
            pFirstListElement = pNewListElement;

            // Put the second element to the new "next-in-line" position
            pFirstListElement -> ptrNextRow = pSecondListElement;
        }
        
        rowTextBuffer = NULL;
        bufferSize = 0;
                
    }

    // Free the Row Buffer after usage!
    /** Google Gemini AI was used to debug the code and explained to add this additional free()-command here **/
    // Also this source was useful: https://stackoverflow.com/questions/75562027/how-to-avoid-memory-leaks-when-using-getline-to-read-from-stdin-in-c
    // The stackoverflow-source showed that the getline-buffer needs to be freed.
    // getline()-manual page doesn't regard freeing the memory...
    free(rowTextBuffer);
    return pFirstListElement;
}

// Print out the given text!
void printText(ROW* pFirstListElement){

    ROW *ptrNextElement = pFirstListElement;

    // Go through the printed text array and print one row by one:
    // Use the known word count!
    while(ptrNextElement != NULL){
        
        printf("%s", ptrNextElement->ptrRowData);
        ptrNextElement = ptrNextElement->ptrNextRow;
    }
    
    return;
}

void clearLinkedList(ROW* pFirstElement){

    // This structure for freeing linked list memory is copied from Uolevi Nikula's example:
    ROW* ptrCurrent = pFirstElement;
    ROW* ptrNext = pFirstElement;

    /** Google Gemini AI was used to help to understand how to properly free the linked list. **/
    // Initially I tried to only free the list element, but this left begind the actual data allocated with the getline()-function.
    // This part was implemented by me, but the cause for memory leak was explained by AI (pointer to the actual data inside the list element is used to free the actual data): 
    while (ptrCurrent != NULL) {
        ptrNext = ptrCurrent->ptrNextRow;
        // We have to free the memory containing the actual data getline() reserved.
        free(ptrCurrent->ptrRowData);
        // As well as the ROW-struct element for that data.
        free(ptrCurrent);
        ptrCurrent = ptrNext;
    }

    // printf("Memory Cleared.\n");
}