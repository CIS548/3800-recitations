/************************************************************************************
 * Author: Seungmin Han
 * Date: 09/04/2023
 * 
 * This document outlines some best C practices and styles while programming for 
 * CIS 3800/5480 projects. This is by no means the bible of C style guide, but some
 * practices that will allow you and your teammates to produce clean and readable code
 * that will help with collaboration and organizing big projects.
 ************************************************************************************/

/**
 * .h files or header files declare any variables, functions, or anything that your
 * source code (.c files) can use.
 * 
 * The ifndef guard can be placed on top of all header files to avoid any multiple
 * references to header files. This way, multiple source code can include this header
 * file, but it will be only included once.
*/
#ifndef c_style
#define c_style

// Global Variables: you may use them, but try to avoid these as much as possible
int a, b;
char c;
char* str;

// custom types
typedef int my_int;
my_int mi = 1;

// enums
enum my_enum {
    ONE,
    TWO,
    THREE
}; // make sure to end with a semicolon

struct my_struct {
    my_int x;
    int y;
    char* string;
}; // do not forget this semicolon too

// declare functions to use
int my_function();

int function1(char*);
int copy_string(char*, char*);
int tokenize_string(char**, char*);
int copy_tokens(char**, char**);

#endif