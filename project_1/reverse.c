#include <stdlib.h>
#include <stdio.h>
#include <argp.h>
#include <string.h>

// Function Declarations
/* 
parseArgs();
readInput();
printText();

readFile();
writeFile();
*/

    int main(int argc, char *argv[]) {

        // printf("Hello World!\n");

        char input_text[256];
        char* pInputFilename;
        char* pOutputFilename;

        // If too many arguments are given:
        int args = argc -1;

        printf("Args: %d\n",args);

        if(args>2){
            fprintf(stderr, "usage: reverse <input> <output>\n");
            exit(1);
        }

        switch (args){
        case 0:

            // Read User Input
            // input = readInput()
            // output = reverseText(input)
            // printText(output)
            printf("Case 0\n");

            break;
        case 1:
            
            pInputFilename = argv[1];

            // parseArgs(&argv, input_filename)
            // input = readFile(input_filename)
            // output = reverseText(input)
            // printText(output)
            printf("Input file: %s\n", pInputFilename);
            break;

        case 2: 

            pInputFilename = argv[1];
            pOutputFilename = argv[2];

            // parseArgs(&argv, &input_filename, &output_filename)
            // input = readFile()
            // output = reverseText(input)
            // printText(output)
            // writeFile(output, output_filename)
            printf("Input file: %s\n", pInputFilename);
            printf("Output file: %s\n", pOutputFilename);
            break;
            
        default:
            break;
        }

        return(0);
    }
/* 
// Source for Argument Parsing: https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c
int parseArgs(int argv, char* input_filename, char* output_filename){

    // This function takes in the arguments from the command line.
    int args = 0;
    input_filename = "";
    output_filename = "";

    if(input_filename == output_filename){
        fprintf(stderr,"Input and output file must differ");
        exit(1);
    }

    // If too many arguments are given:
    if(args>2){
        fprintf(stderr, "usage: reverse <input> <output>");
        exit(1);
    }

    // Count args and decide what to do after in the switch case:
    return args;
}

// Case: No args!
// Source: https://www.w3schools.com/c/c_user_input.php
void readInput(void){

    // Take in user input from stdin:
    printf("Tye in your input: \n");
    fgets(input_text, sizeof(input_text), stdin);

    // Save input word count / length. Parse with " " space bars to count only words!
    return;
}

// Print out the given text!
void printText(char* text_array, int word_count){

    // Go through the printed text array and print one row by one:
    // Use the known word count!
    for i in word_count:
        fprint(rows(i))

    return;
}


/* 
// Case: Input File Argument Given!
void readFile(char* input_text){

    // Read a file one row by one to an array. Later expand array with malloc!
    // Increment word count by every row.
    try:
        fopen(filename);
        // Write the reversed text to an output file.
        while(length(row) != 0):
            row = stdin(FILE)

            input_text.append(row)
    except:
        fprintf(stderr, "error: cannot open file 'input.txt'")
        exit(1)
    closeFile(filename);
    return;
}

// Reverse the given input text!
void reverseText(char* input_text, int word_count){

    // Go through the input text array from the end to beginning. Use stored word count as reference. Output the inputted text in reversed order.

    return;
}

// Case: Input AND output files are given as argument!
void writeFile(char* reversed_text, int word_count, char* filename){

    openFile(filename);
    // Write the reversed text to an output file.
    for i in word_count:
        stdout(FILE, rows(i))

    closeFile(filename);

    return;
}

*/