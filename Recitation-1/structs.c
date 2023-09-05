/* 
Example code on how structs work in C and can be used
*/

#include "structs.h"


//In this case, the struct account is being created on the stack
void stack_account()
{
	struct BankAccount acct_1;
	acct_1.amount = 10;
	acct_1.name = "Nate";

	printf("acct_1 name is %s\n", acct_1.name);

}

// Creating an account on the heap and dereferencing with -> notation
void malloc_account()
{
	struct BankAccount* acct_2;
	acct_2 = malloc(sizeof(struct BankAccount));
	acct_2->amount = 11;
	acct_2->name = "Not Nate";
	printf("acct_2 namae is %s\n", acct_2->name);
	free(acct_2);

}

// Structs can also be pre assigned the same way arrays can
void stack_preset_account()
{

	//Have to make sure to give input values in order
	struct BankAccount acct_3 = {12, "Seungmin"};
	printf("acct_3 name is %s\n", acct_3.name);

}


// Here the BankInformation used typedef instead of just struct
// Making the struct keyword unneeded
void type_dec()
{
	BankInformation pnc;
	pnc.name = "Pittsburgh Branch";
	// An example of an array of structs
	struct BankAccount accounts[10];
	pnc.accounts = accounts;
	accounts[0].name = "Nate";
	accounts[0].amount= 0;

	// Since accounts is a pointer, can be dereferenced using -> notation
	printf("pnc's pittsburgh branchs first account amount is %d\n",
	pnc.accounts->amount);
}


int main(int argc, char** argv)
{
	stack_account();
	malloc_account();
	stack_preset_account();
	type_dec();

}

