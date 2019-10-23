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
TEST(DictTrieTests, PREDICT_EMPTY){
	DictionaryTrie dict;
	vector<string> test;
	ASSERT_EQ(dict.predictCompletions("apple", 5), test);
}
TEST(DictTrieTests, PREDICTSORT_TEST){
	DictionaryTrie dict;
	bool temp;
	temp = dict.insert("app", 4);
	temp = dict.insert("apps", 5);
	vector<string> test;
	test.push_back("apps");
	test.push_back("app");
	ASSERT_EQ(dict.predictCompletions("ap", 3), test);
}TEST(DictTrieTests, PREDICTLIST_TEST){
	DictionaryTrie dict;
	bool temp;
	temp = dict.insert("app",3);
	temp = dict.insert("apc",7);
	temp = dict.insert("apb",8);
	temp = dict.insert("apa",9);
	temp = dict.insert("apca", 1);
	temp = dict.insert("az",2);
	temp = dict.insert("ay",10);
	temp = dict.insert("azi", 1);
	vector<string> test = {"apa", "apb", "apc", "app", "apca"};
	ASSERT_EQ(dict.predictCompletions("ap", 7), test);
}
TEST(DictTrieTests, PREDICSAME_TEST){
	DictionaryTrie dict;
	bool temp;
	temp = dict.insert("apple", 6);
	temp = dict.insert("apples", 7);
	temp = dict.insert("applets", 5);
	temp = dict.insert("banana", 4);
	vector<string> test = {"apples", "apple", "applets"};
	ASSERT_EQ(dict.predictCompletions("apple", 3), test);
}
TEST(DictTrieTests, PREDICTLEFTMIDDLE_TEST){
	DictionaryTrie dict;
	bool temp;
	temp = dict.insert("banana", 4);
	temp = dict.insert("apple", 4);
	vector<string> test = {"apple"};
	ASSERT_EQ(dict.predictCompletions("apple", 3), test);
}
TEST(DictTrieTests, PREDICTSAMEFREQ_TEST){
	DictionaryTrie dict;
	bool temp;
	temp = dict.insert("applet", 3);
	temp = dict.insert("apb", 3);
	temp = dict.insert("apa", 3);
	vector<string> test = {"apa", "apb", "applet"};
	ASSERT_EQ(dict.predictCompletions("ap", 3), test);
}
