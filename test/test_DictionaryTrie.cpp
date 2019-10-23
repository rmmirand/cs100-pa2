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
    DictionaryTrie dicti;
    bool temp;
    temp = dicti.insert("apple", 7);
    temp = dicti.insert("banana", 5);
    ASSERT_EQ(dicti.find("apple"), true);
}TEST(DictTrieTests, FINDME_TEST){
	DictionaryTrie dict;
	bool temp = dict.insert("carrot", 1);
	temp = dict.insert("banana", 2);
	temp = dict.insert("durian", 3);
	temp = dict.insert("cap", 4);
	temp = dict.insert("duran", 5);
	temp = dict.insert("carott", 6);
	temp = dict.insert("durc", 7);
	temp = dict.insert("durca", 8);
	ASSERT_EQ(dict.find("durca"), true);
}
TEST(DictTrieTests, FINDLIST_TEST){
	DictionaryTrie dictii;
	bool temp;
	temp = dictii.insert("apple", 4);
	ASSERT_EQ(dictii.find("apple"), true);
}
