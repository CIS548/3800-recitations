#include <stdio.h>
#include <stdlib.h>



int main(int argc, char ** argv)
{
	int already_set[5] = {7, 20, 15, 46, 96};
	printf("The value of already_set is %p\n", already_set);

	printf("The dereferenced value of already_set is %d\n", *already_set);
	printf("The value of already_set[0] is %d\n", already_set[0]);

	int * third_val = already_set + 2;
	printf("The memory location of the 3rd value of already_set is %p\n", third_val);
	printf("To 3rd value of already_set is %d\n", *third_val);

	char chars[5] = {'a', 'b', 'c'};
	printf("chars size is %lu\n", sizeof(chars));
}

