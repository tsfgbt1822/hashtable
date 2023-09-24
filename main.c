// You should not need to change main.c.  However, while
// developing your software, you may wish to uncomment various
// things that print out information for debugging purposes.  You
// can certainly add your own printing code as well to help you 
// debug things.
//
// Note also that the TAs may print out information when checking
// to see if your code actually works properly.

#include <stdio.h>
#include <string.h>
#include "hash.h"

// Types
typedef struct
{
	char szFirstName[NAMELEN];
	char szLastName[NAMELEN];
	int iAccountNumber;
} Customer;

// Fills a name with a single repeated character
// this is just to provide some simulated data
void FillName(char * name, char cur)
{
	for (int i=0;i<NAMELEN-1;i++)
	{
		name[i]=cur;
	}

	// NULL terminate
	name[NAMELEN-1]='\0';
}

// Fils a customer with some data
void FillCustomer(Customer * pCustomer)
{
	static int lastAN=0;
	static char cFNameStart='A';
	static char cLNameStart='A';

	FillName(pCustomer->szFirstName,cFNameStart);
	FillName(pCustomer->szLastName,cLNameStart);

	// Wrap through all upper-case fn and all upper and lower-case ln
	// Should give over 1,000 combinations, so that's enough
	cFNameStart++;
	if (cFNameStart>'Z')
	{
		cFNameStart='A';
		cLNameStart++;
	}
	if (cLNameStart>'Z' && cLNameStart<'a')
	{
		cLNameStart='a';
	}
	if (cLNameStart>'z')
	{
		cLNameStart='A';
	}

	pCustomer->iAccountNumber = lastAN++;
}

// Fill all of our customers with some simulated data
void FillCustomers(Customer customers[], int count)
{
	for (int i=0;i<count;i++)
	{
		FillCustomer(&customers[i]);
	}
}

void PrintCustomers(Customer customers[], int count)
{
	for (int i=0;i<count;i++)
	{
		printf(	"%s %s (%d)\n",
				customers[i].szFirstName,
				customers[i].szLastName,
				customers[i].iAccountNumber);
	}
}

// Derive a key from a Customer's first letter of first name
// and first letter of last name
int Getkey(Customer customer)
{
	int key = customer.szLastName[0];
	key*=256;
	key+=customer.szFirstName[0];
	return key;
}

void PrintCustomerKeys(Customer customers[], int count)
{
	for (int i=0;i<count;i++)
	{
		printf("%d ",Getkey(customers[i]));
	}
	printf("\n");
}

int main(void)
{
	// Create a bunch of customers
	Customer customers[CUSTCOUNT];

	FillCustomers(customers,CUSTCOUNT);
	//PrintCustomers(customers,CUSTCOUNT);
	//PrintCustomerKeys(customers,CUSTCOUNT);

	// Now, imagine we want to store customers in a much smaller space
	Customer hashtable[TABLESIZE];
	memset(hashtable,0,sizeof(Customer)*TABLESIZE);

	// First, give up on collisions
	// Fill the table, using the Div Method
	printf("\n\nFail Collisions - Division Method:\n");
	for (int i=0;i<CUSTCOUNT;i++)
	{
		int key = Getkey(customers[i]);
        printf("\nmain key:%d", key);    //check what the key is
		if (-1==InsertFailCollision(hashtable,sizeof(Customer),TABLESIZE,
									key,&customers[i],DivMethod))
		{
			//printf("*** Insert failed ***\n");
		}
	}

	// See if we can find the customers
	int countFound=0;
	int countNotFound=0;
	for (int i=0;i<CUSTCOUNT;i++)
	{
		int key = Getkey(customers[i]);
		Customer * custFound = SearchNoCollision(hashtable,key,sizeof(Customer),DivMethod);
		if (custFound!=NULL && Getkey(*custFound)==key)
		{
			countFound++;
			//printf("Found customer with key=%d\n",key);
		}
		else
		{
			countNotFound++;
			//printf("*** Failed to find customer with key=%d\n",key);
		}
	}
	printf("******* Found %d, Not Found %d *******\n",countFound,countNotFound);

	//PrintCustomers(hashtable,CUSTCOUNT);

	// Reset the table
	memset(hashtable,0,sizeof(Customer)*TABLESIZE);
	
	// Fill the table, using the Multiplication Method
	printf("\n\nFail Collisions - Multiplication Method:\n");
	for (int i=0;i<CUSTCOUNT;i++)
	{
		int key = Getkey(customers[i]);
		if (-1==InsertFailCollision(hashtable,sizeof(Customer),TABLESIZE,
									key,&customers[i],MultMethod))
		{
			//printf("*** Insert failed ***\n");
		}
	}

	// See if we can find the customers
	countFound=0;
	countNotFound=0;
	for (int i=0;i<CUSTCOUNT;i++)
	{
		int key = Getkey(customers[i]);
		Customer * custFound = SearchNoCollision(hashtable,key,sizeof(Customer),MultMethod);
		if (custFound!=NULL && Getkey(*custFound)==key)
		{
			countFound++;
			//printf("Found customer with key=%d\n",key);
		}
		else
		{
			countNotFound++;
			//printf("*** Failed to find customer with key=%d\n",key);
		}
	}
	printf("******* Found %d, Not Found %d *******\n",countFound,countNotFound);

	//PrintCustomers(hashtable,CUSTCOUNT);


	// New table
	void * newtable = AllocateChainTable(TABLESIZE);

	// Fill the table
	printf("\n\nChain on Collisions - Multiplication Method:\n");
	for (int i=0;i<CUSTCOUNT;i++)
	{
		int key = Getkey(customers[i]);
		if (-1==InsertChain(newtable,sizeof(Customer),TABLESIZE,
									key,&customers[i],MultMethod))
		{
			//printf("*** Insert failed ***\n");
		}
	}

	// See if we can find the customers
	countFound=0;
	countNotFound=0;
	for (int i=0;i<CUSTCOUNT;i++)
	{
		int key = Getkey(customers[i]);
		Customer * custFound = SearchChain(newtable,key,sizeof(Customer),MultMethod);
		if (custFound!=NULL && Getkey(*custFound)==key)
		{
			countFound++;
			//printf("Found customer with key=%d\n",key);
		}
		else
		{
			countNotFound++;
			//printf("*** Failed to find customer with key=%d\n",key);
		}
	}
	printf("******* Found %d, Not Found %d *******\n",countFound,countNotFound);

	//PrintCustomers(hashtable,CUSTCOUNT);
}
