
#pragma once
#ifndef XOR_LIST_INCLUDE
#define XOR_LIST_INCLUDE
#include <stdint.h>
#include <stdlib.h>
typedef struct xor_node_s xor_node_t;
typedef int xor_key_t;

struct xor_node_s {
    xor_node_t *prext;
    xor_key_t  key;
};

typedef struct {
    xor_node_t   head;
    xor_node_t   tail;
} xor_list_t;

#define XOR_NODE_XOR(a, b) ( (xor_node_t*)( ((uintptr_t) (a)) ^ ((uintptr_t)(b)) ) )
#define xor_node_next(current, prev) xor_node_prext(current, prev)
#define xor_node_prev(current, next) xor_node_prext(current, next)
#define xor_node_tail(head) xor_node_xor((head)->xor, (head))

static inline xor_node_t *xor_node_prext(xor_node_t *current, xor_node_t *other) {
    return XOR_NODE_XOR(current->prext, other);
}

static inline void xor_node_insert(xor_node_t *prev, xor_node_t *next, xor_node_t *node) {
    xor_node_t *pprev = xor_node_prev(prev, next);
    xor_node_t *nnext = xor_node_next(next, prev);
    node->prext = XOR_NODE_XOR(prev, next);
    prev->prext = XOR_NODE_XOR(pprev, node);
    next->prext = XOR_NODE_XOR(node, nnext);
}

static inline void xor_node_delete(xor_node_t *prev, xor_node_t *node) {
    xor_node_t *next = xor_node_next(node, prev);
    xor_node_t *pprev = xor_node_prev(prev, node);
    xor_node_t *nnext = xor_node_next(next, node);
    next->prext = XOR_NODE_XOR(prev, nnext);
    prev->prext = XOR_NODE_XOR(pprev, next);
}

static inline void xor_list_init(xor_list_t *list) {
    list->head.prext = XOR_NODE_XOR(&list->tail, NULL);
    list->tail.prext = XOR_NODE_XOR(&list->head, NULL);
}

static inline int xor_list_empty(xor_list_t *list) {
    return xor_node_next(&list->head, NULL) == &list->tail;
}

static inline xor_node_t *xor_list_first(xor_list_t *list) {
    return xor_node_next(&list->head, NULL);
}

static inline xor_node_t *xor_list_last(xor_list_t *list) {
    return xor_node_prev(&list->tail, NULL);
}

static inline int xor_node_is_sentinel(xor_list_t *list, xor_node_t *node) {
    return (node == &list->head || node == &list->tail);
}

static inline void xor_list_insert_tail(xor_list_t *list, xor_node_t *node) {
    xor_node_t *prev = xor_node_prev(&list->tail, NULL);
    xor_node_insert(prev, &list->tail, node);
}

static inline void xor_list_insert_head(xor_list_t *list, xor_node_t *node) {
    xor_node_t *next = xor_node_next(&list->head, NULL);
    xor_node_insert(&list->head, next, node);
}

#endif /* XOR_LIST_INCLUDE */

