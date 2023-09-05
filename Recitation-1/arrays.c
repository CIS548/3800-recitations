/*
	Example Code on how arrays work in C
*/

#include <stdio.h>
#include <stdlib.h>


void preset_array()
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

void malloc_array(int size)
{
	int * dynamic_array = malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++)
	{
		dynamic_array[i] = i * i;
	}

	for(int i = 0; i < size; i++)
	{
		printf("dynamic_array[%d] is %d\n", i, dynamic_array[i]);
	}


}

int main(int argc, char ** argv)
{
	preset_array();
	malloc_array(atoi(argv[1]));
}

