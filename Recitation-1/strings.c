#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	char preset_str[] = "I am preset string";
	printf("Memory location preset_str points to is %p\n", preset_str);
	char stack_str[10];
	printf("Memory location stack_str points to is %p\n", stack_str);
	//stack_str = "I am stack string"; // Does not work!
	memcpy(stack_str, preset_str, 10);
	printf("stack_str is %s\n", stack_str);


}
