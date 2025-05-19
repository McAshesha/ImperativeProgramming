#pragma once
#ifdef HASHMAP_EXPORTS
    #define HASHMAP "default"
#else
    #define HASHMAP "hidden"
#endif
#include<stdint.h>

typedef const void* cpvoid;


typedef int (*EqualFunc)(cpvoid a, cpvoid b);

typedef uint32_t (*HashFunc) (cpvoid key);

typedef struct Node {
    cpvoid key;
    cpvoid value;
    struct Node* next;
} Node;

typedef struct HashMap {
    EqualFunc equal_func;
    HashFunc hash_func;
    int size;
    Node** table;
}HashMap;

HashMap HM_Init(EqualFunc ef, HashFunc hf, int size);

void HM_Destroy(HashMap* self);

cpvoid HM_Get(const HashMap* self, cpvoid key);

void HM_Set(HashMap* self, cpvoid key, cpvoid value);
