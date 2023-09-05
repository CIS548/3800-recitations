#include <stdio.h>
#include <stdlib.h>

char* allocate_string() {
    char* str = (char*) malloc(20 * sizeof(char)); // MAKE SURE TO FREE THIS
    return str;
}

int main() {
    /********* malloc example 1 *********************************************************************************/
    int* int_array = (int*) malloc(5 * sizeof(int));
    for (int i = 0; i < 5; ++i) {
        int_array[i] = i;
    }
    for (int i = 0; i < 5; ++i) {
        printf("%d, ", int_array[i]);
    }
    printf("\n");

    /********* malloc example 2 with strings ********************************************************************/
    char* string = (char*) malloc(6 * sizeof(char));
    string = "hello";
    printf("%s\n", string);
    //uncomment the line below to free the string and not have any memory leaks
    // free(string);

    /********* SEGMENTATION FAULT will occur if we access memory that we never initialized or allocated *********/
    char* string2;
    printf("%c", string2[0]);

    /********* Thinking question 1. How would we allocate memory for an array of strings (char**)? **************/
    // char** str_arr = malloc(20 * ...)

    /********* Thinking question 1. How would we free such memory? **********************************************/
    // free(str_arr) ?

    /********* Thinking question 3. Do we need to free memory allocated from another function? ******************/
    char* from_another = allocate_string();
    // check with valgrind!
}