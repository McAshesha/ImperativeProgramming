#include <stdlib.h>
#include <stdio.h>

typedef struct State {
    char* regs[256];
} State;

int countDigits(int number) {
    int count = 0;

    while (number != 0) {
        number = number / 10;
        count++;
    }
    return count;
}

void __attribute__((visibility("default"))) concat_2(State* state, char* idx0, char* idx1) {
    char* A = state->regs[atoi(idx0)];
    char* B = state->regs[atoi(idx1)];
    char* result = (char*)malloc(strlen(A) + strlen(B) + 1);
    strcpy(result, A);
    strcat(result, B);
    state->regs[atoi(idx0)] = result;
    free(A);
}

void __attribute__((visibility("default"))) tokenize_1(State* state, char* arg) {
    int tokens = 0;
    char* token = strtok(arg, "_");

    while (token != NULL && (*token) != '\n' && *(token-1)!='\r') {
        tokens++;
        state->regs[tokens] = _strdup(token);
        token = strtok(NULL, "_");
    }

    char* s = (char*)malloc(sizeof(char) * (countDigits(tokens) + 1));
    sprintf(s, "%d", tokens);
    state->regs[0] = s;
}

