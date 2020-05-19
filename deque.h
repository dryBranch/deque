/* @author  harold
 * @email   2440800380@qq.com
 * @libinfo
 *  This is a simple linked list.
 *  It keep only the address of your data.
 *  So, you should garanteen the data is persistent.
 */

#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stddef.h>

typedef struct _deque Deque;

#ifdef __cplusplus
extern "C" {
#endif
/* create and close functions */
// ==========================================================

/* create an empty deque */
Deque* deque_create();
/* clear the empty WITH free the real data */
int deque_clear(Deque *deque);
/* clear the empty WITHOUT free the real data */
int deque_destroy(Deque *deque, void (*freeFunction)(void *));

// ==========================================================


/* basic usage */
// ==========================================================

/* get the size of deque */
size_t deque_size(Deque *deque);


/* add the element at the end of deque */
Deque* deque_add(Deque *deque, void *value);

/* remove the data by COMPARE ADDRESS */
Deque* deque_remove(Deque *deque, void *value);

/* add the data using index
 * the index could be any number
 * the POSITIVE index will be considerred as REVERSE ORDER
 * EXP index = -1 is the last element
 *     the out of range numbers will get the border.
 */
Deque* deque_addIndex(Deque *deque, void *value, int index);

/* remove the data using index WITHOUT free the real data
 * the index could be any number
 * the POSITIVE index will be considerred as REVERSE ORDER
 * EXP index = -1 is the last element
 *     the out of range numbers will get the border.
 */
Deque* deque_removeIndex(Deque *deque, int index);

/* get the address of real data
 * if the deque is empty, NULL will be return.
 * the index could be any number
 * the POSITIVE index will be considerred as REVERSE ORDER
 * EXP index = -1 is the last element
 *     the out of range numbers will get the border.
 */
void* deque_get(Deque *deque, int index);

/* add the data at the top of deque like stack */
Deque* deque_push(Deque *deque, void *value);

/* popup the data at the top of deque like stack 
 * remove and get the data
 */
void* deque_pop(Deque *deque);

/* get the data at the top of deque */
void* deque_top(Deque *deque);

/* get the data in the buttom of deque */
void* deque_buttom(Deque *deque);

/* return 1 for EMPTY, 0 for containing something, -1 for deque NULL POINTER */
int deque_empty(Deque *deque);

/* return 0 for not included, 1 for contained this */
int deque_contain(Deque *deque, void *value);

/* return the INDEX of data in the deque
 * if not included, return -1
 */
int deque_index_of(Deque *deque, void *value);

/* using callback() to manipulate every elements in the deque */
void deque_foreach(Deque *deque, void (*callback)(void *));

/* copy the address in deque to array */
void* deque_to_array(Deque *deque);

// ==========================================================
#ifdef __cplusplus
}
#endif

#endif // _DEQUE_H_