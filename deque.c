#include "deque.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef _DEQUE_ELEMENT
typedef struct _deque_element deque_element;
#endif // _DEQUE_ELEMENT

struct _deque
{
    deque_element *head;
    deque_element *tail;
    size_t size;
};

struct _deque_element
{
    void *value;
    struct _deque_element *prev;
    struct _deque_element *next;
};

static deque_element* element_create(void *value){
    deque_element *e = (deque_element *)malloc(sizeof(deque_element));
    e->next = e->prev = NULL;
    e->value = value;
    return e;
}

static void element_delete(deque_element *elememt){
    free(elememt);
}

static void element_destroy(deque_element *element, void (*free_function)(void*)){
    free_function(element->value);
    free(element);
}

size_t deque_size(Deque *deque){
    return deque->size;
}

Deque* deque_create(){
    Deque *ret = (Deque *)malloc(sizeof(Deque));
    ret->head = ret->tail = NULL;
    ret->size = 0;
    return ret;
}

int deque_clear(Deque *deque){
    int ret = deque->size;
    deque_element *cur, *next;
    for(cur = deque->head, next = NULL; cur != NULL; cur = next){
        next = cur->next;
        element_delete(cur);
    }
    deque->head = deque->tail = NULL;
    deque->size = 0;
    return ret;
}

int deque_destroy(Deque *deque, void (*freeFunction)(void *)){
    int ret = deque->size;
    deque_element *cur, *next;
    for(cur = deque->head, next = NULL; cur != NULL; cur = next){
        next = cur->next;
        element_destroy(cur, freeFunction);
    }
    deque->head = deque->tail = NULL;
    deque->size = 0;
    return ret;
}

Deque* deque_add(Deque *deque, void *value){
    deque_element *element = element_create(value);
    if(deque->size == 0){
        deque->head = deque->tail = element;
    }else{
        element->prev = deque->tail;
        deque->tail->next = element;
        deque->tail = element;
    }
    deque->size++;
    return deque;
}

Deque* deque_remove(Deque *deque, void *value){
    deque_element *cur;
    for(cur = deque->head; (cur != NULL) && (cur->value != value); cur = cur->next);
    if(cur != NULL){
        if(deque->size == 1){
            deque->head = deque->tail = NULL;
        }else if(cur == deque->head){
            cur->next->prev = NULL;
            deque->head = cur->next;
        }else if(cur == deque->tail){
            cur->prev->next = NULL;
            deque->tail = cur->prev;
        }else{
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
        }
        element_delete(cur);
        deque->size--;
    }
    
    return deque;
}

Deque* deque_addIndex(Deque *deque, void *value, int index){
    // comfirm 0 <= index <= deque->size
    if(index < 0){
        if((-index) > deque->size){
            index = 0;
        }else{
            index = deque->size + index;
        }
    }else if(index >= deque->size){
        index = deque->size;
    }

    deque_element *cur;
    int i;
    for(cur = deque->head, i = 0; i < index; i++, cur = cur->next);
    deque_element *e = element_create(value);
    if(cur == NULL){
        if(deque->size == 0){
            deque->head = deque->tail = e;
        }else{
            deque->tail->next = e;
            e->prev = deque->tail;
            deque->tail = e;
        }
    }else{
        if(cur == deque->head){
            deque->head = e;
        }else{
            cur->prev->next = e;
            e->prev = cur->prev;;
        }
        cur->prev = e;
        e->next = cur;
    }
    printf("add %d\n", *(int *)(e->value));
    deque->size++;
    return deque;
}

Deque* deque_removeIndex(Deque *deque, int index){
    if(deque->size == 0) return deque;
    // comfirm 0 <= index < deque->size
    if(index < 0){
        if((-index) > deque->size){
            index = 0;
        }else{
            index = deque->size + index;
        }
    }else if(index >= deque->size){
        index = deque->size - 1;
    }

    deque_element *cur;
    int i;
    for(cur = deque->head, i = 0; i < index; i++, cur = cur->next);

    if(cur->prev == NULL){
        deque->head = cur->next;
    }else{
        cur->prev->next = cur->next;
    }
    if(cur->next == NULL){
        deque->tail = cur->prev;
    }else{
        cur->next->prev = cur->prev;
    }
    element_delete(cur);
    deque->size--;
    return deque;
}

void* deque_get(Deque *deque, int index){
    if(deque->size == 0) return NULL;
    // comfirm 0 <= index < deque->size
    if(index < 0){
        if((-index) > deque->size){
            index = 0;
        }else{
            index = deque->size + index;
        }
    }else if(index >= deque->size){
        index = deque->size - 1;
    }

    deque_element *cur;
    int i;
    for(cur = deque->head, i = 0; i < index; i++, cur = cur->next);
    return cur->value;
}

Deque* deque_push(Deque *deque, void *value){
    deque_addIndex(deque, value, 0);
}

void* deque_pop(Deque *deque){
    void *val = deque_get(deque, 0);
    deque_removeIndex(deque, 0);
    return val;
}

void* deque_top(Deque *deque){
    return deque_get(deque, 0);
}

void* deque_buttom(Deque *deque){
    return deque_get(deque, -1);
}

int deque_empty(Deque *deque){
    if(deque == NULL) return -1;
    if(deque->size == 0) return 1;
    return 0;
}

int deque_contain(Deque *deque, void *value){
    if(deque_index_of(deque, value) == -1) return 0;
    return 1;
}

int deque_index_of(Deque *deque, void *value){
    if(deque == NULL || deque->size == 0) return -1;
    int index = 0;
    deque_element *cur;
    for(cur = deque->head; (cur != NULL) && (cur->value != value); cur = cur->next, index++);
    if(cur == NULL) return -1;
    return index;
}

void deque_foreach(Deque *deque, void (*callback)(void *)){
    if(deque == NULL) return;
    deque_element *cur;
    for(cur = deque->head; cur != NULL; cur = cur->next){
        callback(cur->value);
    }
}