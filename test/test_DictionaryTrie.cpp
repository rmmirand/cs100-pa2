/**
 * TODO: File HEADER
 *
 * Author:
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

/* TODO */
TEST(DictTrieTests, FALSEFIND_TEST){ 
    DictionaryTrie dict;
    bool temp = dict.insert("apple", 6);
    ASSERT_EQ(dict.find("banana"), false);
}
TEST(DictTrieTests, EMPTYSTRING_TEST) {
    DictionaryTrie dict;
    string empty = "";
    ASSERT_EQ(dict.insert(empty, 1), false);
}
TEST(DictTrieTests, INSERTROOT_TEST) {
    DictionaryTrie dict;
    bool temp;
    temp = dict.insert("banana", 5);
    ASSERT_EQ(dict.find("banana"), true);
}
