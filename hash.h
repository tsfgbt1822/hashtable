#ifndef _hash_h
#define _hash_h
// Symbolic Constants
#define NAMELEN	7
#define CUSTCOUNT 1024
#define TABLESIZE 100

// Prototypes
int InsertFailCollision(	void * hashtable, int elementSize, int elementCountMax,
                            int key, void * element, int (*HashFunc)(int key));
void * SearchNoCollision(void * hashtable, int key, int elementSize, int (*HashFunc)(int key));
int DivMethod(int key);
int MultMethod(int key);

void * AllocateChainTable(int elementCountMax);
void FreeChainTable(void * hashtable);
int InsertChain(	void * hashtable, int elementSize, int elementCountMax,
                            int key, void * element, int (*HashFunc)(int key));
void * SearchChain(void * hashtable, int key, int elementSize, int (*HashFunc)(int key));

#endif
