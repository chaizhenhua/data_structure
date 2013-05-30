#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <bk_tree.h>

static bk_node_t *bk_node_create(const char *key, int len, int dist) {
    bk_node_t *node = (bk_node_t *)calloc(sizeof(bk_node_t) + len, 1);
    if (node == NULL) {
        return NULL;
    }
    node->len = len;
    node->dist = dist;
    memcpy(&node->key, key, len);
    return node;
}

static void bk_node_destory(bk_node_t *node) {
    if (node == NULL) {
        return;
    }
    int i;
    for (i = 0; i < BK_DIST_MAX; i++) {
        if (node->childs[i]) {
            bk_node_destory(node->childs[i]);
        }
    }
    free(node);
}

static int bk_node_query(bk_node_t *node, const char *key, int len, int dist,
            bk_tree_distance_fn distance_fn, bk_tree_query_fn callback, void *data) {
    if (node == NULL) {
        return 0;
    }
    int i, ret = 0;
    int d = distance_fn(key, len, node->key, node->len);
    if (d <= dist) {
        callback(node->key, node->len, d, data);
        ret ++;
    }

    int max = (dist + d + 1 < BK_DIST_MAX) ? dist + d + 1 : BK_DIST_MAX;

    for (i = 0; i < max; i++) {
        ret += bk_node_query(node->childs[i], key, len, dist, distance_fn, callback, data);
    }
    return ret;
}

static int bk_node_add_child(bk_node_t *node, const char *key, int len, bk_tree_distance_fn distance_fn) {
    for (;;) {
        int dist = distance_fn(key, len, node->key, node->len);

        if (dist == 0) {
            return 0;
        }

        assert(dist < BK_DIST_MAX);

        if (node->childs[dist - 1]) {
            node = node->childs[dist - 1];
            continue;
        }

        bk_node_t *n = bk_node_create(key, len, dist);
        if (n == NULL) {
            return -1;
        }
        node->childs[dist - 1] = n;
        return 0;
    }
}

bk_tree_t *bk_tree_create(bk_tree_distance_fn distance, bk_tree_query_fn query) {
    bk_tree_t *tree;

    tree = (bk_tree_t *)malloc(sizeof(bk_tree_t));
    if (tree == NULL) {
        return NULL;
    }

    tree->root = NULL;
    tree->distance_fn = distance;
    tree->query_fn = query;
    return tree;
}

void bk_tree_destory(bk_tree_t *tree) {
    bk_node_destory(tree->root);
    free(tree);
}

int bk_tree_insert(bk_tree_t *tree, const char *key, int len) {
    if (tree->root) {
        return bk_node_add_child(tree->root, key, len, tree->distance_fn);
    }
    tree->root = bk_node_create(key, len, 0);
    if (tree->root == NULL) {
        return -1;
    }
    return 0;
}

int bk_tree_query(bk_tree_t *tree, const char *key, int len, int dist, void *data) {
    return bk_node_query(tree->root, key, len, dist, tree->distance_fn, tree->query_fn, data);
}

int levenshtein_dist(const char *key1, int len1, const char *key2, int len2){
    int cost = 0;
    int d1,d2,d3;
    if (len1 == 0) {
        return len2;
    }
    if (len2 == 0) {
        return len1;
    }
    if (key1[len1 - 1] != key2[len2 - 1]) {
        cost = 1;
    }

    d1 = levenshtein_dist(key1, len1 - 1, key2, len2) + 1;
    d2 = levenshtein_dist(key1, len1, key2, len2 - 1) + 1;
    d3 = levenshtein_dist(key1, len1 - 1, key2, len2 - 1) + cost;
    d2 = (d1 < d2) ? d1 : d2;
    return (d2 < d3) ? d2 : d3;
}

