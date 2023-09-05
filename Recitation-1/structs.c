#include "structs.h"

int main(int argc, char** argv)
{
	struct BankAccount acct_1;
	acct_1.amount = 10;
	acct_1.name = "Nate";

	printf("acct_1 name is %s\n", acct_1.name);
}

