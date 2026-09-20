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
ROW* readRows(ROW* pFirstListElement, ROW* pLastListElement, FILE*);
void printText(ROW* pFirstListElement);
void clearLinkedList(ROW* pLastListElement);

    int main(int argc, char *argv[]) {

        printf("! Welcome to a Very Useful Text Reversing Program !\n");

        // Data stream types for file input and output:
        FILE *ptrInputFileHandle;
        FILE *ptrOutputFileHandle;

        char* pTextInput = NULL;
        char* pInputFilename = NULL;
        char* pOutputFilename = NULL;

        // Linked list pointers:
        ROW *pFirstListElement = NULL, *pLastListElement = NULL;

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
            pFirstListElement = readRows(pFirstListElement, pLastListElement, stdin);
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
            pFirstListElement = readRows(pFirstListElement, pLastListElement, ptrInputFileHandle);
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
            pFirstListElement = readRows(pFirstListElement, pLastListElement, ptrInputFileHandle);
            
            fclose(ptrInputFileHandle);
            printf("Reading complete!\n");
            
            ptrOutputFileHandle = fopen(pOutputFilename, "w");
            if (ptrOutputFileHandle == NULL){
                fprintf(stderr, "error: cannot open file 'input.txt'\n");
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
        clearLinkedList(pLastListElement);

        // printf("Kiitos ohjelman käytöstä!\n");
        return(0);
    }

// Sources for Reading the Rows: 
// this blogpost: https://c-for-dummies.com/blog/?p=1112
// This forum post: https://stackoverflow.com/questions/58667971/c-store-strings-created-by-getline-in-a-linked-list
// C-programming manual by Uolevi Nikula for implementing the linked list: https://urn.fi/URN:ISBN:978-952-335-685-6 
// and man getline

ROW* readRows(ROW *pFirstListElement, ROW *pLastListElement, FILE *type){

    // Take in user input from stdin:
    printf("Type in your input: \n");
    
    ROW *pNewListElement, *pSecondListElement;

    char *rowTextBuffer = NULL;
    size_t bufferSize = 0;
    size_t readCharacters;

    // Each new loop calls the getline()-function which automatically dynamically allocates data for the row and provides a pointer to the data.
    // This pointer is stored to the linked list as a new element.
    while((readCharacters = getline(&rowTextBuffer, &bufferSize, type)) != -1){
        
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
            pLastListElement = pNewListElement;
        
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

    // Linked list source: https://urn.fi/URN:ISBN:978-952-335-685-6 

    // Save input word count / length. Parse with " " space bars to count only words!
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


// SOURCE: Uolevi Nikula:
void clearLinkedList(ROW* pFirstElement){

    // This structure for freeing linked list memory is copied from Uolevi Nikula's example:
    ROW* ptrTemp = pFirstElement;
    while (ptrTemp != NULL) {
        pFirstElement = ptrTemp->ptrNextRow;
        free(ptrTemp);
        ptrTemp = pFirstElement;
    }  

    printf("Memory Cleared.\n");
}