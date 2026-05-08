#include "stack_int.h"

#define INITIAL_CAPACITY 8

StackInt stack_create_int() {
    StackInt s = malloc(sizeof(struct StackIntRep));
    s->capacity = INITIAL_CAPACITY;
    s->top = -1;
    s->value = (int*) malloc(sizeof(int) * s->capacity);
    return s;
}

static void stack_resize(StackInt s) {
    s->capacity *= 2;
    s->value = (int*) realloc(s->value, sizeof(int) * s->capacity);
}

void stack_push_int(StackInt s, int value) {
    if (s->top + 1 >= s->capacity) stack_resize(s);
    s->value[++s->top] = value;
}

int stack_pop_int(StackInt s) {
    assert(s->top >= 0);
    return s->value[s->top--];
}

int stack_top_int(StackInt s) {
    assert(s->top >= 0);
    return s->value[s->top];
}

int stack_empty_int(StackInt s) {
    return s->top == -1;
}

void stack_free_int(StackInt s) {
    free(s->value);
    free(s);
}

void stack_set_top(StackInt s, int value){
    assert(s->capacity >= 0);
    s->value[s->top] = value;
}