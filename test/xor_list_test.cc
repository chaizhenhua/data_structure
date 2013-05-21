
#include <xor_list.h>
#include <gtest/gtest.h>

TEST(xor_list, xor_list_init)
{
    xor_list_t list;
    xor_list_init(&list);
    EXPECT_EQ(&list.tail, xor_node_next(&list.head, NULL));
    EXPECT_EQ(&list.head, xor_node_prev(&list.tail, NULL));
    EXPECT_EQ(NULL, xor_node_next(&list.tail, &list.head));
    EXPECT_EQ(NULL, xor_node_prev(&list.head, &list.tail));
}

TEST(xor_list, insert_and_delete)
{
    xor_list_t list;
    xor_list_init(&list);

    xor_node_t node[100];
    for (int i = 0; i < 100; i++) {
        node[i].key = i;
    }

    for (int i = 0; i < 100; i++) {
        xor_list_insert_tail(&list, &node[i]);
        xor_node_t *curr = &node[i];
        xor_node_t *prev = i ? &node[i-1] : &list.head;
        xor_node_t *next = &list.tail;
        EXPECT_EQ(next, xor_node_next(curr, prev) );
        EXPECT_EQ(prev, xor_node_prev(curr, next) );
    }

    EXPECT_EQ(&node[0], xor_node_next(&list.head, NULL));
    EXPECT_EQ(&node[1], xor_node_next(&node[0], &list.head));
    for (int i = 2; i < 100; i++) {
        EXPECT_EQ(&node[i], xor_node_next(&node[i-1], &node[i-2]));
        EXPECT_EQ(i, node[i].key);
    }

    xor_node_t *curr = xor_node_next(&list.head, NULL);
    xor_node_t *prev = &list.head;

    for (int i = 0; curr != &list.tail; i++) {
        EXPECT_EQ(i, curr->key);
        xor_node_t *tmp = curr;
        curr = xor_node_next(curr, prev);
        prev = tmp;
    }

    for (int i = 1; i < 100; i+= 2) {
        xor_node_delete(&node[i-1], &node[i]);
    }

    curr = xor_node_next(&list.head, NULL);
    prev = &list.head;

    for (int i = 0; i < 100; i+= 2) {
        EXPECT_EQ(i, curr->key);
        xor_node_t *tmp = curr;
        curr = xor_node_next(curr, prev);
        prev = tmp;
    }
}


