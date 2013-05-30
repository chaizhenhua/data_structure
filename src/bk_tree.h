
#pragma once

#define BK_DIST_MAX    16

typedef struct bk_node_s bk_node_t;

struct bk_node_s {
    int         dist;
    bk_node_t  *childs[BK_DIST_MAX];
    int         len;
    char        key[1];
};

typedef int  (*bk_tree_distance_fn) (const char *key1, int len1, const char *key2, int len2);
typedef void (*bk_tree_query_fn) (const char *key, int len, int dist, void *data);

typedef struct {
    bk_node_t            *root;
    bk_tree_distance_fn   distance_fn;
    bk_tree_query_fn      query_fn;
} bk_tree_t;

int bk_tree_insert(bk_tree_t *tree, const char *key, int len);
int bk_tree_query(bk_tree_t *tree, const char *key, int len, int dist, void *data);

bk_tree_t *bk_tree_create(bk_tree_distance_fn distance, bk_tree_query_fn query);
void bk_tree_destory(bk_tree_t *tree);

int levenshtein_dist(const char *key1, int len1, const char *key2, int len2);

