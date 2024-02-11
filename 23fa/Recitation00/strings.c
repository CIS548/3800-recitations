/* 
 * Example code on how strings work in C
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Basic string behavior
void basic_string_behavior()
{
	char *str = malloc(sizeof(char) * 20);
	// Copying over 13 bytes to make sure it is null terminated
	memcpy(str, "Hello World!", 13);
	// Printing the value of each character in the character array
	for(int i = 0; i < strlen(str); i++)
	{
		printf("str[%d] is %c\n", i, str[i]);
	}
	// Printing the 12th character, the null terminator
	printf("str[12] is %d\n", str[12]);
	free(str);


}

void weird_string_behavior()
{
	// easy way to declare predefined string on the stack
	// Points to string literal, which is a strange thing in c
	char preset_str[] = "I am preset string";

	printf("Memory location preset_str points to is %p\n", preset_str);
	
	char stack_str[10];
	printf("Memory location stack_str points to is %p\n", stack_str);

	//stack_str = "I am stack string"; // Try running!
	memcpy(stack_str, preset_str, 10);
	// Prints stack_str as a string
	printf("stack_str is: %s\n", stack_str);
}


void null_termination()
{

	char * to_the_max = malloc(sizeof(char) * 11);
	memcpy(to_the_max, "hello world", 11);
	// Really bad practice 
	memcpy(to_the_max + 11, "Bwahahahaha", 11);
	printf("to the max is: %s\n", to_the_max);
	to_the_max[6] = '\0';
	printf("to the max is now: %s\n", to_the_max);
	free(to_the_max);

}




int main(int argc, char** argv)
{
	basic_string_behavior();
	weird_string_behavior();
	null_termination();



}
