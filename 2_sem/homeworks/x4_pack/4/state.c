#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct State {
    char *regs[256];
} State;

void echo_0(State *state) {
    printf("ECHO: \n");
}

void echo_1(State *state, char *arg0) {
    printf("ECHO: %s\n", arg0);
}

void echo_2(State *state, char *arg0, char *arg1) {
    printf("ECHO: %s|%s\n", arg0, arg1);
}

void echo_3(State *state, char *arg0, char *arg1, char *arg2) {
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
}

void print_1(State *state, char *idx) {
    int i = atoi(idx);
    printf("%s\n", state->regs[i]);
}

void printregs_0(State *state) {
    for (int i = 0; i < 256; ++i) {
        if (state->regs[i] != NULL) {
            printf("%d = %s\n", i, state->regs[i]);
        }
    }
}

void store_2(State *state, char *idx, char *what) {
    int i = atoi(idx);
    if (state->regs[i] != NULL) {
        free(state->regs[i]);
    }
    state->regs[i] = strdup(what);
}

void copy_2(State *state, char *dst, char *src) {
    int s = atoi(src);
    int d = atoi(dst);
    char *src_str = state->regs[s];
    char *copy = strdup(src_str);
    if (state->regs[d] != NULL) {
        free(state->regs[d]);
    }
    state->regs[d] = copy;
}

void clear_1(State *state, char *idx) {
    int i = atoi(idx);
    if (state->regs[i] != NULL) {
        free(state->regs[i]);
        state->regs[i] = NULL;
    }
}
