#include <stdio.h>
#include <stdlib.h>

struct BankAccount {
	int amount;
	char* name;
};


typedef struct BankInformation {
	struct BankAccount* accounts;
	char* name;
} BankInformation;