#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct LINKED_STACK_NODE_s *LINKED_STACK_NODE;
typedef struct LINKED_STACK_NODE_s {
    LINKED_STACK_NODE next;
    void *data;
} LINKED_STACK_NODE_t[1];

typedef struct LINKED_STACK_s {
    LINKED_STACK_NODE head;
} LINKED_STACK_t[1], *LINKED_STACK;

int linked_stack_push(LINKED_STACK stack, void *data) {
    LINKED_STACK_NODE node = (LINKED_STACK_NODE) malloc(sizeof(LINKED_STACK_NODE_t));
    if (node != NULL) {
        node->data = data;
        node->next = stack->head;
        stack->head = node;
        return 1;
    } else {
        return 0;//cannot allocate memory
    }
}

void *linked_stack_pop(LINKED_STACK stack) {
    LINKED_STACK_NODE node;
    void *res = NULL;

    if (stack->head != NULL) {
        node = stack->head;
        res = node->data;
        stack->head = node->next;
        free(node);
    } else {
        //empty stack is popped
    }
    return res;
}

int parenthesis_type_check(char character1, char character2) {
    if (character1 == '(' && character2 == ')') {
        return 1;
    } else if (character1 == '[' && character2 == ']') {
        return 1;
    } else if (character1 == '{' && character2 == '}') {
        return 1;
    } else {
        return 0;
    }
}

int parenthesis_balance_algorithm(char* string){
    LINKED_STACK stack = NULL;

    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] == '(' || string[i] == '{' || string[i] == '[') {
            linked_stack_push((LINKED_STACK) &stack, string[i]);
        }
        if (string[i] == ')' || string[i] == '}' || string[i] == ']') {
            if (stack == NULL) {
                printf("ERROR:Stack is NULL.\n");
                return 0;
            } else if (!parenthesis_type_check(linked_stack_pop((LINKED_STACK) &stack), string[i])) {
                printf("ERROR:Parenthesis are not match\n");
                return 0;
            }
        }
    }
    if (stack==NULL) {
        return 1;
    } else{
        printf("Error! Stack is not empty. Stack have unpaired opening symbol/s.\n");
        return 0;
    }
}

int main() {
    char string[] = "({ test } )[]";
    if (parenthesis_balance_algorithm(string)) {
        printf("Balanced !");
    } else {
        printf("Unbalanced !");
    }
}