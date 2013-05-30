#include <string.h>
#include <map>
#include <iterator>
#include <string>
#include <iostream>
#include <bk_tree.h>
#include <gtest/gtest.h>

std::string rand_string(int maxlen = 8) {
    static const char alphanum[] = "0123456789_"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "abcdefghijklmnopqrstuvwxyz";

    std::string s;
    int len = rand() % (maxlen - 1) + 1;
    for (int i = 0; i < len; i++) {
        s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
    }
    return s;
}

void query(const char *key, int len, int dist, void *data) {
    std::map<std::string, int> &map = *static_cast<std::map<std::string, int>*>(data);
    std::string s(key, len);
    map[s] = dist;
}

TEST(bk_tree, query)
{
    srand(time(NULL));
    std::map<std::string, int> tree_entry, result;
    // create tree
    bk_tree_t *tree = bk_tree_create(levenshtein_dist, query);
    ASSERT_TRUE(tree != NULL);
    std::string query_string = rand_string();

    // add entry
    for (int i = 0; i < 1000; i++) {
        std::string s = rand_string();
        tree_entry[s] = tree->distance_fn(query_string.data(), query_string.size(), s.data(), s.size());
        ASSERT_EQ(0, bk_tree_insert(tree, s.data(), s.size()));
    }

    int dist = rand() % BK_DIST_MAX;

    // query
    int match = bk_tree_query(tree, query_string.data(), query_string.size(), dist, static_cast<void *>(&result));

    // check
    for (std::map<std::string, int>::iterator it = result.begin(); it != result.end(); ++it) {
        std::map<std::string, int>::iterator it2 = tree_entry.find(it->first);
        EXPECT_TRUE(it2 != tree_entry.end());
        EXPECT_EQ(it2->second, it->second);
        EXPECT_LE(it->second, dist);
        tree_entry.erase(it2);
        match --;
    }

    EXPECT_EQ(0, match);

    for (std::map<std::string, int>::iterator it = tree_entry.begin(); it != tree_entry.end(); ++it) {
        EXPECT_GT(it->second, dist);
    }

    // clean up
    bk_tree_destory(tree);
}

