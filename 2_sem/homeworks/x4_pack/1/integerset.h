#ifndef INTEGERSET_H
#define INTEGERSET_H

typedef struct IntegerSet IntegerSet;
IntegerSet* CreateSet(int* numbers, int size);
int IsInSet(IntegerSet* set, int number);

#endif
