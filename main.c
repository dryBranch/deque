#include "deque.h"

#include <stdlib.h>
#include <stdio.h>

int i, *data;
int len = 10;
int *ds[10];

void print_all(void *data);
Deque* create_test_deque();
void test_remove(Deque *deque);

Deque* test_index_add();
void test_index_remove(Deque *deque);

void test_get(Deque *deque);
void test_clear(Deque *deque);
void test_index(Deque *deque);

void test_all();


int main(){
    test_all();

    return 0;
}

void test_all(){
    printf("\n%s()\n", __FUNCTION__);
    Deque *stack = create_test_deque();
    test_remove(stack);

    stack = test_index_add();
    test_index_remove(stack);

    stack = create_test_deque();
    test_get(stack);

    stack = create_test_deque();
    test_clear(stack);

    stack = create_test_deque();
    test_index(stack);
    
}

void test_index(Deque *deque){
    printf("\n%s()\n", __FUNCTION__);
    for(i = 0; i < len; i++){
        int c = deque_index_of(deque, ds[i]);
        printf("[%d]: %d\n", i, c);
    }
    printf("NULL: %d\n", deque_index_of(deque, NULL));
}

void test_clear(Deque *deque){
    printf("\n%s()\n", __FUNCTION__);
    deque_clear(deque);
    printf("size = %d\n", deque_size(deque));
    deque_foreach(deque, print_all);
    printf("\n");
}

void test_get(Deque *deque){
     printf("\n%s()\n", __FUNCTION__);
    int t[] = {0, -1, 2, -3, 100, -100};
    for(i = 0; i < (sizeof(t) / sizeof(int)); i++){
        data = (int *)deque_get(deque, t[i]);
        printf("[%d]: data = %d\n", t[i], *data);
    }
}

void test_index_remove(Deque *deque){
    printf("\n%s()\n", __FUNCTION__);

    deque_removeIndex(deque, 100);
    printf("size = %d\n", deque_size(deque));
    deque_foreach(deque, print_all);
    printf("\n");
    deque_removeIndex(deque, -100);
    printf("size = %d\n", deque_size(deque));
    deque_foreach(deque, print_all);
    printf("\n");
    deque_removeIndex(deque, 2);
    printf("size = %d\n", deque_size(deque));
    deque_foreach(deque, print_all);
    printf("\n");
    deque_removeIndex(deque, -2);
    printf("size = %d\n", deque_size(deque));
    deque_foreach(deque, print_all);
    printf("\n");
    for(i = 0; i < 3; i++){
        deque_removeIndex(deque, 0);
        printf("size = %d\n", deque_size(deque));
        deque_foreach(deque, print_all);
        printf("\n");
    }
    for(i = 0; i < 3; i++){
        deque_removeIndex(deque, -1);
        printf("size = %d\n", deque_size(deque));
        deque_foreach(deque, print_all);
        printf("\n");
    }
    deque_removeIndex(deque, 0);
    printf("size = %d\n", deque_size(deque));
    deque_foreach(deque, print_all);
    printf("\n");
    deque_removeIndex(deque, -1);
    printf("size = %d\n", deque_size(deque));
    deque_foreach(deque, print_all);
    printf("\n");
}

Deque* test_index_add(){
    Deque *deque = deque_create();
     printf("\n%s()\n", __FUNCTION__);
    for(i = 0; i < 5; i++){
        data = (int *)malloc(sizeof(int));
        *data = i;
        ds[i] = data;
        deque_addIndex(deque, data, 0);
        printf("size = %d\n", deque_size(deque));
    }
    for(i = 5; i < len; i++){
        data = (int *)malloc(sizeof(int));
        *data = i;
        ds[i] = data;
        deque_addIndex(deque, data, -1);
        printf("size = %d\n", deque_size(deque));
    }
    printf("create compele\n");
    deque_foreach(deque, print_all);
    printf("\n");
    return deque;
}

void test_remove(Deque *deque){
     printf("\n%s()\n", __FUNCTION__);
    for(i = 0; i < len; i++){
        printf("[%d] ", i + 1);
        deque_remove(deque, ds[(i + 5) % len]);
        deque_foreach(deque, print_all);
        printf("size = %d\n", deque_size(deque));
    }
    deque_remove(deque, ds[(i + 5) % len]);
    deque_foreach(deque, print_all);
    printf("size = %d\n", deque_size(deque));
    deque_remove(deque, ds[(i + 5) % len]);
    deque_foreach(deque, print_all);
    printf("size = %d\n", deque_size(deque));
}

Deque* create_test_deque(){
    Deque *stack = deque_create();
     printf("\n%s()\n", __FUNCTION__);
    for(i = 0; i < len; i++){
        data = (int *)malloc(sizeof(int));
        *data = i;
        ds[i] = data;
        deque_add(stack, data);
    }
    printf("add compelet, size = %d\n", deque_size(stack));
    deque_foreach(stack, print_all);
    printf("\n");
    return stack;
}

void print_all(void *data){
    int *d = (int *)data;
    printf("%d ", *d);
}