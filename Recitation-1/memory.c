#include <stdio.h>
#include <stdlib.h>

char* allocate_string() {
    char* str = (char*) malloc(20 * sizeof(char)); // MAKE SURE TO FREE THIS
    return str;
}

char* stack_string() {
    char str[6] = "hello";
    return str;
}

int main() {
    // Anything allocated on the stack is of local scope
    // string3 points to a memory that cannot be accessed
    // Also note the compiler warning
    // memory.c:11:12: warning: address of stack memory associated with local variable 'str' returned [-Wreturn-stack-address]
    char* string3 = stack_string();
    printf("string3: %s\n", string3);

    /********* malloc example 1 *********************************************************************************/
    // note malloc(3) only allocates memory, and does not initialize the memory allocated.
    int* int_array = (int*) malloc(5 * sizeof(int));
    // check that this statement shows a memory error of : uninitialised value(s)
    printf("first element of int_array: %d\n", int_array[0]);
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
    char* string2 = malloc(3);
    printf("%c", string2[0]);

    /********* Thinking question 1. How would we allocate memory for an array of strings (char**)? **************/
    // char** str_arr = malloc(20 * ...)

    /********* Thinking question 1. How would we free such memory? **********************************************/
    // free(str_arr) ?

    /********* Thinking question 3. Do we need to free memory allocated from another function? ******************/
    char* from_another = allocate_string();
    // check with valgrind!
}