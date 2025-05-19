#include "hashmap.h"
#include <stdlib.h>


HashMap __attribute__((visibility(HASHMAP))) HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap hm;

    hm.equal_func = ef;
    hm.hash_func = hf;
    hm.size = size;

    hm.table = (Node**)malloc(sizeof(Node*) * size);
    for (int i = 0; i < size; i++) {
        hm.table[i] = NULL;
    }
    return hm;
}

void __attribute__((visibility(HASHMAP))) HM_Destroy(HashMap* self) {
    if (self != NULL) {
        for (int i = 0; i < self->size; i++) {
            Node* current = self->table[i];
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(self->table);
    }
}

cpvoid __attribute__((visibility(HASHMAP))) HM_Get(const HashMap* self, cpvoid key) {
    uint32_t hash = self->hash_func(key) % self->size;
    Node* current = self->table[hash];

    while (current != NULL) {
        if (self->equal_func(current->key, key)) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void __attribute__((visibility(HASHMAP))) HM_Set(HashMap* self, cpvoid key, cpvoid value) {
    uint32_t hash = self->hash_func(key) % self->size;
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    Node* current = self->table[hash];
    while (current != NULL) {
        if (self->equal_func(current->key, key)) {
            current->value = value;
            free(new_node);
            return;
        }
        current = current->next;
    }
    new_node->next = self->table[hash];
    self->table[hash] = new_node;
}
