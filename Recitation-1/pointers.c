#include <stdio.h>
#include <stdlib.h>



/* Does not return a value
 * just edits the value the pointer 
 * points to 
 * */
void add_b_to_a(int* a, int * b)
{
	*a = *a + *b;
}

void add_example()
{
	int a = 5;
	printf("The memory location of a is: %p\n", &a);
	int b = 6;

	int *ptr_a = &a;
	printf("ptr_a value is: %p\nptr_a dereferenced value is: %d\n", ptr_a, *ptr_a);
	int *ptr_b = &b;


	add_b_to_a(ptr_a, ptr_b);
	printf("a is %d\n", a);
}



void add_another_way(int* output, int num1, int num2)
{
	//int * added = malloc(sizeof(int));
	int added = num1 + num2;
	output = added;
}


void ret_bad_example()
{
	int* output;
	add_another_way(output, 100, 25);
	printf("output is: %d", *output);
}




int main(int argc, char ** argv)
{

	add_example();
	ret_bad_example();
	double_array();
	
}
