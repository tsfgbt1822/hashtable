#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

typedef struct LinkedList               //define linkedList
{
    void *info;
    struct LinkedList *next;
}LinkedList;

LinkedList *createList();               //decleration of new function

// These are stubs.  That is, you need to implement these functions.


//given a key, try to insert into hashtable  and if there is collision, return -1, otherwise return 0
int InsertFailCollision(	void * hashtable, int elementSize, int elementCountMax,
                            int key, void * element, int (*HashFunc)(int key))
{
     hashtable=hashtable+key;
     if(hashtable!=0)   //checks to see if there is a value at that key already
     {
        hashtable=element;  //if there isnt, assign element to hashtable and return 0    
        return 0;
     }

     return -1;             //else, return -1      
}


//Try to find the customer with given key, return the customer, or return NULL
void * SearchNoCollision(void * hashtable, int key, int elementSize, int (*HashFunc)(int key))
{
    hashtable=hashtable+key; //make hashtable point to the given index
    if(hashtable!=0)         //check if there is a value at that point
        return hashtable;    //return the value at the index

    return NULL;            //otherwise, return NULL
}


//use division method to return a new key
int DivMethod(int key)
{
    key=key%13;     //key mod 13 
	return key;
}


//use multiplication method to assign a new key
int MultMethod(int key)
{
    double A=(sqrt(5)-1)/2;     //A=Knuth's number
    key=(8*key*A)-(key*A);      //use multiplication equation given in lecture to get new key
    return key;
}


//create a new hash table that will use chain method to prevent collisions 
void * AllocateChainTable(int elementCountMax)
{
    void * hashtable[elementCountMax];      //create new hashtable
    for(int i=0; i<elementCountMax; i++)    //for each index in array
    {
        LinkedList *list=createList();      //create a new linked list
        hashtable[i]=list;                  //assign the linked list to the array index
    }
    return *hashtable;                      //return the hastable
}


//frees the chain table
void FreeChainTable(void * hashtable)
{
    LinkedList * temp;                      //temporary linked list for placeholding
    temp=hashtable;                         //assign this spot on hashtable to temp
    while(temp->next!=NULL)                 //while temp has been filled
    {
        hashtable=temp->next;               //assign the next node to hashtable
        free(temp);                         //free temp
        temp=hashtable;                     //assign hashtable to temp
    }
}


//fill the table using chaining
int InsertChain(	void * hashtable, int elementSize, int elementCountMax, int key, void * element, int (*HashFunc)(int key))
{
    key=MultMethod(key);            //use multiplication method to create a new key
    LinkedList * temp;              //create temp variable
    hashtable=hashtable+key;        //find indexed spot of hashtable
    temp=hashtable;                 //assign temp to the given hashtable spot

    while(temp->info!=NULL)         //while temp has been assigned a value already
    {
        if(temp->next==NULL)        //check if temp->next exists
        {
            LinkedList *list =createList(); //if temp->next doesnt exist, create it
            temp->next=list;
        }
        temp=temp->next;            //assign temp to the next node in the linkedlist and retry until we find an empty one
    }

    temp->info=element;             //assign element to this spot
    return 0;                       //return 0 to signify element placed
}


//search the table that used chaining
void * SearchChain(void * hashtable, int key, int elementSize, int (*HashFunc)(int key))
{
    key=MultMethod(key);            //use multiplication to find new key
    LinkedList *temp;               //create temporary LinkedList 
    hashtable=hashtable+key;        //index to correct spot in hashtable
    temp=hashtable;                 //assign temp to spot in hashtable

    while(sizeof(temp->info)!=elementSize)      //while the size of what is stored in info does not match the desired element size, go to next node
    {
        temp=temp->next;
    }
    
    return temp->info;              //return info            
}

LinkedList * createList()           //create and initialize linked list
{
    LinkedList * list = (LinkedList*)malloc(sizeof(LinkedList));
    list->next=NULL;
    list->info=NULL;

    return list;
}
