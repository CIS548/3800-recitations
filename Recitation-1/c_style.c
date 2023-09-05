/************************************************************************************
 * Author: Seungmin Han
 * Date: 09/04/2023
 * 
 * This document outlines some best C practices and styles while programming for 
 * CIS 3800/5480 projects. This is by no means the bible of C style guide, but some
 * practices that will allow you and your teammates to produce clean and readable code
 * that will help with collaboration and organizing big projects.
 ************************************************************************************/

// make sure to include the corresponding header file
#include "c_style.h"

// some other useful includes for development
#include <stdio.h>              // for input/output, printf
#include <unistd.h>             // c types
#include <string.h>             // c string library
#include <sys/types.h>          // other special types
#include <stdlib.h>             // c standard library
#include <sys/wait.h>           // includes wait(2)

// Define used functions ABOVE other functions that call it
int my_function() {
    return 1;
}

int main() {
    /****************** Don't forget semicolons! ******************/

    // It is okay to use either
    int camelCase;
    int snake_case;
    // But choose to one convention and stick to it throughout
    // I would recommend snake_case because it is sometimes hard to 
    // distinguish numbers and letters with camelCase

    // use spaces to separate operators
    int i = 0;      // good
    i = i + 1;      // good
    i=i+ 1;         // bad

    // local variables of same type can be declared on the same line
    int x, y, z;
    char c1 = 'a', c2 = 'b';

    // use spaces to separate brackets and keywords
    if (i == 0) {
        // do something
    }
    for (i = 0; i < 10; ++i) {
        // repeat something 10 times
    }
    while (i-- > 5) {
        // do something 5 times
    }
    do
    {
        // something
    } while (i++ < 10); // don't forget semicolon

    // indent for EVERY opening bracket
    if (1) {
        // indent
        if (1) {
            // indent
            if (1) {
                // indent
                // try not to nest more than 3 keywords.
            }
        }
    }

    // switch satements: every case has a single indent, each break has one more
    switch (i) {
        case 0:
            do_a();
            break;
        case 1:
            do_b();
            break;
        default: // must have default
            break;
    }

    // do not use <stdbool.h> booleans. C interprets 0 as false and any other as true
    if (1) {
        // always execute
    }
    if (0) {
        // never execute
    }

    // return values of functions may be used to feed in statements
    if (my_function()) { // returns 1
        // do something
    }
    // exmample with fork
    pid_t pid;
    if ((pid = fork()) < 0) {
        // parent? child? error?
    } else if (pid == 0) {
        // parent? child? error?
    } else {
        // parent? child? error?
    }

    // conditional execution
    #ifdef EXECUTE
    // will execute if EXECUTE is defined
    #else
    // will execute otherwise
    #endif

    #ifndef EXECUTE
    // will execute if EXECUTE is NOT defined
    #else
    // will execute otherwise
    #endif
}

int copy_string(char* s1, char* s2) { return 1; }
int tokenize_string(char** arr1, char* s1) { return 1; }
int copy_tokens(char** arr1, char** arr2) { return 1; }

/**
 * Try to modularize your code as much as possible! Maybe even create a separate file
 * for all your functions! This will make your code more readable.
 * 
 * Below is a function that copies a string, tokenizes it, and copies the tokens to a string array
*/
int function1(char* s1) {
    char* s2;
    if (copy_string(s1, s2) < 0) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    char** tokens;
    if (tokenize_string(tokens, s2) < 0) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    char** tokens_copy;
    if (copy_tokens(tokens_copy, tokens) < 0) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    return 1;
}
